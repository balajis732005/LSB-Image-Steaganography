#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>

typedef struct encodeInputData{
    char *inputMessageFilePath;
    char *imageFilePath;
} EncodeInputData;

void displayOperationMenu();

#endif