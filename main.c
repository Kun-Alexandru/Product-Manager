#include "ProductRepo.h"
#include "UI.h"
#include <crtdbg.h>

int main() {
	ProductRepo* repository = createRepo();
	Service* service = createService(repository);

	addProduct(service, createProduct("CowMilk", "dairy", 32, 12, 11, 2025));
	addProduct(service, createProduct("SoiaMilk", "dairy", 25, 12, 11, 2023));
	addProduct(service, createProduct("Beef", "meat", 17, 19, 11, 2027));
	addProduct(service, createProduct("Pork", "meat", 23, 10, 11, 2027));
	addProduct(service, createProduct("Chicken", "meat", 20, 11, 11, 2027));
	addProduct(service, createProduct("Apple", "fruit", 50, 15, 11, 2042));
	addProduct(service, createProduct("Mango", "fruit", 5, 20, 5, 2023));
	addProduct(service, createProduct("WhiteChoco", "sweets", 2, 20, 12, 2023));
	addProduct(service, createProduct("BrownChoco", "sweets", 3, 20, 12, 2023));
	addProduct(service, createProduct("Peach", "fruit", 10, 1, 1, 2024));

	UI* ui = createUI(service);

	testsProductRepo();
	testsProduct();
	testsProductService();

	start(ui);

	destroyUI(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}