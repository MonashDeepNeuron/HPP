# Parallel Algorithms

## Contents

- [Parallel Algorithms](#parallel-algorithms)
  - [Contents](#contents)
  - [Task 1](#task-1)
    - [Task 1.1 : Execution Policies](#task-11--execution-policies)
    - [Task 1.2 : Alternative Algorithms](#task-12--alternative-algorithms)
      - [Task 1.2.1 : Reduce](#task-121--reduce)
      - [Task 1.2.2 : Exclusive Scan](#task-122--exclusive-scan)
      - [Task 1.2.3 : Inclusive Scan](#task-123--inclusive-scan)
      - [Task 1.2.4 : Transform Reduce](#task-124--transform-reduce)
      - [Task 1.2.5 : Transform Exclusive Scan](#task-125--transform-exclusive-scan)
      - [Task 1.2.6 : Transform Inclusive Scan](#task-126--transform-inclusive-scan)
  - [Links](#links)

## Task 1

### Task 1.1 : Execution Policies

The most basic parallelism comes from the algorithms library. Since C++17 almost all of the algorithms (iterator-based not range-based) in the standard library feature an overload that allows for the algorithm to potentially perform in parallel. These overloads accepts as their first arguments an execution policy. This is an object that represent the level of freedom an algorithms implementation has to try and parallelize its operation. Execution policies are found in the `<execution>` header under the `std::execution` namespace. Execution policies are suggestions, they indicate that a algorithm may be able to be parallelized. How the parallelism is achieve is up to the implementation and requires a parallelism backend library that the implementations will use. The most common is Intel's Thread Building Blocks (TBB) library. Using parallel overloads does require some due-diligence from the programmer to not create deadlocks or data races. The parallel algorithms will not automatically stop these from happening.

|       Execution Policy      |                                                                                                                                                           Description                                                                                                                                                           |
|:---------------------------:|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
|    `std::execution::seq`    |                                                                                  Forbids an algorithm from being parallelized. Invocations of element access functions within the algorithm are indeterminately sequenced in the calling thread                                                                                 |
|    `std::execution::par`    | Specifies that an algorithm can be parallelized. Invocations of element access functions within the algorithm are permitted to execute in the working thread or in a thread implicitly created by the underlying parallel library. Invocations executing in the same thread are indeterminately sequenced in the calling thread |
|   `std::execution::unseq`   |                                                                                                 Specifies that an algorithm can be vectorized such that a single thread using instructions that operate on multiple data items.                                                                                                 |
| `std::execution::par_unseq` |                 Specifies that an algorithm can be parallelized, vectorized or migrated across threads. Invocations of element access functions within the algorithm are permitted to execute in unordered fashion in unspecified threads and can be un-sequenced with respect to one another within each thread.                |

[Execution Policies : cppreference](https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag_t)

### Task 1.2 : Alternative Algorithms

There are a few algorithms in C++ that did not get parallel overloads. Namely a few of the numerical reductions. This is because reduction algorithms typically use binary operators in order to combine elements. The issue with this is not all binary operators are commutative or associative. This can cause problems when making an algorithm work in parallel because the order of operations can affect the result of the reduction. C++ regular reduction algorithms apply their operations in-order meaning that the commutative and associative properties of the binary operator do not matter. For parallel algorithms, commutativity and associativity must be assumed of the binary operator so that operations can be out-of-order.

#### Task 1.2.1 : Reduce

`std::reduce` 

#### Task 1.2.2 : Exclusive Scan

#### Task 1.2.3 : Inclusive Scan

#### Task 1.2.4 : Transform Reduce

#### Task 1.2.5 : Transform Exclusive Scan

#### Task 1.2.6 : Transform Inclusive Scan

## Links

- [Previous Page : Part 7](/content/part7/README.md)
- [Next Page : Atomics](/content/part7/tasks/atomics.md)
- [Content](/content/README.md)
- [HOME](/README.md)
