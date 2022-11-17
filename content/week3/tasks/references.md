# References

## Contents

- [References](#references)
  - [Contents](#contents)
  - [Task 2](#task-2)
    - [Task 2.1 : Dereferencing nullptr](#task-21--dereferencing-nullptr)
    - [Task 2.2 : Syntax](#task-22--syntax)
    - [Task 2.3 : const qualifications](#task-23--const-qualifications)
    - [Task 2.4 : Move and Copy Semantics](#task-24--move-and-copy-semantics)
    - [Task 2.n : Pointers vs References](#task-2n--pointers-vs-references)
  - [Links](#links)

## Task 2

### Task 2.1 : Dereferencing nullptr

In C++, any assignment and initialisation is is copy by default. Pointers are really useful for referring to very large amounts of data that would be expensive to copy however, there are caveats to them.

Pointers can point to nothing. This nothing value is actually the literal `nullptr` we saw in week 0.

```cxx
#include <iostream>

auto main () -> int
{
    int* p {nullptr};

    return 0;
}
```

### Task 2.2 : Syntax

### Task 2.3 : const qualifications

### Task 2.4 : Move and Copy Semantics

### Task 2.n : Pointers vs References

## Links

- [Previous Page : Pointers](/content/week3/tasks/pointers.md)
- [Next Page : Slices](/content/week3/tasks/slices.md)
- [Content](/content/README.md)
- [HOME](/README.md)
