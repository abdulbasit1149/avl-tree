Name: Abdul Basit 
Student ID: 0930431
Date: Monday November 28, 2016
Assignment Number: #4

**************************************************************************************************************
Notes:
	The height of a leaf node is zero (0), so the height of the entire tree with the keys from the file will be 12
	The testing file called "data.txt" is provided to test the program

**************************************************************************************************************
References:	
	[1] - References: c07-f16-notes

**************************************************************************************************************
Compilation:

To compile the program, you need to type 'make' in the terminal. Which will compile the source code into two executable file

Example:

$ make

gcc -c -Wall -pedantic -std=c99 avltree.c
gcc -c -Wall -pedantic -std=c99 tree.c
gcc -Wall -pedantic -std=c99 avltree.o tree.o -o avltree

./avltree

*************************************************************************************************************
How to run:

-To start the program type: "./avltree"

**************************************************************************************************************
Output: 

Menu
-----
(1) Initialization
(2) Find
(3) Insert
(4) Remove
(5) Check Height and Size
(6) Find All (above a given frequency)
(7) Exit
avl/> 2
find key: flr830

key: flr830 frequency: 414

**************************************************************************************************************
Limitation:
	-The binary search tree use strmp() to ordered the keys, so entering different combinations of letter could
	confuse the order
