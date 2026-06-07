#include "main.h"

int main(){
    char operationType = NULL;
    displayOperationMenu();
    scanf(" %c", &operationType);

    if(operationType == 'E'){
        // Encode
    } else if(operationType == 'D') {
        // Decode
    } else {
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
