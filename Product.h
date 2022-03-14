#pragma once

typedef struct
{
	char name[30];
	char category[30];
	int quantity;
	int day, month, year;
} Product;


/// <summary>
/// Make a variable of type Product
/// </summary>
Product* createProduct(char name[], char category[], int quantity, int day, int month, int year);

/// <summary>
/// Free the memory ocupied by a product.
/// </summary>
void destroyProduct(Product* p);

/// <summary>
/// Get name of a product
/// </summary>
char* getName(Product* p);

/// <summary>
/// Get category of a product
/// </summary>
char* getCategory(Product* p);

/// <summary>
/// Get quantity of a product
/// </summary>
int getQuantity(Product* p);

/// <summary>
/// Get the day of expiration of a product
/// </summary>
int getDay(Product* p);

/// <summary>
/// Get the month of expiration of a product
/// </summary>
int getMonth(Product* p);

/// <summary>
/// Get the year of expiration of a product
/// </summary>
int getYear(Product* p);


/// <summary>
/// Format the product as a string in order to easily print it
/// </summary>
void toString(Product* p, char str[]);

Product* copyProduct(Product* p);

void testsProduct();