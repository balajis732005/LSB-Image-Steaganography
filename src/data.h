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

#define MAGIC_STRING "#E#"

#endif