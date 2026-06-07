#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>

typedef struct _EncodeInputData{
    char *inputMessageFilePath;
    char *imageFilePath;
} EncodeInputData;

typedef enum{
    ENCODE_SUCCESS,
    ENCODE_FAILURE
} EncodeStatus;

typedef struct _EncodeResult{
    EncodeStatus encodeStatus;
    char *encodeResultMessage;
} EncodeResult;

void displayOperationMenu();
void getInputForEncode(EncodeInputData *);
EncodeResult* performEncode(EncodeInputData *);

#endif