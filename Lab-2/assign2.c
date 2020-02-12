#include<stdio.h>
#include<stdlib.h>

int count_lines()
{
	FILE *fptr;
	int lines=0;
	char c;
	fptr=fopen("input2.txt","r");
	if(fptr==NULL)
	{
		printf("Couldn't find the file!\n");
		return -1;
	}
	c=getc(fptr);
	while(c!=EOF)
	{
		if(c=='\n')
		{
			lines++;
		}
		c=getc(fptr);
	}
	fclose(fptr);
	return lines;
}
int count_comments()
{
	FILE *fptr;
	int comments=0,comment_state=0;
	fptr=fopen("input2.txt","r");
	if(fptr==NULL)
	{
		return -1;
	}
	char c;
	c=getc(fptr);
	while(c!=EOF)
	{
		if(c=='/')
		{
			c=getc(fptr);
			if(c=='*')
			{
				comment_state=1;
			}
		}
		if(c=='*')
		{
			c=getc(fptr);
			if(c=='/' && comment_state==1)
			{
				comments++;
				comment_state=0;
			}			
		}
		c=getc(fptr);
	}
	fclose(fptr);
	return comments;
}
int count_blank()
{
	int blanks=0,blank_state=0;
	FILE *fptr;
	fptr=fopen("input2.txt","r");
	if(fptr==NULL)
	{
		return -1;
	}
	char c;
	c=getc(fptr);
	while(c!=EOF)
	{
		if(c=='\n')
		{
			if(blank_state==1)
			{
				blanks++;
				blank_state=0;
			}
			c=getc(fptr);
			if(c=='\n')
			{
				blanks++;
				blank_state=1;
			}
		}
		else
		{
			blank_state=0;
		}
		c=getc(fptr);
	}
	fclose(fptr);
	return blanks;
	
}
int main()
{
	printf("Number of lines		: %d\n",count_lines());
	printf("Number of Comments		: %d\n",count_comments());
	printf("Number of blank lines		: %d\n",count_blank());
	return 0;
}
