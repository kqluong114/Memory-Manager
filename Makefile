CC=g++ -g -Wall -fno-builtin -std=c++17

UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
    CC+=-D_XOPEN_SOURCE
    LIBVMAPP=libvm_app_macos.o
    LIBVMPAGER=libvm_pager_macos.o
else
    LIBVMAPP=libvm_app.o
    LIBVMPAGER=libvm_pager.o
endif

# List of source files for your pager
PAGER_SOURCES=pager.cpp globals.cpp

# Generate the names of the pager's object files
PAGER_OBJS=${PAGER_SOURCES:.cpp=.o}

all: pager test1.4 test2.4 test3.4 test4.4 test5.4 test6.4 test7.4 test8.5 test9.4 test10.4 test11.4 test12.4 test13.4 test14.4 test15.4 test16.4 test17.4 test18.4 test19.4 test20.4 test21.4 test22.4 test23.4 test24.4 test25.4 test26.4

# Compile the pager and tag this compilation
pager: ${PAGER_OBJS} ${LIBVMPAGER}
	./autotag.sh push
	${CC} -o $@ $^

# Compile an application program
test1.4: test1.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test2.4: test2.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test3.4: test3.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test4.4: test4.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test5.4: test5.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test6.4: test6.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test7.4: test7.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test8.5: test8.5.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test9.4: test9.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test10.4: test10.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test11.4: test11.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test12.4: test12.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test13.4: test13.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test14.4: test14.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test15.4: test15.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test16.4: test16.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test17.4: test17.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test18.4: test18.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test19.4: test19.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test20.4: test20.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test21.4: test21.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test22.4: test22.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test23.4: test23.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test24.4: test24.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test25.4: test25.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl
test26.4: test26.4.cpp ${LIBVMAPP}
	${CC} -o $@ $^ -ldl

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $<
%.o: %.cc
	${CC} -c $<

clean:
	rm -f ${PAGER_OBJS} pager test1.4 test2.4 test3.4 test4.4 test5.4 test6.4 test7.4 test8.5 test9.4 test10.4 test11.4 test12.4 test13.4 test14.4 test15.4 test16.4 test17.4 test18.4 test19.4 test20.4 test21.4 test22.4 test23.4 test24.4 test25.4 test26.4
