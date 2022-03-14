#include "ProductRepo.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <crtdbg.h>
#include <stdio.h>


ProductRepo* createRepo()
{
	ProductRepo* v = malloc(sizeof(ProductRepo));
	if (v == NULL)
		return NULL;
	v->products = createDynamicArray(CAPACITY, &destroyProduct);

	return v;
}

void destroyRepo(ProductRepo* v)
{
	if (v == NULL)
		return;

	destroy(v->products);

	free(v);
}

int find(ProductRepo* v, char name[], char categ[])
{
	if (v == NULL)
		return -1;

	for (int i = 0; i < v->products->length; i++) {
		Product* p = get(v->products, i);
		if (strcmp(p->name, name) == 0 && strcmp(p->category, categ) == 0)
			return i;
	}
	return -1;

}

int add(ProductRepo* v, Product* p) {
	if (v == NULL)
		return 0;

	if (find(v, p->name, p->category) != -1) {
		Product* b = get(v->products, find(v, p->name, p->category));
		b->quantity = p->quantity;
		return 2;
	}

	addTElem(v->products, p);

	return 1;
}

int removee(ProductRepo* v, int pos)
{
	if (v == NULL)
		return 0;

	if (v->products->length - 1 < pos && pos >= 0)
		return 0;

	del(v->products, pos);
	return 1;
}


int update(ProductRepo* v, char name[], char category[], int quantity, int day, int month, int year)
{
	if (v == NULL)
		return 0;
	int pos;
	pos = find(v, name, category);
	if (pos == -1)
		return 0;

	Product* p = get(v->products, pos);
	p->quantity = quantity;
	p->day = day;
	p->month = month;
	p->year = year;

	return 1;
}

int getLength(ProductRepo* v)
{
	return v->products->length;
}

void testAdd() {

	ProductRepo* v = createRepo();

	Product* prod1 = createProduct("lapte", "dairy", 32, 15, 11, 2023);
	Product* prod2 = createProduct("sour apple", "fruit", 50, 13, 3, 2025);
	assert(add(v, prod1) == 1);
	assert(add(v, prod2) == 1);
	Product* prod4 = createProduct("sweet apple", "fruit", 50, 13, 3, 2025);
	assert(add(v, prod4) == 1);
	assert(getLength(v) == 3);
	Product* prod3 = createProduct("lapte", "dairy", 10, 3, 11, 2023);
	assert(add(v, prod3) == 2);
	assert(update(v, "lapte", "dairy", 15, 20, 02, 2020) == 1);
	assert(update(v, "lapteeee", "dairy", 20, 20, 15, 2027) == 0);
	assert(removee(v, 1) == 1);
	destroyProduct(prod3);


	destroyRepo(v);

}


void testsProductRepo()
{
	testAdd();
}