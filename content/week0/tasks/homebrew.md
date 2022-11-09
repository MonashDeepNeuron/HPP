# Homebrew

Homebrew is a system package manager similar to `apt` however, it is cross platform allowing us to install packages on Linux and MacOS.

---

## Contents

- [Homebrew](#homebrew)
  - [Contents](#contents)
  - [Task 3](#task-3)
    - [3.1 : Installing Homebrew](#31--installing-homebrew)
      - [Note](#note)
    - [3.2 : Packages from Homebrew](#32--packages-from-homebrew)
    - [3.3 : Installing Git (MacOS only)](#33--installing-git-macos-only)
    - [3.4 : Authenticating Git](#34--authenticating-git)
  - [Links](#links)

---

## Task 3

### 3.1 : Installing Homebrew

Install Homebrew is super simple. Copy the following command and run.

```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### Note

> For linux users you will need `curl` installed. Look below for the relevant commands.

Like `apt` we should update its package index and packages (although non-should be installed if this is a fresh install).

```sh
# Update Index
brew update

# Upgrade Packages
brew upgrade
```

### 3.2 : Packages from Homebrew

The reason we are using Homebrew:

1. Package consistency between members regardless of OS and machine.
2. It is the goto for MacOS users but is available to everyone.
3. GCC 12 is most consistently available from Homebrew.

Here are the packages you need to install depending on your setup. For linux :

```sh
# WSL (Windows)
brew install gcc gdb llvm cmake

# MacOS
brew install curl wget gcc gdb llvm cmake

# Linux
# Replace `apt` with your distros package manager.
sudo apt update
sudo apt upgrade -y
sudo apt install git curl wget ca-certificates build-essential
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew update
brew upgrade
brew install gcc gdb llvm cmake
```

You can verify that GCC installed the correct version by running the following command. The output should be similar to this.

```sh
$ gcc-12 -v
Reading specs from /home/linuxbrew/.linuxbrew/Cellar/gcc/12.2.0/bin/../lib/gcc/current/gcc/x86_64-pc-linux-gnu/12/specs
COLLECT_GCC=gcc-12
.
.
.
gcc version 12.2.0 (Homebrew GCC 12.2.0)
```

### 3.3 : Installing Git (MacOS only)

In the last couple tasks Linux and WSL users have installed Git however, Git is a bit awkward on MacOS. To check if Git is already installed run.

```sh
git --version
```

If it says something like command cannot be found, this is ok. If it prompts you to install Git, follow the on-screen instructions. Once finished, run the above command and you should get.

```sh
git --version
git version 2.25.1
```

If it didn't prompt you, you can install it with Homebrew.

```sh
$ brew install git
$ git --version
git version 2.25.1
```

### 3.4 : Authenticating Git

Now that any machine you could be working on has Git, we can authenticate its use with GitHub with a few simple commands. Replace the `<>` with your GitHub credentials from earlier

```sh
git config --global user.name "<github-username>"
git config --global user.email "<github-email>"
```

---

## Links

- [Previous Page : WSL](/content/week0/tasks/wsl.md)
- [Next Page : bpt](/content/week0/tasks/bpt.md)
- [Content](/content/README.md)
- [HOME](/README.md)
