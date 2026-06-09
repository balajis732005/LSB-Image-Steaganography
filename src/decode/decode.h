#ifndef DECODE_H
#define DECODE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "data.h"

typedef struct _DecodedData{
    char *decodedMagicString;
    int decodedMessageFileNameLength;
    char *decodedMessageFileName;
    int decodedMessageFileExtensionLength;
    char *decodedMessageFileExtension;
    int decodedMessageFileSize;
    char *decodedOutputMessageFilePath;
} DecodedData;

StatusResult *getImageData(char *, ImageData *);
int decodeIntegralData(FILE *, int);
char decodeCharData(FILE *, int);
void decodeStringData(FILE *, int, int, char *);
void decodeMessageAndWrite(FILE *, FILE *, int, int);
static void freeStatusResult(StatusResult *);
static void freeDecodedData(DecodedData *);
static void freeImageDataDecode(ImageData *);

#endif