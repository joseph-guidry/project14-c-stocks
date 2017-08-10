#include <stdio.h>
#include "avlTicker.h"
#include "ticker.h"

int main(void)
{
	Node * stocks = NULL;
	int x, error;
	unsigned int dollar, cent;
	char symbol[5], company[NAME_SZ];
	
	//Take input from a input file through STDIN
	while ( (x = fscanf(stdin, "%s %u.%u", symbol, &dollar, &cent)) && fgets(company, NAME_SZ, stdin) )
	{
		//printf("symbol: %s\namount: %u.%u\ncompany: %s\n", symbol, dollar, cent, company);
		
		//Validate input prior to inserting into a tree.
		if ( (error = validate_input( symbol, dollar, cent)) )
		{
			continue;
		}
		
		stock * new_stock = create_stock(symbol, dollar, cent, company);
		print_stock(new_stock);
		insert(&stocks, new_stock, sizeof(stock), cmp_price, print_stock);
	}
	//print_in_order(stocks);
	
	//Accept user input:
	
	//GET SYMBOL
	
	//GET INCREMENT OR DECREMENT 
	
    return 0;
}
