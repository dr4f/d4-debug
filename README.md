# dr4-debug

*a cli tool to visualize and inspect dr4 documents*

For more information on the `dr4` format, [see the `dr4` foundation on github](https://github.com/dr4f)

## Intro

`dr4-debug` is an executable cli tool that allows visualization, debugging, and inspection of `dr4` documents and files. `dr4` is a binary data storage format that stores data in a tabular yet object-oriented manner. The executable is written in C and built with `CMAKE`.

## Building

In order to build `dr4-debug`, run the following commands in your terminal

```
$ mkdir -p bin
$ cd bin
$ cmake ..
$ make
```

### Testing

To run the tests, you just use "make test", from `CMAKE`. You can run the command from the binary directory you ran the previous commands in:

```
$ make test
```

## Examples

In the `examples/` directory, you can find a script called `dr4gen.py`. Running that script with one argument as the path name will generate a sample `dr4` document file you can test the `dr4-debug` executable on.
