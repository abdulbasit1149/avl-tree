/*
Name: Abdul Basit 
Student ID: 0930431
Date: Monday November 28, 2016
Assignment Number: #4
*/

#include <stdio.h>
#include "tree.h"

int main(void)
{

	printf("Welcome\n-------\n\n");
	printf("Author: Abdul Basit\n");
	printf("ID: 0930431\n\n");

	//main command loop for the entire program
	int loop  = 1;

	//For user input
	int choice = -1;

	//File input 
	FILE* ifp;
	char filename[50];	

	//variables to manage and create avl tree
	avl* root = NULL;
	char key[50];

	//Size of tree and height of tree
	int size = 0;
	int height = 0;

	//Frequency to find in tree
	int frequency = 0;

	while(loop)
	{
		printf("Menu\n-----\n");

		printf("(1) Initialization\n");
		printf("(2) Find\n");
		printf("(3) Insert\n");
		printf("(4) Remove\n");
		printf("(5) Check Height and Size\n");
		printf("(6) Find All (above a given frequency)\n");
		printf("(7) Exit\n");

		printf("avl/> ");
		scanf("%2d", &choice);

		switch(choice)
		{
			case 1:

				printf("filename: ");
				scanf("%50s", filename);				
				ifp = fopen(filename, "r");

				if(ifp == NULL)
				{
					printf("\nfile does not exist\n\n");
					break;
				}

				//Read the file and insert keys into tree
				root = parse_file(root, ifp);

				//Close the file				
				fclose(ifp);				

				break;							
			case 2:

				printf("find key: ");
				scanf("%50s", key);
				find_key(root, key);

				break;
			case 3:

				printf("Insert Key: ");
				scanf("%50s", key);
				root = insert_key(root, key);
				
				break;
			case 4:

				printf("Key to delete: ");
				scanf("%50s", key);
				root = delete_key(root,key);

				break;
			case 5:

				height = height_tree(root);

				if(height != -1)
				{
					printf("Height of Tree: %d\n", height_tree(root));
				}
				else
				{
					printf("Height of Tree: 0\n");
				}
				
				size_tree(root, &size);
				printf("Size of Tree: %d\n", size);

				//Reset size to recalculate for next time
				size = 0;

				break;
			case 6:

				printf("frequency: ");
				scanf("%10d",&frequency);				
				find_all(root, frequency);

				break;
			case 7:

				printf("Good bye\n");
				loop = 0;

				break;
			default:
				printf("Please pick from the following options: 1,2,3,4,5,6,7\n");
		}
	}

	//Free all the memory with the avl tree
	free_tree(root);

	return 0;
}
