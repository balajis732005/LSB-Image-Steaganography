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

    inputMessageData->messageFileName = (char *)malloc(sizeof(fileName));
    inputMessageData->messageFileName = fileName;

    inputMessageData->messageFileNameLength = strlen(fileName);

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