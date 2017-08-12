#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include "ticker.h"

#define BUFF_SIZE 100

void reorder_tree(Node * stocks, Node ** new);
FILE * check_file( char * filename);
void usage(const char * input);
char * get_company(char * buffer);
int get_num_length(int dollar, int cent);
void update_stock(Node ** stocks, char * symbol, int dollar, int cent);
void delete_stuff(Node * delete);



int main(int argc, char **argv)
{
	if ( argc < 1)
		usage(argv[0]);
		
	FILE * input = check_file(argv[1]);
	
	Node * new = NULL;
	Node * stocks = NULL;
	int dollar = 0, cent = 0;
	char symbol[5], company[NAME_SZ], buffer[BUFF_SIZE];
	const char * row = "+-----------------------------------------------+\n";
	//Build BST from argv[1] file.
	if( input )
	{
		printf("%s", row);
		printf("\tGETTING STOCK DATA from %s\t\n", argv[1] != NULL? "file": "no file");
		printf("%s", row);
		
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
		//If file is open, then close it.
		fclose(input);
	}
	
	printf("%s", row);
	printf("\t\tGETTING STOCK UPDATES\t\t\n");
	printf("%s", row);
	//Take input from a input through STDIN
	while (  fgets(buffer, BUFF_SIZE, stdin) )
	{	
		//Only will trigger on  blank line
		if(  !(sscanf(buffer, "%s %d.%d", symbol, &dollar, &cent)) || (buffer[0] == '\n') )
			continue;
		
		if ( (dollar == 0) && (cent == 0) )
		{
			buffer[strlen(buffer) - 1] = '\0';
			fprintf(stderr, "Input acheives no effect: [%s]\n", buffer);
			continue;
		}
		
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
		sleep(1);
	}
	
	// This section is commented out but would display 
	// the BST in order based on SYMBOL.	
	/*
	printf("%s", row);
	printf("\t\tIn order by SYMBOL\t\t\n");
	printf("%s", row);

	print_in_order(stocks);
	*/
	reorder_tree(stocks, &new);
	delete_stuff(stocks);
	
	printf("%s", row);
	printf("\tIn order by NOMINAL VALUE\t\t\n");
	printf("%s", row);
	
	print_in_order(new);
	delete_stuff(new);
    return 0;
}

void reorder_tree(Node * stocks, Node ** new)
{
	if ( stocks != NULL)
	{
		//GRAB individual data pieces from node and create new node with that data.
		//ENSURE That dollar and cent amount is positive.
		if ( (((stock *)(stocks->key))->dollar > 0 ) || ( (((stock *)(stocks->key))->dollar == 0 ) && ( ((stock *)(stocks->key))->cent > 0 )  ) )
		{
			stock * new_stock = create_stock( ((stock *)(stocks->key))->symbol, ((stock *)(stocks->key))->dollar, ((stock *)(stocks->key))->cent, ((stock *)(stocks->key))->company );
			insert(new, new_stock, sizeof(stock), cmp_price, print_stock, modify_node);
		}
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
		fprintf(stderr, "No file open: using standard input\n");
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
	//Conduct checks to validate the input from file and stdin.
	if ( !symbol )
	{
		fprintf(stderr, "Invalid data \n");
		return 0;
	}
	
	if ( strlen(symbol) > 5)
	{
		fprintf(stderr, "Error: ticker symbol longer than 5 characters. The record will be skipped.\n");
		return 0;
	}
	if ( (dollar > MAX_VALUE) || (dollar == MAX_VALUE && cent) )
	{
		fprintf(stderr, "Error: price is larger than $1,000,000.00. The record will be skipped.\n");
		return 0;
	}
	if ( get_num_length(dollar, cent) > 9)
	{
		fprintf(stderr, "Error: price longer than 10 characters. The record will be skipped.\n");
		return 0;
	}
	
	return 1;
}

int get_num_length(int dollar, int cent)
{
	int count = 0;
	if (dollar < 0)
	{
		count++;
		dollar *= -1;
	}
	while ( dollar > 0)
	{
		count++;
		dollar /= 10;
	}
	while ( cent > 0)
	{
		count++;
		cent /= 10;
	}
	return count;
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

/*Attempt to free all malloced memory -> GOOD LUCK */
void delete_stuff(Node * delete)
{
	if ( delete )
	{
		delete_stuff(delete->child[0]);
		delete_stuff(delete->child[1]);
		destroy_stock(((stock*)delete->key));
		free(delete);
	}
}
