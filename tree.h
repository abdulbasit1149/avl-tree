/*
Name: Abdul Basit 
Student ID: 0930431
Date: Monday November 28, 2016
Assignment Number: #4
*/

#ifndef __ABASIT__TREE__
#define __ABASIT__TREE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	[1] - References: c07-f16-notes
*/
typedef enum balanceFactor
{
	LeftTooHeavy = -2,
	LeftHeavy = -1,
	Balance = 0,
	RightHeavy = 1,
	RightTooHeavy = 2 
}balanceFactor;

typedef struct avl
{
	int count;
	char* key;
	balanceFactor bf;
	struct avl* left;
	struct avl* right;
}avl;

/*
*valid_malloc
*checks to valid that the malloc was successful
*/
void valid_malloc(void*);

/*
*make_node
*mallocs a node with a given key
*/
avl*  make_node(char[], int);

/*
*balance_tree
*rebalance the tree, ordering to balance factor
*/
avl* balance_tree(avl*);

/*
*singleRightRotation
*rotates the tree right on given node
*/
avl* singleRightRotation(avl*);

/*
*singleLeftRotation
*rotates the tree left on given node
*/
avl* singleLeftRotation(avl*);

/*
*insert_key
*inserts key into tree
*/
avl* insert_key(avl*, char[]);

/*
*find_key
*find a given key
*/
void find_key(avl*, char[]);

/*
*compare_children
*compares the children of the child of the root with problem, to decide which rotation to perform
*/
int compare_children(avl*);

/*
*delete_key
*delete a certain key
*/
avl* delete_key(avl* , char[]);

/*
*find_next_node
*finds the next node in inorder traversal
*/
avl* find_next_node(avl*, avl**, char[], int*);

/*
*free_node
*frees memory assoicated with one node
*/
void free_node(avl*);

/*
*free_tree
*frees memory of whole tree
*/
void free_tree(avl*);

/*
*print_node
*prints the information of a given node
*/
void print_node(avl*);

/*
*find_all
*prints all the content of a ndoe above a provided value
*/
void find_all(avl*, int);

/*
*max
*returns greater value from two provided
*/
int max(int, int);

/*
*height_tree
*calculate the longest path of number of edges for a given node 
*/
int height_tree(avl*);

/*
*balance_factor
*calculate the difference between the left and right sub-trees
*/
int balance_factor(avl*);

/*
*size_tree
*calculate the total number of nodes in the tree
*/
void size_tree(avl*, int*);

/*
*parse_file
*to parse the file, read in each line and insert each key into the tree
*/
avl* parse_file(avl*, FILE*);

/*
*remove_newLine
*removes new line character from line from file
*/
void remove_newLine(char []);

#endif