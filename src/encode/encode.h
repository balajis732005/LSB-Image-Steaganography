#ifndef ENCODE_H
#define ENCODE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "data.h"

typedef struct _InputMessageData{
    char magicString[3];
    int messageFileNameLength;
    char *messageFileName;
    int messageFileExtensionLength;
    char *messageFileExtension;
    long int messageFileSize;
} InputMessageData;

Status getInputMessageData(char *, InputMessageData *);

#endif