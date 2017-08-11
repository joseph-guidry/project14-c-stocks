#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max(x,y) ((x) > (y)  ? (x) : (y))


typedef struct Node {
	struct Node * child[2];
	void * key;
	int height;
	int (*compare)(const void *a, const void *b);
	void (*display)(const void * data) ;
	void (*modify)(void ** temp, void * data1);
}Node;

void destroy_tree(Node * t);
int get_height(Node * t);
Node ** search_val(Node ** t, char * key, int (*compare)(const void * a, const void * b));
void adjust_height(Node * t);
void rotate(Node ** root, int d);
void rebalance(Node **t);
void insert(Node **t, void * key, int size, int (*compare)(const void * a, const void * b), void (*display)(const void * data1), void (*update)(void ** temp, void * data1) );
void print_in_order(Node * t);
void print_reverse_order(Node * t);
void check(Node * root);
