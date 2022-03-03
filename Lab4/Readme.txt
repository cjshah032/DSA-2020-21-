The program follows a sequential include path due to the use of global variable "heapMemory" in myheap.c
For proper execution, please compile in the steps given below:
1. gcc -c myheap.c
2. gcc -c linkedlist.c
3. gcc -c cycle1.c
4. gcc -c main.c
5. gcc -o test myheap.o linkedlist.o cycle1.o main.o
6. ./test.exe

The excel file is named Data Analysis.xlsx. It contains 5 data with N value 10^6, 2*10^6, 3*10^6, 10^7, and 5*10^7.
The gprof function specifics for the above are stored in T1.txt, T2.txt, T3.txt, T10.txt, T50.txt respectively.

Exercise 5 is not included in the zip folder. The cycle2.c is also not included.

