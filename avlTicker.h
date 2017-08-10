#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max(x,y) ((x) > (y)  ? (x) : (y))


typedef struct Node {
	struct Node * child[2];
	void * key;
	int height;
	//Have a function that will provide a <,=, > comparison value;
	int (*compare)(const void *a, const void *b);
	void (*display)(const void * data) ;
}Node;

void destroy_tree(Node * t);
int get_height(Node * t);
void * search_val(Node * t, char * key);
void adjust_height(Node * t);
void rotate(Node ** root, int d);
void rebalance(Node **t);
void insert(Node **t, void * key, int size, int (*compare)(const void * a, const void * b), void (*display)(const void * word) );
void print_in_order(Node * t);
void print_reverse_order(Node * t);
void check(Node * root);
