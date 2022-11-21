# Hello World!

If you've never programmed before, a "Hello World" program is a simplest program and is often used to introduce a language. The first Hello World was created in Brian Kernighan's 1972 "A Tutorial Introduction to the Language B".

## Contents

- [Hello World!](#hello-world)
  - [Contents](#contents)
  - [Task 6](#task-6)
    - [6.1 : Introducing C++](#61--introducing-c)
    - [6.2 : First C++](#62--first-c)
    - [6.3 : Build and Run](#63--build-and-run)
    - [6.4 : Debugging](#64--debugging)
    - [6.5 : Hello World - bpt](#65--hello-world---bpt)
  - [Links](#links)

## Task 6

### 6.1 : Introducing C++

Before you write you first C++ program I will cover a basic synopsis of the language's features.

C++ is a high-level, general purpose compiled programming language. It is strongly-typed with a static-type system and supports multi-paradigm programming.

Most of you would have had exposure to interpreted languages (Python, Ruby, Java, Bash etc.) who have a secondary program; called the interpreter, that runs alongside your code, converting the "higher level" instructions into machine code (binary) as it reads through the code.

C++ works differently, it is a compiled language. This simply means all of the C++ code is converted into machine instructions (by a compiler) before you execute the program. This has the benefit of allowing software to run on "bare metal", meaning the code you write is actually running on the machine (to some degree).

Because of C++ ability to run on baremetal, many people claim it is a "low-level" language however, this could not be more false. Almost all programming languages are mid-to-high level. This is because most support general abstraction techniques take you away from dealing with the machine directly. Only assembly and bytecode languages could be considered "low-level" like; LLVM, x86_64 etc., as these give control over memory and CPU instructions.

But C++ can style more directly interact with the hardware, how can that be if it isn't a low level language. Two things give C++ its power over hardware, first is its _memory model_. Many languages have little or no notion of memory. Data is data and it is as big or small as it is. How big is `int` in Python? To many this doesn't cross their minds when writing Python because you don't need to and that is one of the many benefits of Python. However, there is limits to resources you can use in some circumstances and sometimes you need to be able to guarantee certain memory usages from your software. C++ is one of the language that has a "conscious" notion of memory usage and gives you control over these resources. There is one problem with this, not all computer architectures are the same and don't have the same notion of memory. To tackle this, C++ uses the notion of a universal abstract machine. This is C++ second power over hardware. It has mechanisms for interacting with the underlying hardware through the OS but how it gets there is not to the concern of the developer (unless developing in kernel-space as opposed to user-space). You can use standardized features to access these resources effectively.

I mentioned above that C++ is strongly typed with a static type system. What does this mean? A strong typing basically means that types will not be implicitly cast (converted) to a different type (there are some exceptions to this but we'll cover this in [week 1](/content/part2/README.md)). A static type system means that all data must have an explicit type that must be known at compile time.

To wrap it off I'll briefly discuss the paradigms and styles you can write C++ in. The most obvious is procedural, similar to C. This paradigm simply uses free functions that operate on free data, performing instructions according to a procedure or set of instructions. Paired with procedural programming, C++ also allows for imperative programming style programming which consists of functions changing the systems state. This style centers mostly on telling the computer what exactly what you want done. C++ also support object-oriented-programming (OOP) with its primary IO library using many OOP patterns to create runtime polymorphism. The most popular paradigm used in C++ today is generic programming. C++ has many features that allows you to write code for generic types as opposed to creating new functions for every possible combination of types. Finally, C++ also supports functional programming patterns that allow for for creating general purpose algorithms that are composed create more specific data manipulation.

Hopefully this gives you an idea into the kind of language C++ is and how powerful of a language it is.

### 6.2 : First C++

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

[Example 1](/content/part1/examples/hello/hello.cxx)

Don't worry too much about the details as we will discuss in greater detail during the meetup.

### 6.3 : Build and Run

Press `` ctrl + ` `` to open an integrated terminal window in VSCode. Make a new directory called `build` and run the following command to compile the code.

```sh
# Make `build` directory
$ mkdir build

# Compile with GCC
$ g++-12 -std=c++20 -o build/hello hello.cxx

$ ./build/hello
Hello World!
```

Let's break this command down.

- `g++-12` - This is the GNU C++ compiler from the GCC package. The `-12` just indicates that this is version twelve of GCC.
- `-std=c++20` - This sets the C++ standard. The C++ standard is like the version of the language. C++20 is the most recent version.
- `-o build/hello` - The `-o` flag indicates and output file name. Because we wrote it with a path in front of it (`build/*`), it will output to that path.
- `hello.cxx` - The source file we want to compile.

### 6.4 : Debugging

Debugging is the crux of fixing issues in code. Debuggers allow us to step through the running code and diagnose any issues that are occurring as they occur. Debugging a single executable is pretty trivial but a sufficiently large codebase can become quite complex.

For that reason we are going to go into debugging a little bit more at the meetup as configuring VSCode is a bit tricky. The debugging also doesn't show anything particularly interesting for a simple "Hello World" program.

If you know how a debugger works, you can have a play with VSCode and see if you can get it to work.

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

[Example 2](/content/part1/examples/hello-bpt)

## Links

- [Previous Page : VSCode](/content/part1/tasks/vscode.md)
- [Next Page : Compiler Explorer](/content/part1/tasks/godbolt.md)
- [Content](/content/README.md)
- [HOME](/README.md)