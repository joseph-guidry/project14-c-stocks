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

int compare_symbols(const void *a, const void *b)
{
	//printf("[%s][%s]\n", ((stock*)a)->symbol, ((stock*)b)->symbol);
	int x = strcasecmp( ((stock*)a)->symbol, ((stock*)b)->symbol);
	if ( x == 0 )
		return -1;
	else if (x > 0)
		return 1;
	else 
		return 0;
	
}

void update_stock(Node ** stocks, char * symbol, int dollar, int cent)
{
	Node ** temp = search_val(stocks, symbol, compare_symbols);
	if (!temp)
	{
		//printf("temp null\n");
		//printf("temp: [%s] \n", symbol);
		return;
	}
	else
	{
		//printf("temp not null\n");
		printf("Found: [%s] \n", ((stock*)(*temp)->key)->symbol);
		//modify_node(temp, &dollar, &cent);
		//Adjust position'9.2bcgmsw
	}
	
}

double evalute_value(int dollar1, int cent1, int dollar2, int cent2)
{
	if ( dollar1 < 0 )
		 cent1 *= -1;
		 
	if ( dollar2 < 0)
		cent2 *= -1;

	//printf("adding dollar: %02f + cent: %02f \n", (double) dollar1, ((double)cent1/100));
	double value1 = (double)dollar1 + ((double)cent1/100);
	//printf("adding dollar: %02f + cent: %02f \n", (double)dollar2, ((double)cent2/100));
	double value2 = (double)dollar2 + ((double)cent2/100);
	
	//printf("value1: %0.2f | value2: %0.2f | equals: %0.2f \n", value1, value2, value1 + value2);
	
	return value1 + value2;
}

void modify_node(Node ** temp, void * data)
{
	temp = ((Node **)temp);
	int total_dollar, total_cent;
	double result;
	
	
	/*
	printf("here in modify\n");
	printf("original dollar:  %d.%02d\n",  ((stock*)(*temp)->key)->dollar, ((stock*)(*temp)->key)->cent );
	printf("update dollar1: %d.%02d\n", ((stock*)data)->dollar, ((stock*)data)->cent );
	*/
	if( (result = evalute_value( ((stock*)(*temp)->key)->dollar, ((stock*)(*temp)->key)->cent, ((stock*)data)->dollar, ((stock*)data)->cent )) <= 0.00 )
	{
		//printf("negative value\n");
		fprintf(stderr, "Transaction puts value below $0.01\n");
		return;
	}
	else
	{
		total_dollar = (int) (result /1);
		total_cent = ((double)(result - total_dollar) * 100 + 0.5) ;
	}
	
	((stock*)(*temp)->key)->dollar = total_dollar;
	((stock*)(*temp)->key)->cent = total_cent;
	
	return;
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

double convert_to_price(int dollar, int cent)
{
	double value = 0.0;
	
	value = dollar + (cent / 100);
	
	return value;
}

//How to display the stock structure
void print_stock(const void * x)
{
	printf("%s %d.%02d %s\n", 
		((stock *)x)->symbol, ((stock *)x)->dollar, ((stock *)x)->cent, ((stock *)x)->company);
}
