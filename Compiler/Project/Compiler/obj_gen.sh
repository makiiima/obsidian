cd ./build
./Compiler 
cd ..
llvm-as-14 test.ll 
llc-14 test.bc 
clang-14 -c test.s
clang-14 test.o -o test1 -no-pie 
./test1


