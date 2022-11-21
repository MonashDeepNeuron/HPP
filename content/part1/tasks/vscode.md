# VSCode

VSCode is a text editor with rich extension ecosystem allowing developers to customize a developer environment to their needs.

## Contents

- [VSCode](#vscode)
  - [Contents](#contents)
  - [Note](#note)
  - [Task 5](#task-5)
    - [5.1 : Installing VSCode](#51--installing-vscode)
      - [Note (WSL)](#note-wsl)
    - [5.2 : WSL Extensions](#52--wsl-extensions)
    - [5.3 : General Extensions](#53--general-extensions)
  - [Links](#links)

## Note

> We will be using VSCode throughout this series and as such, all debugging examples will be in reference to VSCode but you are free to use any text editor you want and we will do our best to adjust.

## Task 5

### 5.1 : Installing VSCode

Go to [VSCode's Download page](https://code.visualstudio.com/download) and install it for your host OS.

#### Note (WSL)

> For Windows/WSL users, this means install on the Windows side.

### 5.2 : WSL Extensions

On its own VSCode is just a text editor like Notepad but with colour text however, using extensions we can set it up nicely for developing with C++.

For WSL users, you need to install some extensions on the Windows installation of VSCode in order for VSCode to access the correct permissions. MacOS and Linux users, you can skip to [4.3](#43--general-extensions).

Open VSCode how you would any other app in Windows. In VSCode, open the extension marketplace tab. In the search bar, search for the following extensions click on the extension and click and click the install button for them.

- Remote development
- WSL
- Remote SSH

You can now close VSCode and continue.

### 5.3 : General Extensions

To open VSCode from the terminal, open a new terminal window and type.

```sh
# `.` represents 'this' directory
code .
```

This will open VSCode in the current user directory which should be `~` which represents your users home directory. WSL users, make sure to launch VSCode from your WSL terminal this time so the extensions install on you WSL platform.

In VSCode, open the extension marketplace tab. In the search bar, search for the following extensions click on the extension and click and click the install button for them.

- C/C++
- GitLens
- Git Graph
- GitHub Pull Requests and Issues
- Sonarlint
- markdownlint
- Markdown All In One
- Markdown Preview GitHub Styling

You may have to restart VSCode for the extensions to load. Finally, press `ctrl + ,` to open settings. in the search bar search for "cpp default standard". In the drop down select `c++20`.

And that is it, everything should be set up and ready to go. You next task is to run your first C++ code.

## Links

- [Previous Page : bpt](/content/part1/tasks/bpt.md)
- [Next Page : Hello World](/content/part1/tasks/helloworld.md)
- [Content](/content/README.md)
- [HOME](/README.md)
