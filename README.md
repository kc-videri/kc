# kc

This is a collection of classes, structure and functions which can be useful

## Working with it
### Compile
Tested with gcc-6 and automake 1.15 on Debian SID

run:
```
./autogen.sh
make
```
### Run
There are some test application in the test folder

### Work with KC
First you have to install the compiled libraries using 
```
make install
```
or compile the libraries static in the application. 

For a web application add the following lines into your Makefile
```
CFLAGS+=-I <your folder>/kc/source/include
LIBS=-lfcgi -Wl,-Bstatic -lkcweb -lkc -L<your folder>kc/source/src/.libs -Wl,-Bdynamic
```

## TODO or missing things
* get kcweb to work completely
* string operations
* lists
* packages for Debian and RedHat (OpenSuse)
* get to work on Windows, Android and Mac

## DONE
*
