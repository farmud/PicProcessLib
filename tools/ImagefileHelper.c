#include "ImagefileHelper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


BMP8bit read8Image(char *filename) {
    BMP8bit bmp;
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    RGBQUAD rgbquad[256];
    unsigned char* imageData;

    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file\n");
        return ;
    }
    fread(&fileHeader, sizeof(fileHeader), 1, file);    // 读取文件头
    fread(&infoHeader, sizeof(infoHeader), 1, file);    // 读取信息头
    fread(rgbquad, sizeof(rgbquad), 1, file);           // 读取调色板

    int width = ((infoHeader.biWidth * infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数
    int height = infoHeader.biHeight;
    imageData = (unsigned char*)malloc(width * height);   // 图像数据
    fread(imageData, width * height, 1, file);            // 读取图像数据

    bmp.fileHeader = fileHeader;
    bmp.infoHeader = infoHeader;
    memcpy(bmp.rgbquad, rgbquad, sizeof(rgbquad));
    bmp.imageData = imageData;

    fclose(file);

    return bmp;
}


BMP24bit read24Image(char *filename) {
    BMP24bit bmp;
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    unsigned char* imageData;

    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file\n");
        return ;
    }
    fread(&fileHeader, sizeof(fileHeader), 1, file);    // 读取文件头
    fread(&infoHeader, sizeof(infoHeader), 1, file);    // 读取信息头

    int width = ((infoHeader.biWidth * infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数
    int height = infoHeader.biHeight;
    imageData = (unsigned char*)malloc(width * height);   // 图像数据
    fread(imageData, width * height, 1, file);            // 读取图像数据

    bmp.fileHeader = fileHeader;
    bmp.infoHeader = infoHeader;
    bmp.imageData = imageData;

    fclose(file);

    return bmp;
}

void save8Image(char *filename, BMP8bit bmp) {
    FILE *f=fopen(filename,"wb");
    if(f==NULL){
        perror("can not open file!");
        return;
    }

    fwrite(&bmp.fileHeader,sizeof(bmp.fileHeader),1,f);
    fwrite(&bmp.infoHeader,sizeof(bmp.infoHeader),1,f);
    fwrite(bmp.rgbquad,1024,1,f);
    fwrite(bmp.imageData,sizeof(unsigned char)*bmp.infoHeader.biSizeImage,1,f);
    fclose(f);
}





