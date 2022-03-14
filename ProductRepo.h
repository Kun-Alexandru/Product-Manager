#pragma once
#include "Product.h"
#include "DynamicArray.h"

typedef struct {
	DynamicArray* products;
}ProductRepo;


/// <summary>
/// Creates a ProductRepo.
/// </summary>
ProductRepo* createRepo();

/// <summary>
/// Destroys a given product repository. The memory is freed.
/// </summary>
void destroyRepo(ProductRepo* v);

/// <summary>
/// Finds the product with the given name and category.
/// </summary>
/// <param name="v">Pointer to the ProductRepo.</param>
/// <param name = "name">A string, the name to search for.</param>
/// /// <param name = "categ">A string, the category to search for.</param>
/// <returns>pos - the position on which the product with the given name and category is in the repo; -1 - if the product does not exist.</returns>
int find(ProductRepo* v, char name[], char categ[]);


/*
	Adds a product to the repository.
	Input:	- v - pointer to the ProductRepo
			- p - product
	Output: 1 - if the product was sucessfully added
			0 - if the product could not be added, as another product with the same name and category already exists in the repo.
*/
int add(ProductRepo* v, Product* p);


/*
	Removes a product from the repo.
	Input:	- v - pointer to the ProductRepo
			- pos - position of the product to be removed from the repo
	Output: 1 - if the product was sucessfully removed
			0 - if the product could not be removed
*/
int removee(ProductRepo* v, int pos);

/*
	Updates a product from the repo.
	Input:	- v - pointer to the ProductRepo
			- name - name of the product to be updated
			- category - categ of the product to be updated
			- quantity - new quantity of the prod
			- day,month,year - new expiration date of the prod
	Output: 1 - if the product was sucessfully removed
			0 - if the product could not be removed
*/
int update(ProductRepo* v, char name[], char category[], int quantity, int day, int month, int year);

int getLength(ProductRepo* v);


/*
	Returns the product on the given position in the product vector (repo).
	Input:	v - the product repository;
			pos - integer, the position;
	Output: the product on the given potision, or an "empty" product.
*/
Product getProductOnPos(ProductRepo* v, int pos);

void testsProductRepo();
