 zz-cci
==========

My solutions to the problems from this
[book](https://www.amazon.co.uk/Cracking-Coding-Interview-Programming-Questions/dp/098478280X)
implemented in modern C++ (up to C++17).

## Overview
-----------

I started this project because I wanted to:
  * practice competitive programming
  * see how modern C++ can be leveraged in solving tricky algorithmic problems
    (in the past I always used C for this kind of programming)
  * learn how to approach such problems in a more pragmatic fashion (e.g. use
    unit testing to verify my solutions)

Although the main goal was to implement solutions that meet the requirements in
the problem specifications, I also wanted to experiment a bit. As a result I
implemented some data structures (e.g. a linked list) that are also available
in the Standard Template Library. This was a learning exercise for me. This way
I could compare solutions leveraging STL with solutions based on my own,
simplified implementation of the corresponding containers. For this reason this
repository contains more code than it's actually required to solve the
underlying puzzles.

This repository also contains an extensive suite of unit
tests implemented using [Google Test](https://github.com/abseil/googletest).
They are very helpful in:
  * documenting the assumptions that I made about the problems
  * verifying that my implementations satisfy those assumptions
  * maintaining and expanding this repository
The following revision of Google Test was used during the development:
```
commit cc9dcc54129bafebaeb8e9ffa619bffb71a08474 (HEAD -> master, origin/master, origin/HEAD)
Merge: b9347b3 39de88c
Author: Gennadiy Civil <gennadiycivil@users.noreply.github.com>
Date:   Tue Oct 30 09:34:35 2018 -0400

    Merge pull request #1945 from akonradi/optional-matcher-doc
    
    Add Optional() to the cheat sheet doc.
```
Although any updates to Google Test are highly unlikely to break the build,
please use the revision when debugging.

## Status
--------
**WORK-IN-PROGRESS**

## Build instructions
-------------------
**zz-cci** supports Windows and Linux. 

## Build
Because I'm a Linux user, the build instructions are 

It is assumed that **zz-cci** will be built in `<build-dir>` and that the
top-level source code directory is `<source-dir>`. 

First, you will need to clone Google Test inside `<source-dir>`:
```
$ cd <source_dir>
$ git clone https://github.com/abseil/googletest.git
$ git checkout cc9dcc54129bafebaeb8e9ffa619bffb71a08474
```

Next, you can build as follows:
```
$ cd <build_dir>
$ cmake <source_dir>
$ make
```
Of course you can change the `CMake` generator and build type as you please.

Final notes
-------------
Last, but not least, please fell free to fork and re-use this repository - I
will be extremely happy if anyone finds my implementations helpful! However,
bear in mind the best way to learn is to practice (i.e. code) yourself ;-)
