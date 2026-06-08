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

typedef struct _ImageData{
    char *imageFileName;
    long int imageFileSize;
    int pixelStartByte;
    int imageFileHeaderInfoSize;
    int bitmapWidth;
    int bitmapHeight;
    int bitsPerPixel;
} ImageData;

StatusResult *getInputMessageData(char *, InputMessageData *);
StatusResult *getImageData(char *, ImageData *);
void encode32Bits(FILE *, int *, int *);
void encodeCustomBits(FILE *, int *, int, char *);
void encodeInputFileDetails(char *, InputMessageData *, int *);
void encodeInputFileContent(char *, char *, int *);

#endif