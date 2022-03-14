#pragma once
#include "ProductRepo.h"

typedef struct {
	ProductRepo* repo;
	DynamicArray* undoStack;
	DynamicArray* redoStack;
}Service;


/// <summary>
/// Make a service type based on the given repo
/// </summary>
Service* createService(ProductRepo* v);

/// <summary>
/// Free the memory ocupied by the service, by destroying it
/// </summary>
void destroyService(Service* s);

/// <summary>
/// Add a product in the repo
/// </summary>
int addProduct(Service* s, Product* p);

/// <summary>
/// Remove a product fro the repo
/// </summary>
int removeProduct(Service* s, int pos);

/// <summary>
/// Update a product from the repo
/// </summary>
int updateProduct(Service*, char name[], char category[], int quantity, int day, int month, int year);

/// <summary>
/// Return the repo which service is based on
/// </summary>
ProductRepo* getRepo(Service* s);

int undo(Service* s);

int redo(Service* s);

void testsProductService();
