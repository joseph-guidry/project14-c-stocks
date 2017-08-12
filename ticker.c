#include "ticker.h"


stock * create_stock(char * symbol, int dollar, int cent, char * company)
{
	stock * new_stock = malloc(sizeof(stock));
	if ( !new_stock)
	{
		fprintf(stderr, "Memory error\n");
		return NULL;
	}
	new_stock->dollar = dollar;
	new_stock->cent = cent;
	new_stock->symbol = malloc(SYMBOL_SZ);
	new_stock->company = malloc(NAME_SZ);
	strncpy(new_stock->symbol, symbol, SYMBOL_SZ);
	strncpy(new_stock->company, company, NAME_SZ);
	
	return new_stock;
}


void destroy_stock(stock * old )
{
	free(old->symbol);
	free(old->company);
	free(old);
}

//How to display the stock structure
void print_stock(const void * x)
{
	printf("%5s %7d.%02d %s\n", ((stock *)x)->symbol, ((stock *)x)->dollar, ((stock *)x)->cent, ((stock *)x)->company);
}

int compare_symbols(const void *a, const void *b)
{
	int x = strcasecmp( ((stock*)a)->symbol, ((stock*)b)->symbol);
	if ( x == 0 )
		return -1;
	else if (x > 0)
		return 1;
	else 
		return 0;
	
}

//Place in tree based on the nominal share price. 
int cmp_price(const void * a, const void * b)
{
	stock * first = (stock *) a;
	stock * second = (stock *) b;
	double result = convert_to_price(first->dollar, first->cent) - convert_to_price(second->dollar, second->cent);
	if ( result < 0 )
		return 0;
	else if ( result > 0 )
		return 1;
	//if the values are equal use symbol to determine which way
	else
	{
		if (strcasecmp( first->symbol, second->symbol) < 0 )
		{
			//Send to the left if prices are the same and first symbol is less than other
			return 0;
		}
		else
		{
			//Send to the right if prices are the same and first symbol is greater than other
			return 1;
		}
	}
}
//Take dollar and cent values and convert to double to determine the difference.
static double evalute_value(int dollar1, int cent1, int dollar2, int cent2)
{

	//Ensure that values are both the same sign, either "+" or "-".
	if ( dollar1 < 0 )
		 cent1 *= -1;
		 
	if ( dollar2 < 0)
		cent2 *= -1;

	double value1 = (double)dollar1 + ((double)cent1/100);
	double value2 = (double)dollar2 + ((double)cent2/100);
	
	return value1 + value2;
}

//If symbol is found in the BST, the node will modify its contents with the values of the stock structure.
void modify_node(Node ** temp, void * data)
{
	temp = ((Node **)temp);
	int total_dollar, total_cent;
	double result;
	
	//check if operation will result in stock price falling below $0.01
	if( (result = evalute_value( ((stock*)(*temp)->key)->dollar, ((stock*)(*temp)->key)->cent, ((stock*)data)->dollar, ((stock*)data)->cent )) <= 0.00 )
	{
		fprintf(stderr, "Attempt adjust stock below $0.01. Transaction will NOT be completed\n");
		return;
	}
	else
	{
		//IF value is not a negative, then convert double back to int pieces.
		total_dollar = (int) (result /1);
		total_cent = ((double)(result - total_dollar) * 100 + 0.5) ;
	}
	((stock*)(*temp)->key)->dollar = total_dollar;
	((stock*)(*temp)->key)->cent = total_cent;
	
	return;
}


double convert_to_price(int dollar, int cent)
{
	double value = 0.0;
	
	value = dollar + ((double)cent / 100);
	
	return value;
}

