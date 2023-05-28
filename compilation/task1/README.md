# Task 1
Compile a program (using g++ or clang++) that consists of three translation units (three .cpp files) and execute it. The program prints current local time, which is handy.

The program will consists of source files:
- main.cpp
- print_time.cpp
- timestamp.cpp

Note: indeed there's no CMake for this task, as you need to do building manually.

# Solution

```shell
g++/clang++ -o ProgramName main.cpp print_time.cpp timestamp.cpp
```


# Task 2
The task is to build a program with use of a static library.

Static library 1:
- print_time.cpp
- timestamp.cpp

Program:
- main.cpp
- static library 1

# Solution

```shell
g++/clang++ -c filename_1 filename_2 ... filename_n

ar rs libraryName.a object_file_1 object_file_2 ... object_file_n

g++/clang++ -o ProgramName filename_1 filename_2 ... filename_3 ... libraryname_1 ... libraryname_n
```

# Task 3
Build a program with use of two static libraries.

Static library 1:
- timestamp.cpp

Static library 2:
- print_time.cpp

Program:
- main.cpp
- static library 1
- static library 2

```shell
g++/clang++ -c timestamp.cpp printTime.cpp

ar rs timestamp.a timestamp.o
ar rs printTime.a printTime.o

g++/clang++ -o task1_3 main.cpp timestamp.a printTime.a
```
