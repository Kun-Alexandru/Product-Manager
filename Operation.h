#pragma once
#include "Product.h"

typedef enum {
	ADD,
	DELETE,
	UPDATE
} opType;

typedef struct {
	opType type;
	Product* p;
} Operation;

Operation* createOperation(opType type, Product* p);
void destroyOperation(Operation* o);

opType getOpType(Operation* o);
Product* getOpObject(Operation* o);
