#include "Operation.h"
#include "Product.h"
#include <stdlib.h>

Operation* createOperation(opType type, Product* p) {
	Operation* op = malloc(sizeof(Operation));
	if (op == NULL)
		return NULL;
	op->type = type;

	Product* copyOfP = copyProduct(p);
	op->p = copyOfP;

	return op;
}

void destroyOperation(Operation* o) {
	if (o == NULL)
		return;

	destroyProduct(o->p);
	free(o);
}

opType getOpType(Operation* o) {
	if (o == NULL)
		return -1;
	return o->type;
}

Product * getOpObject(Operation* o) {
	if (o == NULL)
		return NULL;
	return o->p;
}
