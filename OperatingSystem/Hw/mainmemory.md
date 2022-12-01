## 8.3
First fit

212 K is put in 500 K partition.

417 K is put in 600 K partition.

112 K is put in 288 K partition. (New partition 288 K = 500 K - 212 K)

426 K must wait.

Best-fit

212 K is put in 300 K partition.

417 K is put in 500 K partition.

112 K is put in 200 K partition.

426 K is put in 600 K partition.

Worst-fit

212 K is put in 600 K partition.

417 K is put in 500 K partition.

112 K is put in 388 K partition. (600 K - 212 K)

426 K must wait.

In this example Best-fit is the best solution.

## 8.4

Contiguous memory allocation may require relocation of the whole program when there is not enough space in the allocated memory space.
Pure segmentation also may require relocation of the segment if the segment cannot grow in the allocated memory space.
Pure paging is the best scheme in this case as allocation of pages(non-contiguous) is possible without relocation.

## 8.9

a. 400 nanoseconds; 200 nanoseconds to access the page table and 200 nanoseconds to access the word in memory.
b. Effective access time= 0.75 * (200 nanoseconds) + 0.25 * ( 400 nanoseconds ) = 250 nanoseconds
