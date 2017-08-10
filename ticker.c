#include "ticker.h"

stock * create_stock(const char * symbol, unsigned int dollar, unsigned int cent, const char * company)
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
	//x = (stock *) x
	printf("Symbol: %s | Price: %u.%u | Company: %s \n", 
		((stock *)x)->symbol, ((stock *)x)->dollar, ((stock *)x)->cent, ((stock *)x)->company);
}

