# Quiz 05

## Memory management in C

Implement an integer vector struct in C, similar to `std::vector` of C++. The required functions are

```C
typedef struct Vector{
	void* data;
	int size;
	int capacity;
	int elemSize;
}Vector;

/* Constructs a Vector struct `v`.
 * Returns 0 upon success
 * and -1 upon failure. */
int vector_init(Vector* vec, int elemSize);

/* Destroys a Vector struct `vec`. */
void vector_destroy(Vector* vec);

/* Appends the given element
 * `value` to the end of the
 * Vector `vec`. Returns 0 upon
 * success and -1 upon failure. */
int vector_push_back(Vector* vec, void* value);

/* Removes the last element of the
 * Vector `vec`. Its value is stored
 * in `out`. Returns 0 upon success
 * and -1 upon failure. */
int vector_pop(Vector* vec, void* out);

/* Erases the element of the `index`-th entry
 * of Vector `vec`. Returns 0 upon success
 * and -1 upon failure. */
int vector_remove(Vector* vec, int index);
```

https://en.cppreference.com/w/cpp/container/vector

## Resources limit in shell

Add a shell function called `spawner(memoryInKB, timeoutInSec, binaryName)` that runs `binaryName` until `timeoutInSec` or `memoryInKB` limit reached. If so, exit gracefully. Make sure to add proper error checking for
1. number of arguments passed to `spawner()`
2. binary’s existence and
3. exec flag .

The CodeRunner expected non-0 error codes are:

`exit 1;` memory limit reached

`exit 2;` issue with passed arguments

`exit 3;` binaryName doesn't exist

`exit 4;` binaryName doesn't have `+x` flag

`exit 5;` timeout

Make sure to exit gracefully upon any of the conditions reached.

## Makefiles, shared libraries and unit-tests.


You are provided with the following source files: `runner.c`, `test_runner.c` and `libdummy.c`. You can download them from here [1]. On the course's Linux box, create a folder under your home directory named `quiz-5`, e.g. `/home/deadpool/quiz-5` and extract the contects of the file `quiz-5-source-tar.gz` obtained from [1]. It should include the three mentioned files. You can safely delete the tarbal after extraction.

Your task is to write a Makefile that has three recipes:
1. `make runner` which compiles `runner.c` to `runner.out`.
1. `make test` which compiles `test_runner.c` and runs `test_runner.out` Keep in mind that both binaries require `libdummy.c` during runtime and to be linked.
1. `make clean` which cleans up everything created, i.e. `.out` and `.so`, restoring the original state of the folder.

Make sure you add the appropriate linking and compilation steps needed for `libdummy.c` to be available as a shared library (`.so`) and linked to both the other binaries.
In order to check your output, you should after running make runner your folder should containing the following files:

```
runner.out
libdummy.so
Makefile
test_runner.c
runner.c
libdummy.c
```

Running the command ldd runner.out should produce the following, i.e. meaning `runner.out` is linked to the shared library `libdummy.so`, apart from other system included libraries.

```
linux-vdso.so.1 (0x00007fffe4306000)
libdummy.so => ./libdummy.so (0x00007fe815dcf000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fe815bd1000)
/lib64/ld-linux-x86-64.so.2 (0x00007fe815ddb000)
```
Running make test should produce the following output on `std.out`.
```
./test_runner.out
Hello from the shared but dummy library!
All tests passed.
``````
And running `ldd test_runner.out`

```
linux-vdso.so.1 (0x00007fff7bd77000)
libdummy.so => ./libdummy.so (0x00007f4668dee000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f4668bf0000)
/lib64/ld-linux-x86-64.so.2 (0x00007f4668dfa000)
```
 By running make clean the directory should be restored in its original state, i.e. only the following files contained:
```
Makefile
test_runner.c
runner.c
libdummy.c
```
Important: In order to successfully submit the essay,
1. make sure your `/home/deadpool/quiz-5` folder contains your Makefile and
1. paste the same Makefile in the answer text box. There is no CodeRunner functionality, your answers will be graded on the lab's Linux box.

[1] https://github.com/vbassn/049-OS-Exercise5/raw/main/quiz-5-source.tar.gz