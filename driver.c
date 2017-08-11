#include <stdio.h>
#include <ctype.h>
#include "ticker.h"

#define BUFF_SIZE 100

void reorder_tree(Node * stocks, Node ** new);
FILE * check_file( char * filename);
void usage(const char * input);
char * get_company(char * buffer);
void update_stock(Node ** stocks, char * symbol, int dollar, int cent);

int main(int argc, char **argv)
{
	if ( argc < 1)
		usage(argv[0]);
		
	FILE * input = check_file(argv[1]);
	
	Node * new = NULL;
	Node * stocks = NULL;
	int dollar, cent;
	char symbol[5], company[NAME_SZ], buffer[BUFF_SIZE];
	
	//Build BST from argv[1] file.
	if( input )
	{
		while ( (fscanf(input, "%s %d.%d", symbol, &dollar, &cent) ) && fgets(company, NAME_SZ, input) ) 
		{
			if (validate_input(symbol, dollar, cent) )
			{	
				//NULL Terminate the company string. 
				company[strlen(company) - 1] = '\0';
				//Fill the first BST with the words of the first file
				stock * new_stock = create_stock(symbol, dollar, cent, company);
				print_stock(new_stock);
				insert(&stocks, new_stock, sizeof(stock), compare_symbols, print_stock, modify_node);
				//Reset Values for next ticker symbol
				symbol[0] = company[0] = '\0';
				dollar = cent = 0;
			}
		}
	}
	printf("\n\nGETTING STOCK UPDATES\n\n");
	//Take input from a input through STDIN
	while (  fgets(buffer, BUFF_SIZE, stdin) )
	{	
		//Only will trigger on  blank line
		if(  !(sscanf(buffer, "%s %d.%d", symbol, &dollar, &cent)) || (buffer[0] == '\n') )
			continue;

		//Get the company name of the stock.
		strncpy(company, get_company(buffer), NAME_SZ);
		//NULL Terminate the company string.
		company[strlen(company) - 1] = '\0';
		
		//Validate input prior to inserting into a tree.
		if (validate_input(symbol, dollar, cent) )
		{
			stock * new_stock = create_stock(symbol, dollar, cent, company);
			print_stock(new_stock);
			insert(&stocks, new_stock, sizeof(stock), compare_symbols, print_stock, modify_node);
			//Reset Values for next ticker symbol
			symbol[0] = company[0] = '\0';
			dollar = cent = 0;
		}
	}

	printf("\n\nPRINTING in order by SYMBOL BST\n\n");
	print_in_order(stocks);

	reorder_tree(stocks, &new);
	destroy_tree(stocks);
	
	printf("\n\nPRINTING in order by NOMINAL VALUE BST\n\n");
	print_in_order(new);
	destroy_tree(new);
    return 0;
}

void reorder_tree(Node * stocks, Node ** new)
{
	if ( stocks != NULL)
	{
		//GRAB individual data pieces from node and create new node with that data.
		stock * new_stock = create_stock( ((stock *)(stocks->key))->symbol, ((stock *)(stocks->key))->dollar, ((stock *)(stocks->key))->cent, ((stock *)(stocks->key))->company );
		insert(new, new_stock, sizeof(stock), cmp_price, print_stock, modify_node);
		
		reorder_tree(stocks->child[0], new);
		reorder_tree(stocks->child[1], new);
	}
	return;
}
/* Handle opening of file */
FILE * check_file( char * filename)
{
	FILE * input = fopen(filename, "r");
	
	if ( !input)
	{
		fprintf(stderr, "Failed to open %s\n", filename);
	}
	
	return input;
}

void usage(const char * input)
{
	fprintf(stderr, "usage error: %s [filename] < FILE * stream \n", input);
	exit(1);
}
/* This function takes input data and ensures it is valid.*/
int validate_input(const char * symbol, const int dollar, const int cent)
{

	if ( strlen(symbol) > 5)
	{
		fprintf(stderr, "Symbol length is to long, %s \n", symbol);
		return 0;
	}
	if ( (dollar > MAX_VALUE) || (dollar == MAX_VALUE && cent) )
	{
		fprintf(stderr, "Amount exceed the limit, %d.%d \n", dollar, cent);
		return 0;
	}
	if ( (dollar * -1)> MAX_VALUE ) //Convert dollar.cent to string and ensure strlen < 10?
	{
		fprintf(stderr, "Amount exceed the limit, %d.%d \n", dollar, cent);
		return 0;
	}
	return 1;
}
/*Returns the value that is the company information*/
char * get_company(char * buffer)
{
	char * ptr;
	ptr = buffer;
	for (ptr = &buffer[5]; *ptr != '\0'; ptr++)
	{
		if ( (isalpha(*ptr)) || (*ptr == '\n') )
		{
			return ptr;
		}
	}
	return NULL;
}

