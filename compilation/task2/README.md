# Task 1
1) Compile a shared library (.so file) and a program that dynamicly loads it.

The shared library consists of:
- print_time.cpp
- timestamp.cpp

The program:
- main.cpp
- loads the shared library

2) Execute the compiled binary. You might also need to do a few steps here.

3) Study the compiled binary with `ldd` and notice that it depends on the library.
Study the shared libarary and find exported functions `getPosixTimeSec` and `printTime`.
Find their assembly code with `objdump`.

# Solution

```shell

# Compile object files -Wall: enable base warnings. -Werror make all warnings into errors
# -fpic - compile into position independent code
g++ -c -Wall -Werror -fpic timestamp.cpp print_time.cpp 

g++ -shared -o libtime.so timestamp.o print_time.o

# -L providing path to our shared library
# -l linking our shared library with name libtime.so to our executable
g++ -L/home/.../.../libtime.so -Wall -o test main.cpp -ltime

# Providing path to our library for OS loader, also we can use rpaths
export $LD_LIBRARY_PATH=/home/.../.../libtime.so:$LD_LIBRARY_PATH

./test
```