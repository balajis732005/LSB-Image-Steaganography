#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "data.h"

void displayOperationMenu();
void getInputForEncode(EncodeInputData *);
EncodeResult* performEncode(EncodeInputData *);

#endif