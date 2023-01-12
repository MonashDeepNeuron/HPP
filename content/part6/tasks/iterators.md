# Iterators

## Contents

- [Iterators](#iterators)
  - [Contents](#contents)
  - [Task 1](#task-1)
    - [Task 1.1 : What is an iterator?](#task-11--what-is-an-iterator)
    - [Task 1.2 : Iterator Categories](#task-12--iterator-categories)
    - [Task 1.3 : Iterator Functionalities](#task-13--iterator-functionalities)
      - [Task 1.3.1 : Common Operator Interface](#task-131--common-operator-interface)
      - [Task 1.3.2 : Iterator Functions](#task-132--iterator-functions)
  - [Links](#links)

## Task 1

### Task 1.1 : What is an iterator?

An iterator is an abstraction for representing an item, element, value etc. in a collection or sequence of values that also has some notion how to get to a obtain or yield a new item from the sequence. In C++ iterators a lot like pointers in the sense that they hold some value, usually the location of it and has a means of either yielding the value for reading or allows for writing to that value.

### Task 1.2 : Iterator Categories

There are 6 main iterator categories considered in C++. Each subsequent iterator category builds upon the previous categories requirements with increasingly more requirements.

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-kuap{background-color:#34ff34;border-color:#000000;color:#000000;text-align:center;vertical-align:top}
.tg .tg-ayxq{background-color:#fe0000;border-color:#000000;color:#000000;text-align:center;vertical-align:top}
.tg .tg-wp8o{border-color:#000000;text-align:center;vertical-align:top}
.tg .tg-mqa1{border-color:#000000;font-weight:bold;text-align:center;vertical-align:top}
.tg .tg-jdzo{border-color:#000000;font-size:small;text-align:center;vertical-align:top}
.tg .tg-y7v3{background-color:#f8ff00;border-color:#000000;color:#000000;text-align:center;vertical-align:top}
</style>
<table class="tg">
<thead>
  <tr>
    <th class="tg-mqa1" rowspan="2">Iterator Category</th>
    <th class="tg-mqa1" colspan="7">Valid Operations</th>
  </tr>
  <tr>
    <th class="tg-wp8o">write</th>
    <th class="tg-wp8o">read</th>
    <th class="tg-wp8o">increment</th>
    <th class="tg-wp8o">multiple passes</th>
    <th class="tg-wp8o">decrement</th>
    <th class="tg-wp8o">random access</th>
    <th class="tg-wp8o">contiguous storage</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-jdzo">Output</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-ayxq"></td>
    <td class="tg-kuap">Required</td>
    <td class="tg-ayxq"></td>
    <td class="tg-ayxq"></td>
    <td class="tg-ayxq"></td>
    <td class="tg-ayxq"></td>
  </tr>
  <tr>
    <td class="tg-jdzo">Input</td>
    <td class="tg-y7v3">Only if mutable</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-ayxq"></td>
    <td class="tg-ayxq"></td>
    <td class="tg-ayxq"></td>
    <td class="tg-ayxq"></td>
  </tr>
  <tr>
    <td class="tg-jdzo">Forward<br>(Satisfies Input)</td>
    <td class="tg-ayxq"></td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-ayxq"></td>
    <td class="tg-ayxq"></td>
    <td class="tg-ayxq"></td>
  </tr>
  <tr>
    <td class="tg-jdzo">Bidirectional<br>(Satisfies Forward)</td>
    <td class="tg-ayxq"></td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-ayxq"></td>
    <td class="tg-ayxq"></td>
  </tr>
  <tr>
    <td class="tg-jdzo">Random Access<br>(Satisfies Bidirectional)</td>
    <td class="tg-ayxq"></td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-ayxq"></td>
  </tr>
  <tr>
    <td class="tg-jdzo">Contiguous<br>(Satisfies Random Access)</td>
    <td class="tg-ayxq"></td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
    <td class="tg-kuap">Required</td>
  </tr>
</tbody>
</table>

> Note: A pointer actually satisfies the Contiguous Iterator Category

### Task 1.3 : Iterator Functionalities

There are a few ways to interact with an iterator directly. One is to use the overloaded operators for the iterator object. Most iterators implement and overload the same operator set that are used by pointers. The other way is to use functions to interact with iterators, allowing for a more generic interface if a iterator doesn't support the common operator overload set and the implementer preferred to overload the functions.

#### Task 1.3.1 : Common Operator Interface



#### Task 1.3.2 : Iterator Functions

## Links

- [Previous Page : Part 6](/content/part6/README.md)
- [Next Page : Data Structures](/content/part6/tasks/data-structures.md)
- [Content](/content/README.md)
- [HOME](/README.md)
