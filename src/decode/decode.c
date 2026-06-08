#include "decode.h"

StatusResult *performDecode(char *inputEncodedImageFilePath){
    StatusResult *decodeResult = (StatusResult *)malloc(sizeof(StatusResult));

    decodeResult->status = SUCCESS;
    decodeResult->statusMessage = NULL;
    return decodeResult;
}
