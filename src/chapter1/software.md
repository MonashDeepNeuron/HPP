# Installing Software

In this section we will install all the relevant software for developing C++ programs.

## WSL & Linux

To get started open a new terminal session (for WSL, use the WSL terminal) and update your system package managers local package index. This is a list of all available packages and their versions. We can then install some system critical packages that we need in order to develop C++ programs.

```sh
# Update apt (replace apt with relevant package manager if you are not on Ubuntu)
$ sudo apt update
$ sudo apt upgrade -y

# Install system packages
$ sudo apt install git curl wget ca-certificates build-essential cmake
```

## MacOS

To begin, open a new terminal session install Homebrew, a cross platform package manager which will then use to install our C++ compiler(s), debuggers, cURL and Git.

```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew update
brew upgrade
brew install gcc llvm gdb curl git cmake
```

## Verify Installation

You can verify that GCC installed correctly by running the following commands.

```sh
gcc -v
g++ -v
```
