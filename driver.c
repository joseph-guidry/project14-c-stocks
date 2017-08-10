#include <stdio.h>
#include "avlTicker.h"
#include "ticker.h"

int main(void)
{
	Node * stocks = NULL;
	int x;
	unsigned int dollar, cent;
	char symbol[5], company[NAME_SZ];
	while ( (x = fscanf(stdin, "%s %u.%u", symbol, &dollar, &cent)) && fgets(company, NAME_SZ, stdin) )
	{
		printf("symbol: %s\namount: %u.%u\ncompany: %s\n", symbol, dollar, cent, company);
		stock * new_stock = create_stock(symbol, dollar, cent, company);
		insert(&stocks, new_stock, sizeof(stock), cmp_price, print_stock);
	}
	print_in_order(stocks);
	
    return 0;
}
