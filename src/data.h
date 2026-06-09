#ifndef DATA_H
#define DATA_H

typedef struct _EncodeInputData{
    char *inputMessageFilePath;
    char *imageFilePath;
} EncodeInputData;

typedef enum{
    SUCCESS,
    FAILURE
} Status;

typedef struct _StatusResult{
    Status status;
    char *statusMessage;
} StatusResult;

typedef struct _ImageData{
    char *imageFileName;
    long int imageFileSize;
    int pixelStartByte;
    int imageFileHeaderInfoSize;
    int bitmapWidth;
    int bitmapHeight;
    int bitsPerPixel;
} ImageData;

#define MAGIC_STRING "#E#"

#endif