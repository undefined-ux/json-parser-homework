#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

FILE* convertUtf8ToGbk(FILE* input, const char* outputFileName) {
    iconv_t cd;
    cd = iconv_open("GBK", "UTF-8");
    if (cd == (iconv_t)-1) {
        perror("iconv_open");
        exit(EXIT_FAILURE);
    }

    FILE* output = fopen(outputFileName, "w");
    if (output == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char inputBuffer[4096];
    char outputBuffer[8192];
    size_t bytesRead, inputBytesLeft, outputBytesLeft;

    while ((bytesRead = fread(inputBuffer, 1, sizeof(inputBuffer), input)) > 0) {
        inputBytesLeft = bytesRead;
        char* inputPtr = inputBuffer;

        outputBytesLeft = sizeof(outputBuffer);
        char* outputPtr = outputBuffer;

        if (iconv(cd, &inputPtr, &inputBytesLeft, &outputPtr, &outputBytesLeft) == (size_t)-1) {
            perror("iconv");
            exit(EXIT_FAILURE);
        }

        size_t outputBytesWritten = sizeof(outputBuffer) - outputBytesLeft;
        fwrite(outputBuffer, 1, outputBytesWritten, output);
    }

    iconv_close(cd);
    fclose(input);
    fclose(output);

    return fopen(outputFileName, "r");
}

void convertGbkToUtf8(FILE* file) {
    // Get the size of the file
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    // Read the content into a buffer
    char* buffer = (char*)malloc(size + 1);
    if (buffer == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(buffer, 1, size, file);
    buffer[bytesRead] = '\0'; // Null-terminate the buffer

    // Close the original file
    fclose(file);

    // Convert the content from GBK to UTF-8
    iconv_t cd;
    cd = iconv_open("UTF-8", "GBK");
    if (cd == (iconv_t)-1) {
        perror("iconv_open");
        exit(EXIT_FAILURE);
    }

    // Create a temporary buffer for the converted content
    char* tempBuffer = (char*)malloc(size * 4); // UTF-8 can be up to 4 bytes per character
    if (tempBuffer == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char* inputPtr = buffer;
    char* outputPtr = tempBuffer;
    size_t inputBytesLeft = bytesRead;
    size_t outputBytesLeft = size * 4;

    if (iconv(cd, &inputPtr, &inputBytesLeft, &outputPtr, &outputBytesLeft) == (size_t)-1) {
        perror("iconv");
        exit(EXIT_FAILURE);
    }

    // Close the iconv descriptor
    iconv_close(cd);

    // Reopen the original file for writing
    file = fopen("converted_file.txt", "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Write the converted content back to the file
    fwrite(tempBuffer, 1, size * 4 - outputBytesLeft, file);

    // Close the file and free the buffers
    fclose(file);
    free(buffer);
    free(tempBuffer);
}


int isUtf8(FILE* file) {
    rewind(file); // 将文件指针定位到文件开头

    // 读取文件的前三个字节
    char bom[3];
    size_t bytesRead = fread(bom, 1, 3, file);

    // 如果文件小于3个字节，返回0
    if (bytesRead < 3) {
        rewind(file);
        return 0;
    }

    // 判断是否为UTF-8 without BOM编码
    if (bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF) {
        // 文件包含BOM，不是UTF-8 without BOM编码
        rewind(file);
        return 0;
    } else {
        // 文件不包含BOM，可能是UTF-8 without BOM编码
        rewind(file);
        return 1;
    }
}