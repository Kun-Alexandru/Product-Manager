#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int monthDays[12]
= { 31, 28, 31, 30, 31, 30,
   31, 31, 30, 31, 30, 31 };

UI* createUI(Service* s) {

	UI* ui = malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;
	ui->s = s;
	return ui;
}

void destroyUI(UI* u) {

	if (u == NULL)
		return;

	destroyService(u->s);
	free(u);
}

void printMenu() {

	printf("1.Add a product.\n");
	printf("2.Remove a product.\n");
	printf("3.Update a product.\n");
	printf("4.List all the products in the fridge.\n");
	printf("5.Display all products from a given category whose expiration date is close in X given days to the given date\n");
	printf("Q.QUIT.\n");

}

void listProducts(UI* u) {

	if (u == NULL)
		return;
	ProductRepo* repo = getRepo(u->s);
	if (repo == NULL)
		return;

	int vec[100];
	int len = 0;

	for (int i = 0; i < repo->products->length; i++) {
		int check = 0;
		Product* p = get(repo->products, i);
		for (int j = 0; j < len; j++) {
			if (p->quantity == vec[j])
				check = 1;
		}
		if (check == 0) {
			vec[len] = p->quantity;
			len++;
		}
	}

	for (int i = 0; i < len; i++)
		for (int j = i + 1; j < len; j++)
			if (vec[i] > vec[j]) {
				int help = vec[i];
				vec[i] = vec[j];
				vec[j] = help;
			}

	char a[100];
	for (int x = 0; x < len; x++) {
		for (int i = 0; i < repo->products->length; i++)
		{
			Product* p = get(repo->products, i);
			if (vec[x] == p->quantity) {
				toString(p, a);
				printf("%d.%s\n", i + 1, a);
			}
		}
	}
	printf("\n");
}

void listProducts2(UI* u, char string[]) {

	if (u == NULL)
		return;
	ProductRepo* repo = getRepo(u->s);
	if (repo == NULL)
		return;

	Product* x;
	for (int i = 0; i < repo->products->length; i++) 
		for (int j = i + 1; j < repo->products->length; j++) 
			if (getQuantity(repo->products->elems[i]) > getQuantity(repo->products->elems[j]))
			{

				x = repo->products->elems[i];
				repo->products->elems[i] = repo->products->elems[j];
				repo->products->elems[j] = x;

			}
		
	
	char a[100];
	for (int i = 0; i < repo->products->length; i++)
	{	
		Product* y = get(repo->products, i);
		if (strstr(y->name, string)) {
			toString(y, a);
			printf("%d.%s\n", i + 1, a);
		}
		else if (strcmp(string, "-1") == 0) {
			toString(y, a);
			printf("%d.%s\n", i + 1, a);
		}
	}
	printf("\n");
}

int getDifference(int givenDay, int givenMonth, int givenYear, int expirationDay, int expirationMonth, int expirationYear)
{
	// COUNT TOTAL NUMBER OF DAYS
	// BEFORE FIRST DATE 'dt1'

	// initialize count using years and day
	long int n1 = givenYear * 365 + givenDay;

	// Add days for months in given date
	for (int i = 0; i < givenMonth - 1; i++)
		n1 += monthDays[i];

	// SIMILARLY, COUNT TOTAL NUMBER OF
	// DAYS BEFORE 'dt2'

	long int n2 = expirationYear * 365 + expirationDay;
	for (int i = 0; i < expirationMonth - 1; i++)
		n2 += monthDays[i];

	// return difference between two counts
	return (n2 - n1);
}

void listProductsXDaysExpiration(UI* u, int givenDay, int givenMonth, int givenYear,char string[], int givenDaysInTime) {

	if (u == NULL)
		return;
	ProductRepo* repo = getRepo(u->s);
	if (repo == NULL)
		return;

	char a[100];
	int counter = 1;
	for (int i = 0; i < repo->products->length; i++) {
		Product* p = get(repo->products, i);
		if (strcmp(p->category, string) == 0 && getDifference(givenDay, givenMonth, givenYear, p->day, p->month, p->year) >= 0 && getDifference(givenDay, givenMonth, givenYear, p->day, p->month, p->year) <=givenDaysInTime) {
			toString(p, a);
			printf("%d.%s\n", counter, a);
			counter = counter + 1;
		}
		if (strcmp(string, "-1") == 0 && getDifference(givenDay, givenMonth, givenYear, p->day, p->month, p->year) >= 0 && getDifference(givenDay, givenMonth, givenYear, p->day, p->month, p->year) <= givenDaysInTime) {
			toString(p, a);
			printf("%d.%s\n", counter, a);
			counter = counter + 1;
		}
	}
}

int undoUI(UI* ui)
{
	return undo(ui->s);
}

int redoUI(UI* ui) {
	return redo(ui->s);
}

void start(UI* u) {

	int isRunning = 1;
	char option[10] = { '\0' };

	while (isRunning == 1) {

		printMenu();
		printf("\nYour option : ");
		int nothing = scanf("%s", &option);
		if (strcmp(option, "1") == 0) {
			char name[30];
			char category[30];
			int quantity;
			int day;
			int month;
			int year;
			printf("\nWhat's the product name? ");
			nothing = scanf("%s", &name);
			printf("\nWhat's the category of the product? ");
			nothing = scanf("%s", &category);
			printf("\nWhat's the quantity? ");
			nothing = scanf("%d", &quantity);
			printf("\nWhat's the day of the expiration? ");
			nothing = scanf("%d", &day);
			printf("\nWhat's the month of the expiration? ");
			nothing = scanf("%d", &month);
			printf("\nWhat's the year of the expiration? ");
			nothing = scanf("%d", &year);
			if (strcmp(category, "dairy") == 0 || strcmp(category, "sweets") == 0 || strcmp(category, "meat") == 0 || strcmp(category, "fruit") == 0) {
				if (day >= 1 && day <= 31 && month >= 1 && month <= 12) {
					Product* p = createProduct(name, category, quantity, day, month, year);
					addProduct(u->s, p);
				}
				else
					printf("Invadia date\n");
			}
			else
				printf("Invalit category\n");

		}
		else if (strcmp(option, "2") == 0) {
			int pos;
			printf("\nWhat's the number of the product you want to remove? ");
			nothing = scanf("%d", &pos);
			int check = removeProduct(u->s, pos - 1);
			if (check == 0)
				printf("ERROR!! The given number doesn't correspond to a product.\n\n");
		}
		else if (strcmp(option, "3") == 0) {
			char name[30];
			char category[30];
			int quantity;
			int day;
			int month;
			int year;
			printf("\nWhat's the product name? ");
			nothing = scanf("%s", &name);
			printf("\nWhat's the category of the product? ");
			nothing = scanf("%s", &category);
			printf("\nWhat's the quantity? ");
			nothing = scanf("%d", &quantity);
			printf("\nWhat's the day of the expiration? ");
			nothing = scanf("%d", &day);
			printf("\nWhat's the month of the expiration? ");
			nothing = scanf("%d", &month);
			printf("\nWhat's the year of the expiration? ");
			nothing = scanf("%d", &year);
			updateProduct(u->s, name, category, quantity, day, month, year);
		}
		else if (strcmp(option, "4") == 0) {
			char string[100];
			printf("Search for a product by name : ");
			nothing = scanf("%s", &string);
			listProducts2(u, string);
		}
		else if (strcmp(option, "5") == 0) {
			char string[100];
			printf("Give me the category name : ");
			nothing = scanf("%s", &string);
			int numberOfDaysTilExpiration;
			printf("Give me the number of days in which a product expires :");
			nothing = scanf("%d", &numberOfDaysTilExpiration);
			int day, month, year;
			printf("Give me the starting day : ");
			nothing = scanf("%d", &day);
			printf("Give me the starting month : ");
			nothing = scanf("%d", &month);
			printf("Give me the starting year : ");
			nothing = scanf("%d", &year);
			listProductsXDaysExpiration(u, day, month, year, string, numberOfDaysTilExpiration);
			printf("\n");
		}
		else if (strcmp(option, "undo") == 0) {

			int res = undoUI(u);
			if (res == 0)
				printf("Undo successful\n");
			else
				printf("There's nothing to undo\n");
			printf("\n");
		}
		else if (strcmp(option, "redo") == 0) {

			int res = redoUI(u);
			if (res == 0)
				printf("Redo successful\n");
			else
				printf("There's nothing to redo\n");
			printf("\n");
		}

		else if (strcmp(option, "Q") == 0 || strcmp(option, "q") == 0) {
			isRunning = 0;
		}
		else
			printf("INVALID OPTION!!!\n");

	}

}