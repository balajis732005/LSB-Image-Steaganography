#include "decode.h"

StatusResult *performDecode(char *inputEncodedImageFilePath){

    StatusResult *decodeResult = (StatusResult *)malloc(sizeof(StatusResult));

    ImageData *encodedImageData = (ImageData *)malloc(sizeof(ImageData));

    StatusResult *imageDataExtractionStatus = getImageData(inputEncodedImageFilePath, encodedImageData);

    if(imageDataExtractionStatus->status == FAILURE){
        decodeResult->status = FAILURE;
        decodeResult->statusMessage = imageDataExtractionStatus->statusMessage;

        freeStatusResult(imageDataExtractionStatus);
        free(encodedImageData);

        return decodeResult;
    }

    freeStatusResult(imageDataExtractionStatus);

    FILE *encodedImagePtr = fopen(inputEncodedImageFilePath, "rb");

    if(encodedImagePtr == NULL){
        decodeResult->status = FAILURE;
        decodeResult->statusMessage = "[ERROR] Input Encoded Image File Not Found!";

        freeImageDataDecode(encodedImageData);

        return decodeResult;
    }

    DecodedData *outputDecodedData = (DecodedData *)malloc(sizeof(DecodedData));

    int currentByteToDecode = encodedImageData->pixelStartByte;

    outputDecodedData->decodedMagicString = (char *)malloc(strlen(MAGIC_STRING) + 1);

    decodeStringData(
        encodedImagePtr,
        currentByteToDecode,
        3,
        outputDecodedData->decodedMagicString
    );
    currentByteToDecode += 24;

    if(strcmp(outputDecodedData->decodedMagicString, MAGIC_STRING) != 0){
        decodeResult->status = FAILURE;
        decodeResult->statusMessage =
                "[ERROR] Input Encoded Image File is Not Encoded!";

        fclose(encodedImagePtr);

        freeDecodedData(outputDecodedData);
        freeImageDataDecode(encodedImageData);

        return decodeResult;
    }

    outputDecodedData->decodedMessageFileNameLength = decodeIntegralData(encodedImagePtr, currentByteToDecode);
    currentByteToDecode += 32;

    outputDecodedData->decodedMessageFileName = (char *)malloc(outputDecodedData->decodedMessageFileNameLength + 1);

    decodeStringData(
        encodedImagePtr,
        currentByteToDecode,
        outputDecodedData->decodedMessageFileNameLength,
        outputDecodedData->decodedMessageFileName
    );
    currentByteToDecode += (outputDecodedData->decodedMessageFileNameLength * 8);

    outputDecodedData->decodedMessageFileExtensionLength = decodeIntegralData(
        encodedImagePtr,
        currentByteToDecode
    );
    currentByteToDecode += 32;

    outputDecodedData->decodedMessageFileExtension = (char *)malloc(outputDecodedData->decodedMessageFileExtensionLength + 1);

    decodeStringData(
        encodedImagePtr,
        currentByteToDecode,
        outputDecodedData->decodedMessageFileExtensionLength,
        outputDecodedData->decodedMessageFileExtension
    );
    currentByteToDecode += (outputDecodedData->decodedMessageFileExtensionLength * 8);

    outputDecodedData->decodedMessageFileSize =
        decodeIntegralData(
        encodedImagePtr,
        currentByteToDecode
    );
    currentByteToDecode += 32;

    outputDecodedData->decodedOutputMessageFilePath = (char *)malloc(101);

    snprintf(
        outputDecodedData->decodedOutputMessageFilePath,
        101,
        "output/%s_decoded_%s.%s",
        outputDecodedData->decodedMessageFileName,
        encodedImageData->imageFileName,
        outputDecodedData->decodedMessageFileExtension
    );

    FILE *outputDecodedMessagePtr = fopen(outputDecodedData->decodedOutputMessageFilePath, "wb");

    if(outputDecodedMessagePtr == NULL){
        decodeResult->status = FAILURE;
        decodeResult->statusMessage = "[ERROR] Unable to create output file!";

        fclose(encodedImagePtr);

        freeDecodedData(outputDecodedData);
        freeImageDataDecode(encodedImageData);

        return decodeResult;
    }

    decodeMessageAndWrite(
        encodedImagePtr,
        outputDecodedMessagePtr,
        currentByteToDecode,
        outputDecodedData->decodedMessageFileSize
    );

    fclose(encodedImagePtr);
    fclose(outputDecodedMessagePtr);

    freeDecodedData(outputDecodedData);
    freeImageDataDecode(encodedImageData);

    decodeResult->status = SUCCESS;
    decodeResult->statusMessage = NULL;

    return decodeResult;
}

int decodeIntegralData(FILE *encodedImagePtr, int startByte){

    int decodedIntegralValue = 0;

    unsigned char currentByte;

    fseek(encodedImagePtr, startByte, SEEK_SET);

    for(int b = 31; b >= 0; b--){
        fread(&currentByte, 1, 1, encodedImagePtr);
        decodedIntegralValue |= ((currentByte & 1) << b);
    }

    return decodedIntegralValue;
}

char decodeCharData(FILE *encodedImagePtr, int startByte){
    
    unsigned char decodedCharValue = 0;

    unsigned char currentByte;

    fseek(encodedImagePtr, startByte, SEEK_SET);

    for(int b = 7; b >= 0; b--){
        fread(&currentByte, 1, 1, encodedImagePtr);
        decodedCharValue |= ((currentByte & 1) << b);
    }

    return (char)decodedCharValue;
}

void decodeStringData(FILE *encodedImagePtr, int startByte, int stringLength, char *decodedStringValue){

    for(int b = 0; b < stringLength; b++){
        decodedStringValue[b] = decodeCharData(encodedImagePtr, startByte + (b * 8));
    }

    decodedStringValue[stringLength] = '\0';
}

void decodeMessageAndWrite(FILE *encodedImagePtr, FILE *decodedMessagePtr, int startByte, int stringLength){

    char currentCharData;

    for(int b = 0; b < stringLength; b++){
        currentCharData = decodeCharData(encodedImagePtr, startByte + (b * 8));
        fwrite(&currentCharData, 1, 1, decodedMessagePtr);
    }

}

static void freeStatusResult(StatusResult *result){
    if(result){
        free(result);
    }
}

static void freeDecodedData(DecodedData *data){
    if(data){
        free(data->decodedMagicString);
        free(data->decodedMessageFileName);
        free(data->decodedMessageFileExtension);
        free(data->decodedOutputMessageFilePath);
        free(data);
    }
}

static void freeImageDataDecode(ImageData *data){
    if(data){
        free(data->imageFileName);
        free(data);
    }
}
