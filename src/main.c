#include "main.h"

int main(){
    char operationType;
    displayOperationMenu();
    scanf(" %c", &operationType);

    operationType = toupper(operationType);

    if(operationType == 'E'){
        // Encode
        EncodeInputData *encodeInputData = (EncodeInputData *)malloc(sizeof(EncodeInputData));
        getInputForEncode(encodeInputData);

        EncodeResult *encodeResult = (EncodeResult *)malloc(sizeof(EncodeResult));
        encodeResult = performEncode(encodeInputData);

        if(encodeResult->encodeStatus == ENCODE_SUCCESS){
            printf("\nENCODE SUCCESS!\n");
        } else if(encodeResult->encodeStatus == ENCODE_FAILURE) {
            printf("\nENCODE FAILURE!\n");
            printf("%s\n", encodeResult->encodeResultMessage);
        }
    }
    else if(operationType == 'D') {
        // Decode
    } 
    else {
        printf("\nEnter Valid option!\n");
    }

    return 0;
}

void displayOperationMenu(){
    printf("\nWelcome to LSB Image Steaganography!\n");
    printf("Enter the operation you want to perform: \n");
    printf("1) ENCODE - \'E\'\n2) DECODE - \'D\'\n");
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
