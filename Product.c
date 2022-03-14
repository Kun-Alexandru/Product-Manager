#include "Product.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Product* createProduct(char name[], char category[], int quantity, int day, int month, int year) {

	Product* p = malloc(sizeof(Product));

	if (p == NULL)
		return NULL;

	strcpy(p->name, name);
	strcpy(p->category, category);
	p->quantity = quantity;
	p->day = day;
	p->month = month;
	p->year = year;

	return p;

}

void destroyProduct(Product* p)
{
	if (p == NULL)
		return;

	free(p);
}
char* getName(Product* p)
{
	if (p == NULL)
		return " ";
	return p->name;
}
char* getCategory(Product* p)
{
	if (p == NULL)
		return " ";
	return p->category;
}
int getQuantity(Product* p)
{
	if (p == NULL)
		return -1;
	return p->quantity;
}

int getDay(Product* p)
{
	if (p == NULL)
		return -1;
	return p->day;
}

int getMonth(Product* p)
{
	if (p == NULL)
		return -1;
	return p->month;
}

int getYear(Product* p)
{
	if (p == NULL)
		return -1;
	return p->year;
}

void toString(Product* p, char str[])
{
	if (p == NULL)
		return;

	sprintf(str, "Product %s from category %s in quantity %d expires in %d.%d.%d.", p->name, p->category, p->quantity, p->day, p->month, p->year);
}

Product* copyProduct(Product* p)
{
	if (p == NULL)
		return NULL;
	return createProduct(p->name,p->category,p->quantity,p->day,p->month,p->year);
}


void testAddProd() {


	Product* prod1 = createProduct("lapte", "dairy", 32, 15, 11, 2023);
	Product* prod2 = createProduct("sour apple", "fruit", 50, 13, 3, 2025);
	assert(getQuantity(prod1) == 32);
	assert(getQuantity(prod2) == 50);
	assert(getDay(prod1) == 15);
	assert(getDay(prod2) == 13);
	assert(getMonth(prod1) == 11);
	assert(getMonth(prod2) == 3);
	assert(getYear(prod1) == 2023);
	assert(getYear(prod2) == 2025);
	destroyProduct(prod1);
	destroyProduct(prod2);

}


void testsProduct()
{
	testAddProd();
}
