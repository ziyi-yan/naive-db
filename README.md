# Naive Database

A simple database in C++ based on https://cstack.github.io/db_tutorial/.

I followed the tutorial from part 1 to part 5 and use C++ to re-implement it and incorporate a open-sourced third-party library [abseil](http://abseil.io) for better string manipulations.

The program can store user input data into memory and list them. When program exited under proper instruction, it will
persist the data into disk via file I/O. If you use the same file to re-start the program, you will find that the previous
input data are already loaded into memory to read.

All your input should have three attributes, first one should be a non-negative integer. Second one is a string can contains 32 characters
, you can use it as username field. The last one is also a string which can contains 255 characters, you can put your email address in this field.

## Supported SQL Syntax
Insert statement should be start with `insert` keyword followed by three attributes: id, username, email. For example,
```
db > insert 1 ziyi ziyi.yan@foxmail.com
Executed.
```
List your input is very easy. Just type `select` and you will get all you data
```
db > select
(1, ziyi, ziyi.yan@foxmail.com)
```
For gracefully shutdown, type `.exit`.

## Building & Running

- cmake
- compiler support c++17

Under the project root directory, run
```
$ mkdir build && cd build
$ cmake ..
$ make
$ # run the naive-db with a local filename as its first parameter
$ ./naive-db mydb.db
db > insert 1 ziyi ziyi.yan@foxmail.com
Executed.
db > insert 2 foo foo.bar@baz.com
Executed.
db > select
(1, ziyi, ziyi.yan@foxmail.com)
(2, foo, foo.bar@baz.com)
Executed.
db > .exit
$ # program will exit gracefully here
$ # run the command again to check the persistent data in mydb.db file
$ ./naive-db mydb.db
db > select
(1, ziyi, ziyi.yan@foxmail.com)
(2, foo, foo.bar@baz.com)
Executed.
```

## Testing
First, you need to install [ruby](http://www.ruby-lang.org).

Under the project root directory, run
```
$ gem install bundle
$ bundle install
$ # run the tests in spec/ directory
$ bundle exec rspec
```

## Implemented Rubric Points

- Loops, Functions, I/O
    - Implemented a read-eval-print loop (REPL) for simple SQL (src/main.cc#L33)
    - Save user's input to memory and persist it to disk via file I/O (src/Pager.cpp#L11)
- Object Oriented Programming
    - Use `Statement`, `Executor`, `Table`, `Row`, `Pager` objects to construct the program in a modular way (src/*.cpp files naming after these class names)
    - Utilize initialization list to initialize `pager_` member in `Table` object (src/Table.cpp#L11)
- Memory Management
    - `Table` destructor handle gracefully persistence operation on `Pager` (src/Table.cpp#L16)
    - `Pager` cleanup all the allocated memory for user input's rows (src/Pager.cpp#L64)
