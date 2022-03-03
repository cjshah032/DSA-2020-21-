The file readFile.h and readFile.c contain the structure for "record" (Bank Account details) and the necessary function which reads from a file and stores it in an expandable array.
The files insertionSort.h and insertionSort.c contain the procedures and main method for exercise 2.
The executable can be made from the following sequence:

    gcc -c readFile.c
    gcc -c insertionSort.c
    gcc -o test insertionSort.o readFile.o

The output data (runtime and stack space comparisons and graphs) is stored in Output.xlsx. The first sheet is data for exercise 2.

For the insertion sort procedure, inputs larger than 15000 could not be processed due to memory shortage.

Observations:
1. Reading input is linear (O(n)).
2. Insertion sort is O(n*n) in time.
3. Insertion sort is O(n) in space.