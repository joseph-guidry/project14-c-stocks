#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SYMBOL_SZ 5
#define NAME_SZ 56
#define MAX_VALUE 1000000

typedef struct stock {
	char * symbol;
	int dollar;
	int cent;
	char * company;
}stock;

stock * create_stock(const char * symbol, int dollar, int cent, const char * company);
int cmp_price(const void * a, const void * b);
int compare_symbols(const void *a, const void *b);
double convert_to_price(int dollar, int cent);
void print_stock(const void * x);
int validate_input(const char * symbol, const int dollar, const int cent);
void modify_node(void ** temp, void * data1);
