# Arduino PString Library

[![Build Status](https://travis-ci.org/boseji/PString-Arduino-lib.svg?branch=master)](https://travis-ci.org/boseji/PString-Arduino-lib)

**`PString`** *("Print-to-String")* is a new lightweight Print-derivative
string class that renders text into a character buffer.
With ***PStrings***, you can use the Print renderer for any device,
even those that do not directly support Print-style text formatting,
by first "printing" to a string.

For Better documentation Refer to :

<http://arduiniana.org/libraries/pstring/>

This is the 3rd Version of the library

## Attribution

This library has been created by [Mikal Hart](http://arduiniana.org/about/).

This is only a github-fork of the project.

It is being improved upon, here by [@boseji](https://github.com/boseji) .

## Description

**`PString`** *("Print-to-String")* is a new lightweight Print-derivative
string class that renders text into a character buffer.
With ***PStrings***, you can use the Print renderer for any device,
even those that do not directly support Print-style text formatting,
by first "printing" to a string.

In its simplest use case, you deploy an “on-the-fly” constructor to format text:

```c++
    char buffer[30];
    #define pi 3.14159
    PString(buffer, sizeof(buffer), pi);
```

This code uses Print’s float rendering functions to generate
the string equivalent of `pi` into buffer.

Since **`PString`** inherits from `Print`, **`PString`** objects
can do everything that other Print-derived classes do:

```c++
    char buffer[50];
    PString mystring(buffer, sizeof(buffer));
    char name[] = "Joe";
    int age = 45;

    mystring.print("Hi, my name is ");
    mystring.print(name);
    mystring.print(" and I am ");
    mystring.print(age);
    mystring.println(" years old.");
```

This generates the expected sentence in buffer the same as
if you had printed to the Serial port.

### Other member functions

**`PString`** is a fairly minimal string class.
It can report its length and capacity and give const access
to its internal string buffer:

```c++
    Serial.print(str.length());
    Serial.print(str.capacity());
    Serial.print(str);
```

You can reuse a string by calling its `begin()` function.
This effectively resets the position in the buffer where
the next printed text will go:

```c++
    str.print("Hello");
    str.begin();
    str.print("World");
    // str contains "World" here
```

### Operators

**`PString`** provides three operators for assignment, concatenation,
and equivalency test:

```c++
    char buffer[20];
    PString str(buffer, sizeof(buffer));
    str = "Yin"; // assignment
    str += " Yang"; // concatenation
    if (str == "Yin Yang") // comparison
    {
      Serial.println("They are equal!");
    }
```

### Runtime safety

***PStrings*** do not “own” their own buffers.
Instead, they rely on **pre-allocated static buffers**
that are passed in at the point of construction.
***PStrings never allocate memory dynamically***,
even when the result of a `print()`, assignment, or concatenation
operation would seem to exceed the current buffer’s size.
*In these cases, the excess data is simply discarded and*
*the string correctly terminated.*

Because of these constraints, ***PStrings*** can make three key guarantees:

>
> **1. They will never cause a buffer overflow**
>
> **2. A string’s buffer will always be valid memory, i.e. the original buffer**
>
> **3. buffers will always contain valid (i.e. NULL-terminated) C string data.**
>

## Download

### Original Works

The **Original version** of **`PString`** is [PString3.zip](http://arduiniana.org/PString/PString3.zip).

### Current Library version Download

<https://github.com/boseji/PString-Arduino-lib/archive/master.zip>

## Revision History

Version 1 – initial release

Version 2 – include support for inline renderings with modifiers HEX, OCT, etc.
(and eventually float precision)

Version 3 – Arduino 1.0 compatibility

V3.0.1 - Modifications to advance Hex printing functions

V3.0.2 - Adding CI/CD build verification

## Resource Consumption

**`PString`** objects consume 8 bytes of memory during their lifetimes.
Depending on what features are used, including the **`PString`** library
usually adds only `100-600 bytes` to a *program’s size*.

> *[All input is appreciated](http://arduiniana.org/libraries/pstring/).*
>
> [Mikal Hart](http://arduiniana.org/about/)
