# Hello

Example Hello World and w/ Makefile

## Build and Run

```sh
$ mkdir build

# Directly
$ g++ -std=c++20 -o build/hello hello.cxx
$ ./build/hello
Hello, world!

# Or...

# With Makefile
$ make run-release
Making output directories...
mkdir -p build/debug
mkdir -p build/release
Done!
Compiling Release...
g++ -std=c++20 -o build/release/hello hello.cxx
Done!
build/release/hello
Hello, world!
```

- [Content](/content/README.md)
- [Week 0](/content/chapter1/README.md)
- [Examples](/content/chapter1/examples/README.md)
