# Hello World

If you've never programmed before, a "Hello World" program is a simplest program and is often used to introduce a language. The first Hello World was created in Brian Kernighan's 1972 "A Tutorial Introduction to the Language B".

## Introducing C++

Before you write you first C++ program I will cover a basic synopsis of the language's features.

C++ is a high-level, general purpose compiled programming language. It is strongly-typed with a static-type system and supports multi-paradigm programming.

Most of you would have had exposure to interpreted languages (Python, Ruby, Java, Bash etc.) who have a secondary program; called the interpreter, that runs alongside your code, converting the "higher level" instructions into machine code (binary) as it reads through the code.

C++ works differently, it is a compiled language. This simply means all of the C++ code is converted into machine instructions (by a compiler) before you execute the program. This has the benefit of allowing software to run on "bare metal", meaning the code you write is actually running on the machine (to some degree).

Because of C++ ability to run on baremetal, many people claim it is a "low-level" language however, this could not be more false. Almost all programming languages are mid-to-high level. This is because most support general abstraction techniques take you away from dealing with the machine directly. Only assembly and bytecode languages could be considered "low-level" like; LLVM, x86_64 etc., as these give control over memory and CPU instructions.

But C++ can style more directly interact with the hardware, how can that be if it isn't a low level language. Two things give C++ its power over hardware, first is its _memory model_. Many languages have little or no notion of memory. Data is data and it is as big or small as it is. How big is `int` in Python? To many this doesn't cross their minds when writing Python because you don't need to and that is one of the many benefits of Python. However, there is limits to resources you can use in some circumstances and sometimes you need to be able to guarantee certain memory usages from your software. C++ is one of the language that has a "conscious" notion of memory usage and gives you control over these resources. There is one problem with this, not all computer architectures are the same and don't have the same notion of memory. To tackle this, C++ uses the notion of a universal abstract machine. This is C++ second power over hardware. It has mechanisms for interacting with the underlying hardware through the OS but how it gets there is not to the concern of the developer (unless developing in kernel-space as opposed to user-space). You can use standardized features to access these resources effectively.

I mentioned above that C++ is strongly typed with a static type system. What does this mean? A strong typing basically means that types will not be implicitly cast (converted) to a different type (there are some exceptions to this but we'll cover this in chapter 2). A static type system means that all data must have an explicit type that must be known at compile time.

To wrap it off I'll briefly discuss the paradigms and styles you can write C++ in. The most obvious is procedural, similar to C. This paradigm simply uses free functions that operate on free data, performing instructions according to a procedure or set of instructions. Paired with procedural programming, C++ also allows for imperative programming style programming which consists of functions changing the systems state. This style centers mostly on telling the computer what exactly what you want done. C++ also support object-oriented-programming (OOP) with its primary IO library using many OOP patterns to create runtime polymorphism. The most popular paradigm used in C++ today is generic programming. C++ has many features that allows you to write code for generic types as opposed to creating new functions for every possible combination of types. Finally, C++ also supports functional programming patterns that allow for for creating general purpose algorithms that are composed create more specific data manipulation.

Hopefully this gives you an idea into the kind of language C++.

## Hello C++

To begin open a new terminal window, create a directory called 'hello', change to the newly created directory and open it in your text editor of choice.

```sh
# Makes new directory
mkdir hello

# Enter `hello`
cd hello

# Create files `hello.cxx`
touch hello.cxx

# Open text editor of choice
```

Open the `hello.cxx` file, copying and pasting the program below into the file.

<span>Filename: hello.cxx</span>

```cxx
{{#include examples/hello/hello.cxx}}
```

## Building and Running

Reopen your terminal at the 'hello' directory and make a new directory called `build`. You can then run the following command to compile the code.

```sh
# Make `build` directory
$ mkdir build

# Compile with GCC
$ g++ -std=c++20 -o build/hello hello.cxx

$ ./build/hello
Hello World!
```

Let's break this command down.

- `g++` - This is the GNU C++ compiler from the GCC package. The `-12` just indicates that this is version twelve of GCC.
- `-std=c++20` - This sets the C++ standard. The C++ standard is like the version of the language. C++20 is the most recent version.
- `-o build/hello` - The `-o` flag indicates and output file name. Because we wrote it with a path in front of it (`build/*`), it will output to that path.
- `hello.cxx` - The source file we want to compile.

## Hello World w/ Make

While building this program is relatively simple, much larger programs become super cumbersome to write out every time and trying to remember each flag and command is a difficult task. Throw in the fact that there are many different compilers available to build a particular C++ project in but not all of them are available on every platform. This can make the task of compiling C++ programs difficult and intricate. Luckily there are tools make compiling much easier. One such tool is GNU `make` tool. `make` uses a 'Makefile' as an input which describes various build recipes. A recipe can be used as an action for `make` to complete or used as a dependency of another recipe. For out simple 'Hello, world!' program we can create a `Makefile` like the one below alongside our source file. This sample `Makefile` has some basic recipes for building with or without debug symbols (commonly known as debug and release modes) and even cleanup to ensure a clean build directory.

> Note: Windows users skip ahead.

<span>Filename: Makefile</span>

```markdown
{{#include examples/hello/Makefile}}
```

We can build our project using one of the many build recipes. This will output our program into a directory defined the `Makefile`. We can then run the generated executable.

```sh
make debug
./build/debug/hello
```

## Hello World w/ CMake

`make` is a useful tool but it can be fairly obscure what is happening with all of the defined variables. It is also hard to change parts of the configuration which often leads to many different `Makefile`s existing for different configurations which can be difficult to maintain. `make` is also only available on UNIX based platforms meaning if you are Windows you can't use `make` to build your project and instead must use something like Visual Studio project files. So how do we handle all of these different configurations and build systems? We can use another tool CMake. CMake is a metabuild system which is used to configure your project and generate different build scripts from one configuration so the same project cna be built for both `make`, Visual Studio, Xcode and many other build systems. For our 'Hello, world!' program we just need a single CMake configuration file (called `CMakeLists.txt` files) in the same directory as our source file.

```CMakeLists.txt
{{#include examples/hello-cmake/CMakeLists.txt}}
```

Using this we can generate a different builds for different platforms. You cna do so by running the following commands in a terminal at the same directory the source file is in.

### Configure

```sh
# Generate a Makefile
cmake -S . -B build -G "Unix Makefiles"

# Generate Xcode project files
cmake -S . -B build -G Xcode

# Generate Visual Studio project files
# `-A` flag used to specify architecture for VS project files
cmake -S . -B build -G "Visual Studio 19 2022" -A x64
```

### Build

```sh
cmake --build build --target HelloCMake
```

### Run

```sh
$ ./build/HelloCMake
Hello, CMake!
```
