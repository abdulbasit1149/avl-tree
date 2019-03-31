/*
Name: Abdul Basit 
Student ID: 0930431
Date: Monday November 28, 2016
Assignment Number: #4
*/

#include "tree.h"

void valid_malloc(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Out of memory\n");
		exit(1);
	}
}

avl*  make_node(char key[], int count)
{
	avl* node = (avl*)malloc(sizeof(avl));
	valid_malloc(node);

	node->left = NULL;
	node->right = NULL;

	node->key = (char*)malloc(sizeof(char) * strlen(key) + 1);
	valid_malloc(node->key);
	strcpy(node->key,key);
 
	node->count = count;	
	node->bf = Balance;
	return node;
}

avl* balance_tree(avl* root)
{
	//The right side of the tree is heavy, then the left
    if (root->bf < -1)
    {
    	//Determine which child should get preference    
        if (compare_children(root->right))          
        {
        	//Single Right Rotation on right child of root        	
            root->right = singleRightRotation(root->right);

        	//Single Left Rotation             
            root = singleLeftRotation(root);
        }
        else
        {
        	//Single Left Rotation        	
            root = singleLeftRotation(root);
        }
    }
	//The left side of the tree is heavy, then the right    
    else if(root->bf > 1)
    {
    	//Determine which child should get preference
        if (compare_children(root->left))
        {
        	//Single Right Rotation
            root = singleRightRotation(root);
        }
        else
        {           
        	//Single Left Rotation on left child of root
            root->left = singleLeftRotation(root->left);

        	//Single Right Rotation            
            root = singleRightRotation(root);
        }
    }  
    return root;
}

avl* insert_key(avl* root, char key[])
{
	/*
		insert node
	*/
	if (root != NULL)
	{
		if (strcmp(root->key, key)  ==  0)
		{
			//If key already exist, increase frequency only
			root->count = root->count + 1;
			return root;			
		}
		else if (strcmp(key, root->key)  < 0)
		{
			root->left = insert_key(root->left, key);
		}
		else /* strcmp(root->key, key)  >  0*/
		{
			root->right = insert_key(root->right, key);
		}
	}
	else
	{
		//Malloc a new node for a given key
		avl* temp = make_node(key, 1);			
		return temp;
	}

	//Recalculate balance factor
	int balanceFactor = balance_factor(root);
	root->bf = balanceFactor;

	//Balance the tree
    root = balance_tree(root);	

	return root;
}

void find_key(avl* root, char key[])
{
	//Base case
	if (root == NULL)
	{
		printf("\nNo_such_key\n\n");
	}		

	//Recursive case
	if (root != NULL)
	{
		if (strcmp(key, root->key) == 0)
		{
			printf("\nkey: %s frequency: %d\n\n", root->key, root->count);
			return;
		}
		else if (strcmp(key, root->key) < 0)
		{
			find_key(root->left, key);
		}
		else
		{
			find_key(root->right, key);
		}	
	}
}

int compare_children(avl* root)
{
	if (root->left == NULL)
	{
		return 0;
	}
	else if(root->right == NULL)
	{
		return 1;
	}	

	if (root->left != NULL && root->right != NULL)
	{
		int balanceLeft = balance_factor(root->left);
		int balanceRight = balance_factor(root->right);

		//both children have the same balance factor, perferences can be given to any
		if (balanceLeft + balanceRight == 0)
		{
			return 1;
		}
		//Right child has children which are not equal on either side, so it gets perferences
		else if(balanceLeft  == 0 && balanceRight != 0)
		{
			return 0;
		}
		//Left child has children which are not equal on either side, so it gets perferences		
		else
		{
			return 1;
		}
	}

	//Fail case
	return 1;
}

avl* delete_key(avl* root, char key[])
{
	/*
		delete node
	*/
	if (root != NULL)
	{
		if (strcmp(key, root->key) == 0)
		{
			if (root->count == 1)
			{
				//If node to delete has no child
				if (root->left == NULL && root->right == NULL)
				{
					free(root);
					return NULL;
				}
				//if node to delete has one left child, assign left child to parent of node to delete
				else if(root->left != NULL && root->right == NULL)
				{
					avl* temp  = root->left;
					free(root);
					return temp;
				}
				//if node to delete has one right child, assign right child to parent of node to delete				
				else if(root->left == NULL && root->right != NULL)
				{
					avl* temp  = root->right;
					free(root);
					return temp;
				}
				//if node to delete has both children, find next node in inorder traversal to replace deleted node
				else
				{
					avl* toAdd;
                    int found = 0;
					root = find_next_node(root, &toAdd, key, &found);

                    avl* tempLeft = root->left;
                    avl* tempRight = root->right;
                    avl* tempRoot = root;

                    toAdd->right = tempRight;
                    toAdd->left = tempLeft;                    

                    free(tempRoot);

                    int balanceFactor = balance_factor(toAdd);
                    toAdd->bf = balanceFactor;
                    return toAdd;
				}			
			}
			else
			{
				//if node already exist, the decrease frequency by one
				root->count = root->count - 1;
				return root;
			}
		}
		else if (strcmp(key, root->key) < 0)
		{
			root->left = delete_key(root->left, key);
		}
		else
		{
			root->right = delete_key(root->right, key);
		}    
	}
	else
	{
		//Key does not exist
		printf("\nNo_such_key\n\n");
	}
  
    if (root !=  NULL)
    {
        int balanceFactor = balance_factor(root);
        root->bf = balanceFactor;
        root = balance_tree(root);
    }

	return root;
}

avl* find_next_node(avl* root, avl** newNode, char key[], int* found)
{
	//Base case
	if (root == NULL)
	{
		return NULL;
	}
	else
	{
		if (*found == 0 && root->left != NULL)
		{
			root->left = find_next_node(root->left,  newNode,  key, found);
		}

		if (strcmp(root->key, key) > 0)
		{
            if (root->left == NULL && root->right == NULL)
            {
                *found = 1;
                *newNode = root;
                root = NULL;                                                 
            }
            else if (root->left == NULL && root->right != NULL)
            {
                *found = 1;
                avl* temp = root->right;
                *newNode = root;
                root = temp;                
            }
		}

		if (*found == 0 && root->right != NULL)
		{
			root->right = find_next_node(root->right,  newNode,  key, found);		
		}
	}	

    if (root != NULL)
    {
        int balanceFactor = balance_factor(root);
        root->bf = balanceFactor;
    }
    
	return root;
}

void free_node(avl* node)
{
	if (node != NULL)
	{
		free(node->key);
		free(node);
	}
}

void free_tree(avl* root)
{
	if(root && root->left != NULL)
	{
		free_tree(root->left);
	}

	if(root && root->right != NULL)
	{
		free_tree(root->right);
	}

	if(root != NULL)
	{	
		free_node(root);
	}
}

void print_node(avl* node)
{
	if (node != NULL)
	{
		printf("Key: %s, frequency: %d\n", node->key, node->count);		
	}
}

void find_all(avl* root, int frequency)
{	
	if (root != NULL)
	{		
		if (root->left != NULL)
		{
			find_all(root->left, frequency);
		}

        if (root->count >= frequency)
        {
        	//Print that node if it is above a given frequency
            print_node(root);
        }   

		if (root->right != NULL)
		{
			find_all(root->right, frequency);	
		}
	}

}

int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	
	return b;
}

int height_tree(avl* node)
{
	if (node == NULL)
	{
		return -1;
	}

	int leftHeight = height_tree(node->left);
	int rightHeight = height_tree(node->right);

	return max(leftHeight, rightHeight) + 1;
}

int balance_factor(avl* root)
{
	return (height_tree(root->left) - height_tree(root->right));
}

avl* singleRightRotation(avl* root)
{
	avl* temp = root->left;
	root->left = temp->right;
	temp->right = root;

	int balanceFactor = balance_factor(root);
	root->bf = balanceFactor;

	balanceFactor = balance_factor(temp);
	temp->bf = balanceFactor;

	return temp;
}

avl* singleLeftRotation(avl* root)
{
	avl* temp = root->right;
	root->right = temp->left;
	temp->left = root;

	int balanceFactor = balance_factor(root);
	root->bf = balanceFactor;

	balanceFactor = balance_factor(temp);
	temp->bf = balanceFactor;

	return temp;
}

void size_tree(avl* root, int* count)
{
    if (root && root->left != NULL)
    {
        size_tree(root->left, count);
    }

    if (root && root->right != NULL)
    {
        size_tree(root->right, count);
    }

    if (root && root != NULL)
    {
        *count = *count + 1;        
    }
}

avl* parse_file(avl* root, FILE* ifp)
{
	char buffer[500];
	char* token;
	while(fgets(buffer, 500, ifp) != NULL)
	{
		token = strtok(buffer, " ");

		while(token != NULL)
		{			
			if(strlen(token) > 2)
			{
				remove_newLine(token);
				root = insert_key(root, token);	
			}			
			token = strtok(NULL, " ");
		}
	}
    return root;
}

void remove_newLine(char string[])
{
	if(string[strlen(string) - 1] == '\n')
	{
		string[strlen(string) - 1] = '\0';
	}
}