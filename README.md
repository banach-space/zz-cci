 zz-cci
==========
[![Build Status](https://travis-ci.org/banach-space/zz-cci.svg?branch=master)](https://travis-ci.org/banach-space/zz-cci)
[![Build status](https://ci.appveyor.com/api/projects/status/f5d0f2hqc9jxa5ny/branch/master?svg=true)](https://ci.appveyor.com/project/banach-space/zz-cci/branch/master)


My solutions to the problems from this
[book](https://www.amazon.co.uk/Cracking-Coding-Interview-Programming-Questions/dp/098478280X)
implemented in modern C++17.

## Overview

I started this project because I wanted to:
  * practice competitive programming
  * see how modern C++ can be leveraged to solve tricky algorithmic problems
    (in the past I had used C for this kind of programming)
  * learn how to approach such problems in a more pragmatic way (e.g. use
    unit tests to define and verify my assumptions)

Although my main goal was to implement solutions that meet the requirements
from the problems' specifications, I also wanted to experiment a bit. As a
result I implemented multiple data structures (e.g. a doubly linked list), some
of which are also available in the Standard Template Library. This was a
learning exercise that enabled me to compare solutions leveraging STL with
solutions based on my own, simplified implementation of the corresponding
containers. For this reason this repository contains more code than is required
to solve the underlying puzzles.

This repository also contains an extensive suite of unit
tests implemented using [Google Test](https://github.com/abseil/googletest).
These were very helpful in:
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
please use the above revision when debugging.

## Status
Chapters 1-5 are now complete. The remaining chapters contain more generic
questions that focus on testing IQ and generic software skills. I may revisit
them in the future.

## Build instructions
**zz-cci** supports Windows and Linux. It should also work on Mac OS, but I
haven't had the time to tweak my CI to verify that.

## Build 
Because I'm a Linux user, the following build instructions are for Linux.
However, porting this to Windows should be rather straightforward (and I do
test it in my CI).

I assume that **zz-cci** will be built in `<build-dir>` and that the
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
Of course you can change the `CMake` generator and the build type
(`Release\Debug` etc) as required.  Once built, you can run the binary
implementing all the unit tests, `cciUT`. In the CI that I set-up all tests are
green.

## Final notes
Last, but not least, please fell free to fork and re-use this repository - I
will be very happy if anyone finds my implementations helpful! However,
bear in mind the best way to learn is to practice (i.e. code) yourself ;-)
