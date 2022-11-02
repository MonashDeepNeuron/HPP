# `hello-bpt` - A Great New Project

A 'hello world' program using bpt.

---

## Install bpt

The following are the commands to install bpt on your system.

### Download

#### MacOS or Linux

```sh
# MacOS
curl bpt.pizza/get/macos -Lo bpt

# Linux
curl bpt.pizza/get/linux -Lo bpt

# Both
chmod a+x bpt
```

#### Windows

```ps
Invoke-WebRequest bpt.pizza/get/windows -OutFile bpt.exe
```

### Install

```sh
./bpt install-yourself
```

If bpt reports that you `PATH` has been modified, you'll have to restart your terminal.

---

## Build

```sh
bpt build -t :c++20:gcc-11 -j 4 -o build
```

## Run

```sh
./build/hello
```
