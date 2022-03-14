#pragma once
#include "Service.h"

typedef struct
{
	Service* s;
} UI;

UI* createUI(Service* s);
void destroyUI(UI* u);

void start(UI* u);