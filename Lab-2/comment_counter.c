#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Using preprocessor macros instead of enums, per request; normally
 * I would use enums, since they obey scoping rules and
 * show up in debuggers.
 */
#define TEXT           0
#define SAW_SLASH      1
#define SAW_STAR       2
#define SINGLE_COMMENT 3
#define MULTI_COMMENT  4

#define TOTAL_STATES   5

#define NO_ACTION      0
#define INC_TOTAL      1
#define INC_SINGLE     2
#define INC_MULTI      4

/**
 * This example assumes 7-bit ASCII, for a total of
 * 128 character encodings.  You'll want to change this
 * to handle other encodings.
 */
#define ENCODINGS    128

/**
 * Need a state table to control state transitions and an action
 * table to specify what happens on a transition.  Each table
 * is indexed by the state and the next input character.
 */
static int  state[TOTAL_STATES][ENCODINGS]; // Since these tables are declared at file scope, they will be initialized to
static int action[TOTAL_STATES][ENCODINGS]; // all elements 0, which correspond to the "default" states defined above.

/**
 * Initialize our state table.
 */
void initState( int (*state)[ENCODINGS] )
{
  /**
   * If we're in the TEXT state and see a '/' character, move to the SAW_SLASH
   * state, otherwise stay in the TEXT state
   */
  state[TEXT]['/'] = SAW_SLASH;

  /**
   * If we're in the SAW_SLASH state, we can go one of three ways depending
   * on the next character.
   */
  state[SAW_SLASH]['/'] = SINGLE_COMMENT;
  state[SAW_SLASH]['*'] = MULTI_COMMENT;
  state[SAW_SLASH]['\n'] = TEXT;

  /**
   * For all but a few specific characters, if we're in any one of
   * the SAW_STAR, SINGLE_COMMENT, or MULTI_COMMENT states,
   * we stay in that state.
   */
  for ( size_t i = 0; i < ENCODINGS; i++ )
  {
    state[SAW_STAR][i] = MULTI_COMMENT;
    state[SINGLE_COMMENT][i] = SINGLE_COMMENT;
    state[MULTI_COMMENT][i] = MULTI_COMMENT;
  }

  /**
   * Exceptions to the loop above.
   */
  state[SAW_STAR]['/'] = TEXT;
  state[SAW_STAR]['*'] = SAW_STAR;

  state[SINGLE_COMMENT]['\n'] = TEXT;
  state[MULTI_COMMENT]['*'] = SAW_STAR;
}

/**
 * Initialize our action table
 */
void initAction( int (*action)[ENCODINGS] )
{
  action[TEXT]['\n'] = INC_TOTAL;
  action[SAW_STAR]['/'] = INC_MULTI;
  action[MULTI_COMMENT]['\n'] = INC_MULTI | INC_TOTAL;   // Multiple actions are bitwise-OR'd
  action[SINGLE_COMMENT]['\n'] = INC_SINGLE | INC_TOTAL; // together
  action[SAW_SLASH]['\n'] = INC_TOTAL;
}

/**
 * Scan the input file for comments
 */
void countComments( FILE *stream, size_t *totalLines, size_t *single, size_t *multi )
{
  *totalLines = *single = *multi = 0;

  int c;
  int curState = TEXT, curAction = NO_ACTION;

  while ( ( c = fgetc( stream ) ) != EOF )
  {
    curAction = action[curState][c]; // Read the action before we overwrite the state
    curState = state[curState][c];   // Get the new state (which may be the same as the old state)

    if ( curAction & INC_TOTAL )     // Execute the action.
      (*totalLines)++;

    if ( curAction & INC_SINGLE )
      (*single)++;

    if ( curAction & INC_MULTI )
      (*multi)++;
  }
}

/**
 * Main function.
 */
int main( int argc, char **argv )
{
  /**
   * Input sanity check
   */
  if ( argc < 2 )
  {
    fprintf( stderr, "USAGE: %s <filename>\n", argv[0] );
    exit( EXIT_FAILURE );
  }

  /**
   * Open the input file
   */
  FILE *fp = fopen( argv[1], "r" );
  if ( !fp )
  {
    fprintf( stderr, "Cannot open file %s\n", argv[1] );
    exit( EXIT_FAILURE );
  }

  /**
   * If input file was successfully opened, initialize our
   * state and action tables.
   */
  initState( state );
  initAction( action );

  size_t totalLines, single, multi;

  /**
   * Do the thing.
   */
  countComments( fp, &totalLines, &single, &multi );
  fclose( fp );

  printf( "File                 : %s\n", argv[1] );
  printf( "Total lines          : %zu\n", totalLines );
  printf( "Single-comment lines : %zu\n", single );
  printf( "Multi-comment lines  : %zu\n", multi );

  return EXIT_SUCCESS;
}