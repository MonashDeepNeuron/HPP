# The C++ Type System

## Strong vs Weak Typing

In [1.3 Hello World](../chapter1/helloworld.md) we discussed a bit about C++'s types system. But what is a type system? A type system is a formal notion of which terms have which properties. The rules and constructs of a type system underpin the meaning help by any discourse written in any and all programming languages. Without a type system, programming languages cannot construct grammar or structure and thus cannot become coherent and cohesive expressions of language.

This is all a bit abstract and delves into [Type Theory](https://en.wikipedia.org/wiki/Type_theory) which is a more formal, mathematical notion of types. For our purposes we will just look at what C++'s type system does.

First and foremost, C++ is considered by many (but not universally) to be a strongly typed language. There isn't a universal definition of a strong or weak types but the basic premise is based around the question:

> Does the type system allow implicit conversions between type?

In the case of C++, 90% of types have no implicit conversions. The only contradiction to this is type promotion or narrowing, this is when types of the same _kind_ get promoted or narrowed to a similar yet different type. This occurs for some type in C++ because the bit width, layout and structure are so similar; due to how memory in computers work, that some types will implicitly meet the requirements of of another type. While this can occur in C++, it is limited to only a handful of primitive _data types_. Weaker typing allows for this implicit conversions to happen more frequently (think JavaScript's type system).

## Static vs Dynamic Type Systems

So what about static and dynamic typing? These characterisations refer to the type checking techniques used in a language and how a language expresses the notion of types. These are the two key ways to look at either static or dynamic typing.

In a dynamically typed language, the type of an object does not have to be explicitly stated, but is inferred at runtime based on its contexts and the surrounding expressions. Python is a good example of this as you can create an object and assign it a type without ever declaring what type the object should be. This allows interpreters to forego type checking until a particular operation is performed on an object which may or may not fail. In a statically typed language, this is the opposite. You must formally declare the type of an object and i must be known to the system before the program ever runs. Most often, it must be known at compile time. However, some languages can forego an explicit **notation** of an object type and allow the compiler to infer the type. C++ and many other compiled languages; like Rust, are capable of type inference using various **argument deduction** techniques.

## A Pinch of Type Theory

Before we move on, there a some important definitions that are good to know going forward.

- Literals - A literal is a constant that refers to a determined value. For example, the character for 'three', `3`, has the value of three.
- Values - A value is the independent data of a type. Think of it as an instance or object.
- Types - A type is the formal definition and classification of values that is exhibit particular properties related properties. Examples of types include primitive data; like `int` from Python, as well as user defined types, often called classes in many languages. In C++ types are created using the `struct` and `class` keywords.
- Typeclasses - A typeclass is a polymorphic type constraint. It defines the expected properties of a type including methods, functions and patterns. In C++ typeclasses are created using the `concept` keyword.
- Kinds - A kind is, well; to put it bluntly, a type of a type. It describes the type of a nullary type constructor, ie. the constructor of primitive data-types which take no parameters. What this basically means is something that can hold a value.

In C++ supports everything except Kinds. We will go more into a little more depth during Chapter 5.
