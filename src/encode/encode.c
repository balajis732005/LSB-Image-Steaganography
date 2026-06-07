#include "encode.h"

EncodeResult* performEncode(EncodeInputData *encodeInputData){
    EncodeResult *encodeResult = (EncodeResult *)malloc(sizeof(EncodeResult));
    InputMessageData *inputMessageData = (InputMessageData *)malloc(sizeof(InputMessageData));

    Status inputDataExtractionStatus;
    inputDataExtractionStatus = getInputMessageData(encodeInputData->inputMessageFilePath, inputMessageData);

    if(inputDataExtractionStatus == FAILURE){
        encodeResult->encodeStatus = ENCODE_FAILURE;
        encodeResult->encodeResultMessage = (char *)malloc(51);
        encodeResult->encodeResultMessage = "[ERROR] Input Message File Not Found!";
        return encodeResult;
    }

    printf("\nMagic String: %s", inputMessageData->magicString);
    printf("\nFile Name Length: %d", inputMessageData->messageFileNameLength);
    printf("\nFile Name: %s", inputMessageData->messageFileName);
    printf("\nFile Extension length: %d", inputMessageData->messageFileExtensionLength);
    printf("\nFile Extension : %s", inputMessageData->messageFileExtension);
    printf("\nFile Size : %ld\n", inputMessageData->messageFileSize);

    encodeResult->encodeStatus = ENCODE_SUCCESS;
    encodeResult->encodeResultMessage = NULL;
    return encodeResult;
}

Status getInputMessageData(char *inputMessageFilePath, InputMessageData *inputMessageData){
    FILE *inputMessageFilePtr = fopen(inputMessageFilePath, "r");

    if(inputMessageFilePtr == NULL){
        return FAILURE;
    }

    strcpy(inputMessageData->magicString, MAGIC_STRING); // Magic String

    // Input File Name
    char *fileName = strrchr(inputMessageFilePath, '/');
    if(fileName){
        fileName++;
    } else {
        fileName = inputMessageFilePath;
    }

    char *backSlash = strrchr(inputMessageFilePath, '\\');
    if(backSlash){
        fileName = backSlash + 1;
    }

    char *dot = strrchr(fileName, '.');

    size_t fileNameLength = dot - fileName;

    inputMessageData->messageFileName = (char *)malloc(fileNameLength + 1);
    memcpy(inputMessageData->messageFileName, fileName, fileNameLength);

    inputMessageData->messageFileNameLength = (int)fileNameLength;

    // Input File Extension

    char *fileEntension = strrchr(fileName, '.');
    if(fileEntension){
        fileEntension++;
    }

    inputMessageData->messageFileExtension = (char *)malloc(sizeof(fileEntension));
    inputMessageData->messageFileExtension = fileEntension;

    inputMessageData->messageFileExtensionLength = strlen(fileEntension);

    // Input File Size
    fseek(inputMessageFilePtr, 0, SEEK_END);
    inputMessageData->messageFileSize = ftell(inputMessageFilePtr);

    fclose(inputMessageFilePtr);

    return SUCCESS;
}