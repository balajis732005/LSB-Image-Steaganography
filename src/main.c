#include "main.h"

int main(){

    char operationType;
    displayOperationMenu();
    scanf(" %c", &operationType);

    operationType = toupper(operationType);

    if (operationType == 'E'){

        // Encode
        EncodeInputData *encodeInputData =
            (EncodeInputData *)malloc(sizeof(EncodeInputData));

        getInputForEncode(encodeInputData);

        StatusResult *encodeResult = performEncode(encodeInputData);

        if (encodeResult->status == SUCCESS)
        {
            printf("\nENCODE SUCCESS!\n");
        }
        else if (encodeResult->status == FAILURE)
        {
            printf("\nENCODE FAILURE!\n");
            printf("%s\n", encodeResult->statusMessage);
        }

        free(encodeInputData->inputMessageFilePath);
        free(encodeInputData->imageFilePath);
        free(encodeInputData);
        free(encodeResult);
    }
    else if (operationType == 'D'){

        char *inputEncodedImageFilePath = (char *)malloc(101);

        printf("Enter Encoded Image File Path: ");
        scanf(" %100[^\n]", inputEncodedImageFilePath);

        StatusResult *decodeResult =
            performDecode(inputEncodedImageFilePath);

        if (decodeResult->status == SUCCESS)
        {
            printf("\nDECODE SUCCESS!\n");
        }
        else if (decodeResult->status == FAILURE)
        {
            printf("\nDECODE FAILURE!\n");
            printf("%s\n", decodeResult->statusMessage);
        }

        free(inputEncodedImageFilePath);
        free(decodeResult);
    }
    else{
        printf("\nEnter Valid option!\n");
    }

    return 0;
}

void displayOperationMenu(){
    printf("\nWelcome to LSB Image Steaganography!\n");
    printf("Enter the operation you want to perform: \n");
    printf("1) ENCODE - 'E'\n2) DECODE - 'D'\n");
    printf("Enter your choice: ");
}

void getInputForEncode(EncodeInputData *encodeInputData){
    printf("\n------------------------------------\n");

    encodeInputData->inputMessageFilePath = (char *)malloc(101);
    printf("Enter the input message file path: ");
    scanf(" %100[^\n]", encodeInputData->inputMessageFilePath);

    encodeInputData->imageFilePath = (char *)malloc(101);
    printf("Enter the image file path: ");
    scanf(" %100[^\n]", encodeInputData->imageFilePath);
}