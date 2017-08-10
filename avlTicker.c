#include "avlTicker.h"


//Get the item to modify and what to update it to. 
/*
	1. Search for element; Return to modify function.
	2. Member to modify
	3. How to modify it.
*/

void modify_node(Node * t, void * data)
{
	return;
}

void destroy_tree(Node * t)
{
	if (t != NULL)
	{
		destroy_tree(t->child[0]);
		destroy_tree(t->child[1]);
		free(t->key);
		free(t);
	}
}

int get_height(Node * t)
{
	if (t != NULL)
	{
		return t->height;
	}
	else
	{
		return 0;
	}
}

void * search_val(Node * t, char * key)
{
	//This function takes a root node, and a key word to search for.
	//Returns the word that was succesfully matched, else it returns nothing.
	
	if ( t == NULL)
	{	//Reached end of search -- Not in the tree;
		return NULL;
	}	
	
	//If there are leaf nodes remaining to search.
	int order = t->compare(key, t->key);
	//If compare function returns as equal (-1)
	if ( order  < 0)
	{
		return t->key; 
	}
	//Else the compare function returns either greater than (1) or less than (0).
	else 
	{
		return search_val(t->child[order], key);
	}
}

void adjust_height(Node * t)
{
	//Double check and adjust
	if(t != NULL)
		t->height = 1 + Max(get_height(t->child[0]), get_height(t->child[1]));
}

void rotate(Node ** root, int d)
{
	//Implemenation of AVL tree rotation that picks the direction based on the data it receives from rebalance().
	Node * oldRoot;
	Node * newRoot;
	Node * oldMiddle;
	
	oldRoot = *root;
	newRoot = oldRoot->child[d];
	oldMiddle = newRoot->child[!d];
	
	oldRoot ->child[d] = oldMiddle;
	newRoot->child[!d] = oldRoot; 
	*root = newRoot;
	
	//Adjust heights after rotation
	adjust_height((*root)->child[!d]); 	//old
	adjust_height(*root);				//new
}

void rebalance(Node **t)
{
	//Checks the height of the nodes in the tree, will rotate if required in the appropriate direction.
	int d;
	
	if (*t != NULL)
	{
		for (d = 0; d < 2; d++)
		{
			if (get_height((*t)->child[d]) > get_height((*t)->child[!d]) + 1)
			{
				if( get_height((*t)->child[d]) > get_height((*t)->child[!d]))
				{
					rotate(t, d);
				}
				else
				{
					rotate(&(*t)->child[d], !d);
					rotate(t, d);
				}
				
				return;
			}
		}
		adjust_height(*t);
	}
}

void insert(Node **t, void * key, int size, int (*compare)(const void * a, const void * b), void (*display)(const void * data))
{
	if (*t == NULL)
	{
		*t = malloc(sizeof(struct Node));
		if (t == NULL)
		{
			fprintf(stderr, "Memory error\n");
			return;
		}
		
		(*t)->child[0] = NULL;
		(*t)->child[1] = NULL;
		
		//Insert the word into a new BST.
		(*t)->key = malloc(size);
		memcpy((*t)->key, key, size);
		(*t)->height = 1;
		
		(*t)->compare = compare;
		(*t)->display = display;
		return;
	}
	else if ( compare(key, (*t)->key)  < 0)
	{
		return;
	}
	else
	{
		insert(&(*t)->child[(*t)->compare(key, (*t)->key)], key, size, compare, display);
		rebalance(t);
		return;
	}
}

void print_in_order(Node * t)
{
	if ( t != NULL)
	{ 	
		print_in_order(t->child[0]);
		t->display(t->key);
		print_in_order(t->child[1]);
	}
}

void print_reverse_order(Node * t)
{
	if ( t != NULL)
	{
		print_reverse_order(t->child[1]);
		t->display(t->key);
		print_reverse_order(t->child[0]);
	}
}

void check(Node * root)
{
	int i;
	if ( root != NULL)
	{
		for ( i = 0; i < 2; i++)
		{
			check(root->child[i]);
		}
		root->height == 1 + Max(get_height(root->child[0]), get_height(root->child[1]));
	}
}

