#include "ticker.h"
#include "avlTicker.h"



stock * create_stock(const char * symbol, int dollar, int cent, const char * company)
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

void modify_node(void ** temp, void * data1)
{
	printf("here in modify\n");

	//printf("update dollar: %d.%d\n", *((stock*)data)->dollar), *((int*)cent));
	//Ensure there is enough cents to do subtraction from
	
	
	/*
	if ( *(int*)dollar < 0 )
		 *(int*)cent *= -1;
		 
	int total_dollar = ((stock*)(*temp)->key)->dollar + (--(*(int*)dollar));
	int total_cent = ((stock*)(*temp)->key)->cent  + (100+(*(int*)cent));
	
	if ( (total_dollar >= 0) || ( (total_dollar == 0) && (total_cent > 0) ) )
	{
		((stock*)(*temp)->key)->dollar = total_dollar;
		((stock*)(*temp)->key)->cent = total_cent;
		//printf("temp dollar: %d.%d\n", ((stock*)(*temp)->key)->dollar, ((stock*)(*temp)->key)->cent);
	}
	else
	{
		fprintf(stderr, "Transaction puts value below $0.01\n");
		return;
	}
	//printf("temp dollar: %d.%d\n", ((stock*)(*temp)->key)->dollar, ((stock*)(*temp)->key)->cent);
	while ( ((stock*)(*temp)->key)->cent > 99 )
	{
		((stock*)(*temp)->key)->cent -= 100;
		((stock*)(*temp)->key)->dollar++;
	}
	*/
	
	
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
	printf("%s %d.%d %s\n", 
		((stock *)x)->symbol, ((stock *)x)->dollar, ((stock *)x)->cent, ((stock *)x)->company);
}
