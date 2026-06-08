#include "encode.h"

EncodeResult* performEncode(EncodeInputData *encodeInputData){
    EncodeResult *encodeResult = (EncodeResult *)malloc(sizeof(EncodeResult));
    InputMessageData *inputMessageData = (InputMessageData *)malloc(sizeof(InputMessageData));
    ImageData *imageData = (ImageData *)malloc(sizeof(ImageData));

    StatusResult *inputDataExtractionStatus;
    inputDataExtractionStatus = getInputMessageData(encodeInputData->inputMessageFilePath, inputMessageData);

    if(inputDataExtractionStatus->status == FAILURE){
        encodeResult->encodeStatus = ENCODE_FAILURE;
        encodeResult->encodeResultMessage = (char *)malloc(51);
        encodeResult->encodeResultMessage = inputDataExtractionStatus->statusMessage;
        return encodeResult;
    }

    // printf("\nFile Name Length: %d", inputMessageData->messageFileNameLength);
    // printf("\nFile Name: %s", inputMessageData->messageFileName);
    // printf("\nFile Extension length: %d", inputMessageData->messageFileExtensionLength);
    // printf("\nFile Extension : %s", inputMessageData->messageFileExtension);
    // printf("\nFile Size : %ld\n", inputMessageData->messageFileSize);

    StatusResult *imageDataExtractionStatus;
    imageDataExtractionStatus = getImageData(encodeInputData->imageFilePath, imageData);
    
    if(imageDataExtractionStatus->status == FAILURE){
        encodeResult->encodeStatus = ENCODE_FAILURE;
        encodeResult->encodeResultMessage = (char *)malloc(51);
        encodeResult->encodeResultMessage = imageDataExtractionStatus->statusMessage;
        return encodeResult;
    }

    // printf("FN : %s\n", imageData->imageFileName);
    // printf("SIZE : %ld\n", imageData->imageFileSize);
    // printf("PStart: %d\n", imageData->pixelStartByte);
    // printf("HINFOSIZE : %d\n", imageData->imageFileHeaderInfoSize);
    // printf("W : %d\n", imageData->bitmapWidth);
    // printf("H : %d\n", imageData->bitmapHeight);
    // printf("BPerPix : %d\n", imageData->bitsPerPixel);

    long int bytesNeededToEncode = 24 + 
                              32 + (inputMessageData->messageFileNameLength * 8) + 
                              32 + (inputMessageData->messageFileExtensionLength * 8) + 
                              32 + (inputMessageData->messageFileSize * 8);
    
    long int noOfBytesInImage = (imageData->bitmapWidth) * (imageData->bitmapHeight) * 3;

    printf("%ld\n", bytesNeededToEncode);

    if(bytesNeededToEncode > noOfBytesInImage){
        encodeResult->encodeStatus = ENCODE_FAILURE;
        encodeResult->encodeResultMessage = (char *)malloc(51);
        encodeResult->encodeResultMessage = "[ERROR] BMP File Capacity is not sufficient to encode input data!";
        return encodeResult;
    }

    char *encodedImageFilePath = (char *)malloc(101);
    snprintf(
        encodedImageFilePath,
        101,
        "output/%s_encoded.%s",
        imageData->imageFileName,
        "bmp"
    );

    printf("%s\n", encodedImageFilePath);

    copyImageFile(encodeInputData->imageFilePath, encodedImageFilePath);

    int currentByteForEncode = imageData->pixelStartByte;

    printf("%d\n", currentByteForEncode);

    encodeInputFileDetails(encodedImageFilePath, inputMessageData, &currentByteForEncode);

    encodeResult->encodeStatus = ENCODE_SUCCESS;
    encodeResult->encodeResultMessage = NULL;
    return encodeResult;
}

StatusResult *getInputMessageData(char *inputMessageFilePath, InputMessageData *inputMessageData){
    FILE *inputMessageFilePtr = fopen(inputMessageFilePath, "r");

    StatusResult *statusResult = (StatusResult *)malloc(sizeof(StatusResult));
    statusResult->statusMessage = NULL;

    if(inputMessageFilePtr == NULL){
        statusResult->status = FAILURE;
        statusResult->statusMessage = "[ERROR] Input Message File Not Found!";
        return statusResult;
    }

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

    statusResult->status = SUCCESS;
    return statusResult;
}

StatusResult *copyImageFile(char *inputImageFilePath, char *outputImageFilePath){

    StatusResult *statusResult = (StatusResult *)malloc(sizeof(StatusResult));
    statusResult->statusMessage = NULL;

    FILE *inputImagePtr = fopen(inputImageFilePath, "rb");
    if(inputImagePtr == NULL){
        statusResult->status = FAILURE;
        statusResult->statusMessage = "[ERROR] Input Image File Not Found!";
        return statusResult;
    }

    FILE *outputImagePtr = fopen(outputImageFilePath, "wb");
    if(outputImagePtr == NULL){
        statusResult->status = FAILURE;
        statusResult->statusMessage = "[ERROR] Output Image File Not Found!";
        fclose(inputImagePtr);
        return statusResult;
    }

    unsigned char dataBuffer[4096];
    size_t byteRead;

    while((byteRead = fread(dataBuffer, 1, sizeof(dataBuffer), inputImagePtr)) > 0){
        fwrite(dataBuffer, 1, byteRead, outputImagePtr);
    }

    fclose(inputImagePtr);
    fclose(outputImagePtr);

    statusResult->status = SUCCESS;
    return statusResult;
}

// Read 16-bit little-endian value
static uint16_t readLittleEndian_16bits(const unsigned char *p){
    return (uint16_t)p[0] |
           ((uint16_t)p[1] << 8);
}

// Read 32-bit little-endian value
static uint32_t readLittleEndian_32bits(const unsigned char *p){
    return (uint32_t)p[0] |
           ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}

StatusResult *getImageData(char *imageFilePath, ImageData *imageData){

    FILE *imageFilePtr = fopen(imageFilePath, "rb");
    StatusResult *statusResult = (StatusResult *)malloc(sizeof(StatusResult));
    statusResult->statusMessage = NULL;

    if(imageFilePtr == NULL){
        statusResult->status = FAILURE;
        statusResult->statusMessage = "[ERROR] Image File Not Found!";
        return statusResult;
    }

    // Image File Name
    char *fileName = strrchr(imageFilePath, '/');
    if(fileName){
        fileName++;
    } else {
        fileName = imageFilePath;
    }

    char *backSlash = strrchr(imageFilePath, '\\');
    if(backSlash){
        fileName = backSlash + 1;
    }

    char *dot = strrchr(fileName, '.');

    size_t fileNameLength = dot - fileName;

    imageData->imageFileName = (char *)malloc(fileNameLength + 1);
    memcpy(imageData->imageFileName, fileName, fileNameLength);

    // Check 1: File Extension Check
    char *fileExtension = strrchr(fileName, '.');
    if(fileExtension){
        fileExtension++;
    }

    if (fileExtension == NULL || (strcmp(fileExtension, "bmp") != 0 && strcmp(fileExtension, "BMP") != 0)){
        statusResult->status = FAILURE;
        statusResult->statusMessage = "[ERROR] Image File Not have \'.bmp\' Extension!";
        return statusResult;
    }

    // Check 2: Header Minimum Size
    unsigned char header[54];
    if(fread(header, 1, 54, imageFilePtr) < 54){
        statusResult->status = FAILURE;
        statusResult->statusMessage = "[ERROR] Image File Not in BMP Format, Header size is less than minimum size!";
        fclose(imageFilePtr);
        return statusResult;
    }

    // Check 3: File Signature
    if(header[0] != 'B' || header[1] != 'M'){
        statusResult->status = FAILURE;
        statusResult->statusMessage = "[ERROR] Image File Not in BMP Format, Signature of the file is not \'BM\'!";
        fclose(imageFilePtr);
        return statusResult;
    }

    // Image File Size
    imageData->imageFileSize = (long int)readLittleEndian_32bits(&header[2]);

    // Pixels Start Byte
    imageData->pixelStartByte = (int)readLittleEndian_32bits(&header[10]);

    // Image Header Size
    imageData->imageFileHeaderInfoSize = (int)readLittleEndian_32bits(&header[14]);

    // Check 4: Hedaer Info Size is Standard or not
    if (imageData->imageFileHeaderInfoSize != 12 &&
        imageData->imageFileHeaderInfoSize != 40 &&
        imageData->imageFileHeaderInfoSize != 52 &&
        imageData->imageFileHeaderInfoSize != 56 &&
        imageData->imageFileHeaderInfoSize != 108 &&
        imageData->imageFileHeaderInfoSize != 124)
    {
        statusResult->status = FAILURE;
        statusResult->statusMessage = "[ERROR] Image File Not in BMP Format, Size of Header Info is not Standard!";
        fclose(imageFilePtr);
        return statusResult;
    }

    if(imageData->imageFileHeaderInfoSize == 12){
        imageData->bitmapWidth = (int)readLittleEndian_16bits(&header[18]);
        imageData->bitmapHeight = (int)readLittleEndian_16bits(&header[20]);
        imageData->bitsPerPixel = (int)readLittleEndian_16bits(&header[24]);
    } else {
        imageData->bitmapWidth = (int)readLittleEndian_16bits(&header[18]);
        imageData->bitmapHeight = (int)readLittleEndian_16bits(&header[22]);
        imageData->bitsPerPixel = (int)readLittleEndian_16bits(&header[28]);
    }

    // Check 5: RGB Data
    if(imageData->bitsPerPixel != 24){
        statusResult->status = FAILURE;
        statusResult->statusMessage = "[ERROR] BMP File with only RGB 24 bits per pixel is only supported!";
        fclose(imageFilePtr);
        return statusResult;
    }

    // Check 6: Compression Status
    if(imageData->imageFileHeaderInfoSize != 12){
        uint32_t compression = readLittleEndian_32bits(&header[30]);
        if (compression != 0){
            statusResult->status = FAILURE;
            statusResult->statusMessage = "[ERROR] Uncompressed BMP File is only supported!";
            fclose(imageFilePtr);
            return statusResult;
        }
    }

    statusResult->status = SUCCESS;
    return statusResult;
}

void encodeIntegralData(FILE *outputImageFilePtr, int startByte, const int dataToEncode){

    unsigned char currentByte;

    fseek(outputImageFilePtr, startByte, SEEK_SET);

    for(int b = 31; b >= 0; b--){
        unsigned char encodeBit = (dataToEncode >> b) & 1;

        fread(&currentByte, 1, 1, outputImageFilePtr);

        currentByte = (currentByte & 0xFE) | encodeBit;

        fseek(outputImageFilePtr, -1, SEEK_CUR);

        fwrite(&currentByte, 1, 1, outputImageFilePtr);
    }
}

void encodeStringData(FILE *outputImageFilePtr, int startByte, const char *dataToEncode){

    unsigned char currentByte;

    fseek(outputImageFilePtr, startByte, SEEK_SET);

    while(*dataToEncode)
    {
        unsigned char currentChar =
                (unsigned char)*dataToEncode;

        for(int b = 7; b >= 0; b--)
        {
            unsigned char encodeBit =
                    (currentChar >> b) & 1;

            fread(&currentByte, 1, 1, outputImageFilePtr);

            currentByte =
                    (currentByte & 0xFE) | encodeBit;

            fseek(outputImageFilePtr, -1, SEEK_CUR);

            fwrite(&currentByte, 1, 1, outputImageFilePtr);
        }

        dataToEncode++;
    }
}

void encodeInputFileDetails(char *outputImageFilePath, InputMessageData *inputMessageData, int *byteToEncode){
    FILE *outputImageFilePtr = fopen(outputImageFilePath, "rb+");

    // Encode Magic String
    encodeStringData(outputImageFilePtr, *byteToEncode, MAGIC_STRING);
    (*byteToEncode) += (strlen(MAGIC_STRING) * 8);

    // Encode Input File Name Size
    encodeIntegralData(outputImageFilePtr, *byteToEncode, inputMessageData->messageFileNameLength);
    (*byteToEncode) += 32;

    // Encode Input File Name
    encodeStringData(outputImageFilePtr, *byteToEncode, inputMessageData->messageFileName);
    (*byteToEncode) += (inputMessageData->messageFileNameLength * 8);

    // Encode Input File Extension Size
    encodeIntegralData(outputImageFilePtr, *byteToEncode, inputMessageData->messageFileExtensionLength);
    (*byteToEncode) += 32;

    // Encode Input File Extension
    encodeStringData(outputImageFilePtr, *byteToEncode, inputMessageData->messageFileExtension);
    (*byteToEncode) += (inputMessageData->messageFileExtensionLength * 8);
}
