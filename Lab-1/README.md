# Compilers-Lab

A simple compiler with specs given in the pdf.

## Get the Source

From the command line, run

```sh
git clone https://www.github.com/AranyaAryaman/Compilers-Lab.git
```

OR

You can directly download the zip from [here](https://github.com/AranyaAryaman/Compilers-Lab/archive/master.zip)

## Usage

Run `make` on root folder to make the executable.
Now run `./compiler` on same directory to get a REPL. Press Ctrl+D to exit.

Alternatively, you can run `./compile <filename>` to give input from a file directly.
In this case, assembly output will be stored in `out.s` file.

For debug info, all lexemes are dumped into `lex.txt`, and all non-terminal expansions are dumped in `debug.txt`.

For a parse tree representation, run `python3 graph.py`. It reads debug.txt and shows a figure in matplotlib.
`graph.py` has the following dependencies -
- matplotlib
- networkx
- pygraphviz
To install them, refer to the next section.

## Install Optional Dependencies

Compiler itself does not require any deps. These are for generating the parse tree.

For debian based systems -

```sh
sudo apt install python3 python3-pip graphviz libgraphviz-dev pkg-config
python3 -m pip install --user matplotlib networkx pygraphviz
```

## Contributors

- [Avneet Singh](https://www.github.com/AvyChanna)
- [Aranya Aryaman](https://www.github.com/AranyaAryaman/)
- [Naveen Kumar](https://www.github.com/evilbefall)
- [Ajinkya](https://www.github.com/turingsherlock)
