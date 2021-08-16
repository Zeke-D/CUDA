/* 
 * stocks.c 
 *
 * Read the contents of portfolio.txt and store each 
 * entry as a Linked List of stocks.
 *
 * Compile with: gcc -o stocks stocks.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stock {
    char* symbol;       /* Ticker-tape symbol (i.e., GOOG) */
	int purchasePrice;
	int currentPrice;
	int numberOfShares;
} stock_t;

typedef struct node {
    stock_t* data;
    struct node* next;
} node_t;

/* Note that you may need to change the signatures provided */
void print_portfolio(node_t* startNode);
node_t* create_portfolio(FILE* filePointer);
void free_portfolio(node_t* startNode);
int total_value(node_t* startNode);


int main() {
	FILE* filePointer = fopen("./portfolio.txt", "r");
	node_t* startStockNode = (node_t*) malloc(sizeof(node_t));
	startStockNode = create_portfolio(filePointer);
	print_portfolio(startStockNode);
	printf("Total value so far: %d\n", total_value(startStockNode));
	free_portfolio(startStockNode);
	fclose(filePointer);
    return 0;
}

node_t* create_portfolio(FILE* filePointer) {
	
	char* symbol = (char*) malloc(6);
	int purchasePrice;
	int currentPrice;
	int numberOfShares;

	node_t* startNode;	
	node_t* previousNode;

	while ( fscanf(	filePointer, 
					"%s %d %d %d", 
					symbol, &purchasePrice, &currentPrice, &numberOfShares
			) 
			!= EOF
	) {

		node_t* newNode = (node_t*) malloc(sizeof(node_t));
		stock_t* nodeData = (stock_t*) malloc(sizeof(stock_t));

		char* newSym = (char*) malloc(6);
		strcpy(newSym, symbol);
		nodeData->symbol = newSym;
		nodeData->purchasePrice = purchasePrice;
		nodeData->currentPrice = currentPrice;
		nodeData->numberOfShares = numberOfShares;

		newNode->data = nodeData;
		
		if (previousNode) {
			previousNode->next = newNode;
		}

		if (!startNode) {
			startNode = newNode;
		}
		
		previousNode = newNode;

	}

	free(symbol);

	return startNode;

}

void print_portfolio(node_t* startNode) {

	node_t* currentNode = startNode;

	while (currentNode) {
		stock_t* data = currentNode->data;
		printf(
			"%-5s| %-5d | %-5d | %-5d |\n", 
			data->symbol, data->purchasePrice, data->currentPrice, data->numberOfShares
		);
		currentNode = currentNode->next;
	}

	return;

}

void free_portfolio(node_t* startNode) {

	node_t* currentNode = startNode;

	while (currentNode) {
		node_t* nextNode = currentNode->next;
		free(currentNode->data->symbol);
		free(currentNode->data);
		free(currentNode);
		currentNode = nextNode;
	}

	return;

}

int total_value(node_t* startNode) {
	int value = 0;
	node_t* currentNode = startNode;

	while (currentNode) {
		value += currentNode->data->numberOfShares * (currentNode->data->currentPrice - currentNode->data->purchasePrice);
		currentNode = currentNode->next;
	}

	return value;
}
