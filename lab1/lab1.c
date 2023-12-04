#include <stdlib.h>
#include <string.h>
#include "../tools/ImagefileHelper.h"

void grayProcess(char* srcPath, char* dstPath) {
    // 默认处理
    if(srcPath == NULL){
        srcPath = "../img/rgb.bmp";
    }
    if(dstPath == NULL){
        dstPath = "../lab1/img/GrayRGB.bmp";
    }
    BMP24bit bmp = read24Image(srcPath);
    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;
    // 编写调色板
    RGBQUAD rgbquad[256];
    for (int i = 0; i < 256; i++) {
        rgbquad[i].rgbBlue = (unsigned char)i;
        rgbquad[i].rgbGreen = (unsigned char)i;
        rgbquad[i].rgbRed = (unsigned char)i;
        rgbquad[i].rgbReserved = (unsigned char)0;
    }
    // 更改文件头信息
    bmp.infoHeader.biBitCount = 8;                                                          // 位数改为8
    int newRowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;      // 每行像素所占字节数
    bmp.fileHeader.bfOffBits = sizeof(bmp.fileHeader) + sizeof(bmp.infoHeader) + sizeof(rgbquad);  // 偏移量
    bmp.fileHeader.bfsize = bmp.fileHeader.bfOffBits + newRowSize * bmp.infoHeader.biHeight;        // 文件大小
    // 更改信息头信息
    bmp.infoHeader.biSizeImage = newRowSize * bmp.infoHeader.biHeight;                          // 图像数据大小
    unsigned char * returnImageData = (unsigned char*)malloc(bmp.infoHeader.biSizeImage);  // 用于返回的图像数据
    // // 改为灰度图
    for(int i = 0;i<bmp.infoHeader.biHeight;i++){
        for(int j = 0;j<bmp.infoHeader.biWidth;j++){
            int index = i * rowSize + j * 3;
            int gray = 0.114*bmp.imageData[index] + 0.587*bmp.imageData[index+1] + 0.299*bmp.imageData[index+2];
            returnImageData[i * newRowSize + j] = gray;
        }
    }
    BMP8bit returnBmp;
    returnBmp.fileHeader = bmp.fileHeader;
    returnBmp.infoHeader = bmp.infoHeader;
    memcpy(returnBmp.rgbquad, rgbquad, sizeof(rgbquad));
    returnBmp.imageData = returnImageData;
    save8Image(dstPath, returnBmp);
}

void reverseProcess(char *srcPath, char *dstPath) {
    // 默认处理
    if(srcPath == NULL){
        srcPath = "../img/GrayRGB.bmp";
    }
    if(dstPath == NULL){
        dstPath = "../lab1/img/ReverseRGB.bmp";
    }
    BMP8bit bmp = read8Image(srcPath);
    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数
    // 反色
    for (int i = 0; i < rowSize * bmp.infoHeader.biHeight; i++) {
        bmp.imageData[i] = 255 - bmp.imageData[i];
    }
    // 保存反色图文件
    save8Image(dstPath, bmp);
}

void depatureRGB(char *srcPath, char *dstPathB, char *dstPathG, char *dstPathR) {
    if(srcPath == NULL){
        srcPath = "../img/rgb.bmp";
    }
    if(dstPathB == NULL){
        dstPathB = "../lab1/img/B.bmp";
    }
    if(dstPathG == NULL){
        dstPathG = "../lab1/img/G.bmp";
    }
    if(dstPathR == NULL){
        dstPathR = "../lab1/img/R.bmp";
    }

    BMP24bit bmp = read24Image(srcPath);
    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数

    // 编写调色板
    RGBQUAD rgbquad[256];
    for (int i = 0; i < 256; i++) {
        rgbquad[i].rgbBlue = (unsigned char)i;
        rgbquad[i].rgbGreen = (unsigned char)i;
        rgbquad[i].rgbRed = (unsigned char)i;
        rgbquad[i].rgbReserved = (unsigned char)0;
    }

    // 更改文件头信息
    bmp.infoHeader.biBitCount = 8;                                                          // 位数改为8
    int newRowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;      // 每行像素所占字节数

    bmp.fileHeader.bfOffBits = sizeof(bmp.fileHeader) + sizeof(bmp.infoHeader) + sizeof(rgbquad);  // 偏移量
    bmp.fileHeader.bfsize = bmp.fileHeader.bfOffBits + newRowSize * bmp.infoHeader.biHeight;        // 文件大小

    // 更改信息头信息
    bmp.infoHeader.biSizeImage = newRowSize * bmp.infoHeader.biHeight;                          // 图像数据大小

    unsigned char * BImageData = (unsigned char*)malloc(bmp.infoHeader.biSizeImage);    // B通道
    unsigned char * GImageData = (unsigned char*)malloc(bmp.infoHeader.biSizeImage);    // G通道
    unsigned char * RImageData = (unsigned char*)malloc(bmp.infoHeader.biSizeImage);    // R通道

    // 分离RGB通道
    for(int i = 0;i<bmp.infoHeader.biHeight;i++){
        for(int j = 0;j<bmp.infoHeader.biWidth;j++){
            int index = i * rowSize + j * 3;
            BImageData[i * newRowSize + j] = bmp.imageData[index];
            GImageData[i * newRowSize + j] = bmp.imageData[index + 1];
            RImageData[i * newRowSize + j] = bmp.imageData[index + 2];
        }
    }

    BMP8bit Bbmp;
    BMP8bit Gbmp;
    BMP8bit Rbmp;
    Bbmp.fileHeader = bmp.fileHeader;
    Bbmp.infoHeader = bmp.infoHeader;
    memcpy(Bbmp.rgbquad, rgbquad, sizeof(rgbquad));
    Bbmp.imageData = BImageData;

    Gbmp.fileHeader = bmp.fileHeader;
    Gbmp.infoHeader = bmp.infoHeader;
    memcpy(Gbmp.rgbquad, rgbquad, sizeof(rgbquad));
    Gbmp.imageData = GImageData;

    Rbmp.fileHeader = bmp.fileHeader;
    Rbmp.infoHeader = bmp.infoHeader;
    memcpy(Rbmp.rgbquad, rgbquad, sizeof(rgbquad));
    Rbmp.imageData = RImageData;

    save8Image(dstPathB,Bbmp);
    save8Image(dstPathG,Gbmp);
    save8Image(dstPathR,Rbmp);

}
