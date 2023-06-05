SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++17
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lz -lncurses -rdynamic
LIBS = `$(LLVMCONFIG) --libs`

.PHONY: all clean

all: compiler

clean:
	$(RM) -rf parser.cpp parser.hpp parser tokens.cpp $(OBJS) compiler

parser.cpp: parser.y
	bison -d -o $@ $^
	
parser.hpp: parser.cpp

tokens.cpp: tokens.l parser.hpp
	flex -o $@ $^

%.o: %.cpp
	clang++ -g -c $(CPPFLAGS) -o $@ $<

compiler: $(OBJS)
	clang++ -g -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

test: compiler example.txt
	cat example.txt | ./compiler
