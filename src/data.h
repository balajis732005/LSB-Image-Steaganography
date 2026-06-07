#ifndef DATA_H
#define DATA_H

typedef struct _EncodeInputData{
    char *inputMessageFilePath;
    char *imageFilePath;
} EncodeInputData;

typedef enum{
    ENCODE_SUCCESS,
    ENCODE_FAILURE
} EncodeStatus;

typedef struct _EncodeResult{
    EncodeStatus encodeStatus;
    char *encodeResultMessage;
} EncodeResult;

typedef enum{
    SUCCESS,
    FAILURE
} Status;

#define MAGIC_STRING "#E#"

#endif