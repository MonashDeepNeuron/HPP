# Installing Software

In this section we will install all the relevant software for developing C++ programs.

## WSL & Linux

To get started open a new terminal session (for WSL, use the WSL terminal) and update your system package managers local package index. This is a list of all available packages and their versions. We can then install some system critical packages that we need in order to develop C++ programs. From there we can install Homebrew, a cross platform package manager which we will use to install our C++ compiler(s) and debuggers.

```sh
# Update apt (replace apt with relevant package manager if you are not on Ubuntu)
$ sudo apt update
$ sudo apt upgrade -y

# Install system packages
$ sudo apt install git curl wget ca-certificates build-essential

# Install Homebrew and update
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
$ brew update
$ brew upgrade

# Install C++ compiler(s), debuggers
$ brew install gcc llvm gdb
```

## MacOS

To begin, open a new terminal session install Homebrew, a cross platform package manager which will then use to install our C++ compiler(s), debuggers, cURL and Git.

```sh
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
$ brew update
$ brew upgrade
$ brew install gcc llvm gdb curl git
```

## Verify Installation

You can verify that GCC installed the correct version by running the following command. The output should be similar to this.

```sh
$ gcc-12 -v
Reading specs from /home/linuxbrew/.linuxbrew/Cellar/gcc/12.2.0/bin/../lib/gcc/current/gcc/x86_64-pc-linux-gnu/12/specs
COLLECT_GCC=gcc-12

# Other info ...

gcc version 12.2.0 (Homebrew GCC 12.2.0)
```

## Authenticating Git with GitHub

If you have a GitHub (or other) account and you want to link it to your machine, run the following commands, replacing `<>` with your personal details.

```sh
$ git config --global user.name "<github-username>"
$ git config --global user.email "<github-email>"
```

## Installing bpt

bpt is a build and packaging tool for C++. It makes consuming C++ libraries, running tests and packaging your code much easier compared to conventional methods (notably Cmake).

```sh
# Linux (WSL included)
curl bpt.pizza/get/linux -Lo bpt

# MacOS
curl bpt.pizza/get/macos -Lo bpt

# Both
chmod a+x bpt
./bpt install-yourself
```

## Installing VSCode

Go to [VSCode's Download page](https://code.visualstudio.com/download) and install it for your machines host OS.

> Note: For WSL users, this means install on the Windows side.

On its own VSCode is just a text editor like Windows Notepad but with coloured text however, using extensions we can set it up for developing with any language. Open VSCode as you would any other app in Windows, MacOS or Linux. In VSCode, open the extension marketplace tab. In the search bar, search for the following extensions click on the extension and click and click the install button for them.

> Note: For WSL users, only install the extensions marked 'WSL only' on the Windows side. The other extensions must be installed on the WSL. Install the them after opening VSCode in WSL (instructions below).

- C/C++
- GitLens
- Git Graph
- GitHub Pull Requests and Issues
- Sonarlint
- Remote development (WSL only)
- WSL (WSL only)
- Remote SSH (WSL only)

You may have to restart VSCode for the extensions to load. Finally, press `ctrl + ,` to open settings. in the search bar search for "cpp default standard". In the drop down select `c++20`.

To open VSCode from the terminal, open a new terminal window and type.

```sh
# `.` represents 'this' directory
$ code .
```

This will open VSCode in the current user directory which should be `~` which represents your users home directory. WSL users, make sure to launch VSCode from your WSL terminal this time. And that is it, everything should be set up and ready to go.
