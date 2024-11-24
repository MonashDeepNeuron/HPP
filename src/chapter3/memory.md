# Dynamic Memory

C++ gives us precise control of how memory is used. This allows programs to be highly optimised and control the amount of overhead a program has but means that memory must be managed by manually.

## Stack vs Heap

In almost all computers there are two kinds of memory resource pools. The first kind, which we have been using exclusively so far is called the stack. Stack memory is the local memory resources that the computers OS is willing give the program when it runs. However, the stack is limited in size and it is very easy to use up all of the stacks available memory very quickly.

This is where the second memory resource pool comes in called the heap or the free store. The heap is a much larger pool of memory programs can access and utilise but there is a catch to its use. You must go through the operating system each time you want memory from the heap. You are also responsible for returning ownership of that memory to the OS when you are done.

## `new` and `delete`

So, how do we get memory from the heap. This is done with a `new` expression. `new` is a keyword that invokes the OS's memory resource allocator giving you access to memory from the OS. `new` returns a pointer of the allocated resources type. You can use this pointer however you need to like any other pointer but, after you have finished using the memory resource you must relinquish ownership of it using `delete` on the pointer holding the resource. Not doing so will cause a memory leak.

```cxx
#include <iostream>

auto main () -> int
{
    int* ip = new int(7);   ///< Creates an `int` initialised with the value `7` on the heap

    std::cout << "ip = " << ip << std::endl;
    std::cout << "*ip = " << *ip << std::endl;

    delete ip;
    ip = nullptr;

    return 0;
}
```

[Example](https://www.godbolt.org/z/v13hfhM54)

## Dynamic Slices

You can also allocate slices using `new[]` expressions and deallocate with `delete[]`.

```cxx
#include <iostream>

void print(int arr[], std::size_t s)
{
    std::cout << "[ ";
    for (auto i {0}; i < s; ++i)
        std::cout << arr[i] << ", ";
    std::cout << "]" << std::endl;
}

auto main () -> int
{
    int* nums = new int[]{ 1, 2, 3, 4, 5 }; ///< Creates a slice of `int` initialised with brace list

    print(nums, 5);

    delete[] nums;
    nums = nullptr;

    return 0;
}
```

[Example](https://www.godbolt.org/z/fx7136qnv)

## Forewarning on Dynamic Memory Management

Dynamic memory management is hard to get right and very easy to get wrong. Memory leaks occur and cause dramatic problems for critical systems and slow a program and even an entire computer to a grinding halt. Avoid using raw `new` and `delete` expressions in anything beyond trivial programs or unless you know what you are doing. In chapter 5 we will look at various principles that will assists in resource usage; including memory, to ensure C++ program are safe. That being said, have a toy with `new` and `delete` now to get an idea of how they work.
