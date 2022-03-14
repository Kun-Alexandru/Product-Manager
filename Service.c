#include "Operation.h"
#include "Service.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

Service* createService(ProductRepo* r)
{
	Service* s = malloc(sizeof(Service));
	if (s == NULL)
		return NULL;
	s->repo = r;
	s->undoStack = createDynamicArray(10, &destroyOperation);
	s->redoStack = createDynamicArray(10, &destroyOperation);

	return s;
}


void destroyService(Service* s)
{
	if (s == NULL)
		return;
	destroyRepo(s->repo);
	destroy(s->undoStack);
	destroy(s->redoStack);
	free(s);
}

int addProduct(Service* s, Product* p) {
	int check;
	check = add(s->repo, p);
	if (check == 0)
		destroyProduct(p);
	if (check == 1 || check == 2) {
		Operation* op = createOperation(ADD, p);
		if (op == NULL)
			return -1;
		addTElem(s->undoStack, op);
	}
	return check;
}

int removeProduct(Service* s, int pos)
{
	int check;
	Product* p = s->repo->products->elems[pos];
	Operation* op = createOperation(DELETE, p);
	check = removee(s->repo, pos);
	if (check == 1)
	{
		if (op == NULL)
			return -1;
		addTElem(s->undoStack, op);
	}
	return check;
}

int updateProduct(Service* s, char name[], char category[], int quantity, int day, int month, int year)
{
	int check;
	int pos = find(s->repo, name, category);
	if (pos == -1)
		return 0;
	Product* p = s->repo->products->elems[find(s->repo, name, category)];
	Product* b = copyProduct(p);
	check = update(s->repo, name, category, quantity, day, month, year);
	Operation* op = createOperation(UPDATE, b);
	if (check == 1) {
		if (op == NULL)
			return -1;
		addTElem(s->undoStack, op);
	}
	destroyProduct(b);
	return check;
}

int undo(Service* s) {

	if (s == NULL)
		return -1; // error

	int stackSize = getLen(s->undoStack);
	if (stackSize == 0)
		return 1;
	Operation* op = get(s->undoStack, stackSize - 1);
	if (op == NULL)
		return -1;
	Product* p = getOpObject(op);
	if (p == NULL)
		return -1;
	int pos = find(s->repo, p->name, p->category);
	if (getOpType(op) == ADD) {
		removee(s->repo, pos);
		Operation* op2 = createOperation(DELETE, p);
		addTElem(s->redoStack, op2);
	}
	else if (getOpType(op) == DELETE) {
		add(s->repo, copyProduct(p));
		Operation* op2 = createOperation(ADD, p);
		addTElem(s->redoStack, op2);
	}
	else if (getOpType(op) == UPDATE) {
		update(s->repo, p->name, p->category, p->quantity, p->day, p->month, p->year);
		Operation* op2 = createOperation(UPDATE, p);
		addTElem(s->redoStack, op2);
	}
	del(s->undoStack, stackSize - 1);
	printf("%d - undo stack\n", getLen(s->undoStack));
	printf("%d - redo stack\n", getLen(s->redoStack));
	return 0;
}

int redo(Service* s) {

	if (s == NULL)
		return -1; // error
	int stackSize = getLen(s->redoStack);
	if (stackSize == 0)
		return 1;
	Operation* op = get(s->redoStack, stackSize - 1);
	if (op == NULL)
		return -1;
	Product* p = getOpObject(op);
	if (p == NULL)
		return -1;


	int pos = find(s->repo, p->name, p->category);
	if (getOpType(op) == ADD) {
		removee(s->repo, pos);
		Operation* op2 = createOperation(ADD, p);
		addTElem(s->undoStack, op2);
	}
	else if (getOpType(op) == DELETE) {
		add(s->repo, copyProduct(p));
		Operation* op2 = createOperation(ADD, p);
		addTElem(s->undoStack, op2);
	
	}
	else if (getOpType(op) == UPDATE) {
		update(s->repo, p->name, p->category, p->quantity, p->day, p->month, p->year);
		Operation* op2 = createOperation(UPDATE, p);
		addTElem(s->undoStack, op2);
	}
	del(s->redoStack, stackSize - 1);
	printf("%d - undo stack\n", getLen(s->undoStack));
	printf("%d - redo stack\n", getLen(s->redoStack));
	return 0;

}

ProductRepo* getRepo(Service* s)
{
	return s->repo;
}

void testAddService() {

	ProductRepo* repository = createRepo();
	Service* service = createService(repository);



	assert(addProduct(service, createProduct("CowMilk", "dairy", 32, 12, 11, 2025)) == 1);
	assert(addProduct(service, createProduct("SoiaMilk", "dairy", 25, 12, 11, 2023)) == 1);
	assert(removeProduct(service, 1) == 1);
	Product* prod1 = createProduct("CowMilk", "dairy", 32, 12, 11, 2025);
	assert(addProduct(service, prod1) == 2);
	destroyService(service);
	destroyProduct(prod1);
}


void testsProductService()
{
	testAddService();
}