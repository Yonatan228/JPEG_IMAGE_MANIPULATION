#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>

int main() {

    int len, size, i = 0;
    double input;
    unsigned char* buffer = NULL;
    FILE* fp = NULL;

    fp = fopen("C:/Users/Yonatan/source/repos/jpg manipulation/original.jpg", "rb");
    if (!fp) {
        printf("an error occured!");
        return 0;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return 0;
    }

    len = ftell(fp);
    rewind(fp);

    buffer = (unsigned char*)malloc(len); // allocate buffer for data
    if (!buffer) {
        fclose(fp);
        return 0;
    }

    while (1) {
        buffer[i++] = fgetc(fp); // copy file into buffer
        if (feof(fp))
            break;
    }
    fclose(fp);

    for (i = 0; i < len; i++) // look for marker 0xffc0
        if ((buffer[i] == 255) && (buffer[i + 1] == 192))
            break;

    printf("Multiply X length by?\n");
    scanf("%lf", &input);

    size = (buffer[i + 5] * 256) + buffer[i + 6]; // calculate y length
    size = size / input; // divide y length by input

    buffer[i + 5] = size / 256; // update y size
    buffer[i + 6] = size % 256;

    size = (buffer[i + 7] * 256) + buffer[i + 8]; // calculate x length
    size = size * input; // multiply x length by input

    buffer[i + 7] = size / 256; // update x size
    buffer[i + 8] = size % 256;

    fp = fopen("C:/Users/Yonatan/source/repos/jpg manipulation/result.jpg", "wb"); // create new jpeg to copy buffer

    for (i = 0; i < len; i++) // copy buffer with new y and x length
        fputc(buffer[i], fp);

    fclose(fp);
    return 0;
}