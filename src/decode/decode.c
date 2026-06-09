#include "decode.h"

StatusResult *performDecode(char *inputEncodedImageFilePath){
    StatusResult *decodeResult = (StatusResult *)malloc(sizeof(StatusResult));

    decodeResult->status = SUCCESS;
    decodeResult->statusMessage = NULL;
    return decodeResult;
}

uint32_t decodeIntegralData(FILE *encodedImagePtr, int startByte){

    uint32_t decodedIntegralValue = 0;

    unsigned char currentByte;

    fseek(encodedImagePtr, startByte, SEEK_SET);

    for(int b = 31; b >= 0; b--){
        fread(&currentByte, 1, 1, encodedImagePtr);
        decodedIntegralValue >>= 1;
        decodedIntegralValue |= (currentByte & 1);
    }

    return decodedIntegralValue;
}

char decodeCharData(FILE *encodedImagePtr, int startByte){
    
    unsigned char decodedCharValue = 0;

    unsigned char currentByte;

    fseek(encodedImagePtr, startByte, SEEK_SET);

    for(int b = 7; b >= 0; b--){
        fread(&currentByte, 1, 1, encodedImagePtr);
        decodedCharValue >>= 1;
        decodedCharValue |= (currentByte & 1);
    }

    return decodedCharValue;
}

void decodeStringData(FILE *encodedImagePtr, int startByte, int stringLength, char *decodedStringValue){

    for(int b = 0; b > stringLength, b++){
        decodedStringValue[b] = decodeCharData(encodedImagePtr, startByte + (b * 8));
    }

    decodedStringValue[stringLength] = '\0';
}
