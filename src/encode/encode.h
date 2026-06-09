#ifndef ENCODE_H
#define ENCODE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdint.h>
#include "data.h"

typedef struct _InputMessageData{
    int messageFileNameLength;
    char *messageFileName;
    int messageFileExtensionLength;
    char *messageFileExtension;
    int messageFileSize;
} InputMessageData;

StatusResult *getInputMessageData(char *, InputMessageData *);
StatusResult *getImageData(char *, ImageData *);
StatusResult *copyImageFile(char *, char *);
void encodeIntegralData(FILE *, int, const int);
void encodeStringData(FILE *, int, const char *);
void encodeInputFileDetails(char *, InputMessageData *, int *);
void encodeInputFileContent(int, char *,char *, int *);

#endif