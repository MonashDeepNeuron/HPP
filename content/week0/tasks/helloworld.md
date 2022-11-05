# Hello World!

If you've never programmed before, a "Hello World" program is a simplest program and is often used to introduce a language. The first Hello World was created in Brian Kernighan's 1972 "A Tutorial Introduction to the Language B".

---

## Contents

- [Hello World!](#hello-world)
  - [Contents](#contents)
  - [Task 6](#task-6)
    - [6.1 : First C++](#61--first-c)
    - [6.2 : Build and Run](#62--build-and-run)
    - [6.3 : Makefiles](#63--makefiles)
    - [6.4 : Debugging](#64--debugging)
    - [6.5 : Hello World - bpt](#65--hello-world---bpt)
  - [Links](#links)

---

## Task 6

### 6.1 : First C++

To begin we are going to open a new terminal window. We car going to create a directory called "hello", enter it and create some files and open VSCode there.

```sh
# Makes new directory
mkdir hello

# Enter `hello`
cd hello

# Create files `hello.cxx` and `README.md`
touch hello.cxx README.md

# Open VSCode
code .
```

Open the `hello.cxx` file by clicking it on the left file view.

Here is "Hello World" in C++.

```cxx
// This is a comment, these are ignored by the compiler

/// Preprocessor statement using `#` symbol
/// The preprocessor runs at compile time before the code is compiled
/// `#include` copies the header `iostream` into the current file
#include <iostream>

/// Main function
/// Entry point of the executable.
/// Takes no arguments and returns an `int`.
auto main () -> int
{
    /// From the namespace `std`.
    /// Use `cout` (character out).
    /// Put (<<) the string literal to stream.
    /// From `std` put a `endl` specifier. 
    std::cout << "Hello World!" << std::endl;

    /// Return 0 on successful termination.
    return 0;
}
```

Don't worry too much about the details as we will discuss in greater detail during the meetup.

---

### 6.2 : Build and Run

Press `` ctrl + ` `` to open an integrated terminal window in VSCode. Make a new directory called `build` and run the following command to compile the code.

```sh
# Make `build` directory
mkdir build

# Compile with GCC
g++-12 -std=c++20 -o build/hello hello.cxx
```

Let's break this command down.

- `g++-12` - This is the GNU C++ compiler from the GCC package. The `-12` just indicates that this is version twelve of GCC.
- `-std=c++20` - This sets the C++ standard. The C++ standard is like the version of the language. C++20 is the most recent version.
- `-o build/hello` - The `-o` flag indicates and output file name. Because we wrote it with a path in front of it (`build/*`), it will output to that path.
- `hello.cxx` - The source file we want to compile.

---

### 6.3 : Makefiles

But writing out these compile commands is tedious and error-prone. `make` is a tool that can read a Bash-like file and build your software for you based on pre-written commands. The command configurations are called recipes adn you can write them in such a way that different recipes can depend on each other and allowing you to break down the steps of building an application.

Create a file called `Makefile` and copy the contents below.

```sh
touch Makefile
```

```Makefile
# Variables

# C++ compiler
CXX = g++-12

# C++ standard
STDCXX = -std=c++20

# Source file
SRC = hello.cxx

# Executable name
EXE = hello

# Build directory
BUILDDIR = build

# Recipes are a name followed by a colon and its dependencies
# eg. `name: dep1 dep2`

# Builds debug and release
all: debug release

# Builds release and runs
run: all run-release

# Cleans output files
clean:
    @echo "Cleaning..."
    rm $(BUILDDIR)/**/*.o
    rm $(BUILDDIR)/**/$(EXE)
    @echo "Done!"

# Runs the release build
run-release: release
    $(BUILDDIR)/release/$(EXE)

# Builds release config
release: dirs
    @echo "Compiling Release..."
    $(CXX) $(STDCXX) -o $(BUILDDIR)/release/$(EXE) $(SRC)
    @echo  "Done!"

# Runs debug build
run-debug: debug
    $(BUILDDIR)/debug/$(EXE)

# Build debug config
debug: dirs
    @echo "Compiling Debug..."
    $(CXX) -g $(STDCXX) -o $(BUILDDIR)/debug/$(EXE) $(SRC)
    @echo  "Done!"

# Create need directories
dirs:
    @echo "Making output directories..."
    mkdir -p $(BUILDDIR)/debug
    mkdir -p $(BUILDDIR)/release
    @echo "Done!"
```

To build with make simply run

```sh
# Run make 
$ make
.
.
.
Hello World!
```

---

### 6.4 : Debugging

Debugging is the crux of fixing issues in code. Debuggers allow us to step through the running code and diagnose any issues that are occurring as they occur. Debugging a single executable is pretty trivial but a sufficiently large codebase can become quite complex.

For that reason we are going to go into debugging a little bit more at the meetup as configuring VSCode is a bit tricky. The debugging also doesn't show anything particularly interesting for a simple "Hello World" program.

If you know how a debugger works, you can have a play with VSCode and see if you can get it to work.

---

### 6.5 : Hello World - bpt

`make` is a useful tool and paired with Cmake you can configure and build very large and complex code bases, but these configuration files are hard to read, tedious to write and error prone. Cmake is also a good and pretty standard in industry for C and C++ developers, but this standard is pretty outdated. So for the majority of this series we're going to be using a new tool called `bpt`. bpt is a lot like `pip` (Python), `gem` (Ruby), `hackage` (Haskell) and `cargo` (Rust) allow near seamless control over control over dependencies, testing and distribution of our software.

One thing to note is bpt experimental, robust enough to handle most cases but has a few caveats, however, beyond a few libraries to ease utility, we won't need many dependencies as we are mostly look at the C++ language and C++ standard library and tus dependencies won't be a major issue. However, we using bpt as it has a pretty robust, plug-and-play testing framework and more intuitive build procedures.

To start off open a new terminal window and run the following command. Keep the default options by pressing enter for each instruction.

```sh
bpt new hello-bpt
code hello-bpt
```

The directory structure should look like this:

```sh
hello-bpt
├── README.md
├── bpt.yaml
└── src
    └── hello-bpt
        ├── hello-bpt.cpp
        └── hello-bpt.hpp
```

You can delete the `hello-bpt` directory and its contents in the `src/` directory as these are just temporaries. Create a file in `src/` called `hello.main.cxx`. Copy the "Hello World" program from your other directory (or above again) and past into the newly created file.

> bpt uses 'stem-leaf' file extensions to determine the purpose of a file. e.g. the `*.main.*` middle stem indicates to bpt that this is a executable that is run (as opposed to a library). You'll learn more about these as we go along.

Now simply run the following command to build the bpt project.

```sh
bpt build -t :c++20:gcc-12 -o build
```

This will spit out the binary into `build/`, dropping both file extensions. To run the program, simply call.

```sh
$ ./build/hello
Hello World!
```

---

## Links

- [Previous Page: VSCode](/content/week0/tasks/vscode.md)
- [Next Page: Compiler Explorer](/content/week0/tasks/godbolt.md)
- [Content](/content/README.md)
- [HOME](/README.md)
