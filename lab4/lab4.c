#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tools/ImagefileHelper.h"
#include "lab4.h"

#include <math.h>

void mirror(char * srcPath, char* dstPath1,char* dstPath2)
{
    if(srcPath == NULL) {
        srcPath = "../img/lena.bmp";
    }
    if(dstPath1 == NULL) {
        dstPath1 = "../lab4/img/mirror1.bmp";
    }
    if(dstPath2 == NULL) {
        dstPath2 = "../lab4/img/mirror2.bmp";
    }
    BMP8bit bmp = read8Image(srcPath);
    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数

    unsigned char *newImageData1 = (unsigned char*)malloc(rowSize * bmp.infoHeader.biHeight);
    unsigned char *newImageData2 = (unsigned char*)malloc(rowSize * bmp.infoHeader.biHeight);

    for(int i = 0; i< bmp.infoHeader.biHeight ; i ++) {
        for(int j = 0; j < rowSize ; j ++ ) {
            newImageData1[i*rowSize+j]=bmp.imageData[i*rowSize+rowSize-j-1];
            newImageData2[i*rowSize+j]=bmp.imageData[(bmp.infoHeader.biHeight-i-1)*rowSize+j];
        }
    }
    // 写入文件
    BMP8bit newBmp1 = bmp;
    newBmp1.imageData = newImageData1;
    newBmp1.fileHeader = bmp.fileHeader;
    newBmp1.infoHeader = bmp.infoHeader;
    memcpy(newBmp1.rgbquad, bmp.rgbquad, sizeof(bmp.rgbquad));
    save8Image(dstPath1, newBmp1);

    BMP8bit newBmp2 = bmp;
    newBmp2.imageData = newImageData2;
    newBmp2.fileHeader = bmp.fileHeader;
    newBmp2.infoHeader = bmp.infoHeader;
    memcpy(newBmp2.rgbquad, bmp.rgbquad, sizeof(bmp.rgbquad));
    save8Image(dstPath2, newBmp2);
}

void shrink(char* srcPath, char* dstPath)
{
    if(srcPath == NULL) {
        srcPath = "../img/lena.bmp";
    }
    if(dstPath == NULL) {
        dstPath = "../lab4/img/shrink.bmp";
    }
    BMP8bit bmp = read8Image(srcPath);
    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数


    const float rate = 2; // 缩小倍数

    int newWidth = bmp.infoHeader.biWidth / rate;
    int newHeight = bmp.infoHeader.biHeight / rate;
    unsigned char* newImageData = (unsigned char*)malloc(newWidth*newHeight);   // 用于处理的图像数据
    for(int i = 0;i < newHeight;i ++){
        for(int j = 0;j < newWidth;j ++){
            newImageData[i*newWidth+j] = bmp.imageData[(int)(i*rate*rowSize+j*rate)];
        }
    }
    BITMAPFILEHEADER newFileHeader;
    BITMAPINFOHEADER newInfoHeader;
    // 写入文件头
    newFileHeader.bfType[0] = 'B';
    newFileHeader.bfType[1] = 'M';
    newFileHeader.bfsize = 54 + 1024 + newWidth * newHeight;
    newFileHeader.bfReserved = 0;
    newFileHeader.bfOffBits = 54 + 1024;
    // 写入信息头
    newInfoHeader.biSize = 40;
    newInfoHeader.biWidth = newWidth;
    newInfoHeader.biHeight = newHeight;
    newInfoHeader.biPlanes = 1;
    newInfoHeader.biBitCount = 8;
    newInfoHeader.biCompression = 0;
    newInfoHeader.biSizeImage = newWidth * newHeight;
    newInfoHeader.biXPixelsPerMeter = 0;
    newInfoHeader.biYPixelsPerMeter = 0;
    newInfoHeader.biCirsUsed = 0;
    newInfoHeader.biClrImportant = 0;

    // 写入文件
    BMP8bit newBmp;
    newBmp.fileHeader = newFileHeader;
    newBmp.infoHeader = newInfoHeader;
    newBmp.imageData = newImageData;
    memcpy(newBmp.rgbquad, bmp.rgbquad, 1024);
    save8Image(dstPath, newBmp);

}

void translate(char * srcPath, char* dstPath)
{
    if(srcPath == NULL) {
        srcPath = "../img/lena.bmp";
    }
    if(dstPath == NULL) {
        dstPath = "../lab4/img/translate.bmp";
    }

    BMP8bit bmp = read8Image(srcPath);

    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数

    const int dx = 100, dy = 100; // 平移距离
    unsigned char *newImageData = (unsigned char*)malloc(rowSize * bmp.infoHeader.biHeight);

    for(int i = 0; i< bmp.infoHeader.biHeight ; i ++) {
        for(int j = 0; j < rowSize ; j ++ ) {
            int index = (i - dx) * rowSize + (j - dy );
            if(index >= 0 && index < rowSize * bmp.infoHeader.biHeight && i >= dy && j >= dx) {
                newImageData[i * rowSize + j] = bmp.imageData[index];
            }
            else newImageData[i * rowSize + j] = 255;
        }
    }

    // 写入文件
    BMP8bit newBmp = bmp;
    newBmp.imageData = newImageData;
    newBmp.fileHeader = bmp.fileHeader;
    newBmp.infoHeader = bmp.infoHeader;
    memcpy(newBmp.rgbquad, bmp.rgbquad, 1024);
    save8Image(dstPath, newBmp);
}

void revolve(char * srcPath, char* dstPath)
{
    if(srcPath == NULL) {
        srcPath = "../img/lena.bmp";
    }
    if(dstPath == NULL) {
        dstPath = "../lab4/img/revolve.bmp";
    }
    BMP8bit bmp = read8Image(srcPath);

    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数

    unsigned char *newImageData = (unsigned char*)malloc(rowSize * bmp.infoHeader.biHeight);

    const double theta = -5* M_PI / 12; // 旋转角度
    const double sinx = sin(theta);
    const double cosx = cos(theta);

    // 旋转中心
    const int midx = bmp.infoHeader.biWidth / 2;
    const int midy = bmp.infoHeader.biHeight / 2;

    for(int i = 0; i< bmp.infoHeader.biHeight ; i ++) {
        for(int j = 0; j < rowSize ; j ++ ) {

            int x0 = (int)(cosx * (j - midx) + sinx * (i - midy) + midx);
            int y0 = (int)(-sinx * (j - midx) + cosx * (i - midy) + midy);

            if(x0 >= 0 && x0 < bmp.infoHeader.biWidth && y0 >= 0 && y0 < bmp.infoHeader.biHeight)
                newImageData[i * rowSize + j] = bmp.imageData[y0 * rowSize + x0];
            else
                newImageData[i*rowSize+j] = 255;

        }
    }

    // 写入文件
    BMP8bit newBmp = bmp;
    newBmp.imageData = newImageData;
    newBmp.fileHeader = bmp.fileHeader;
    newBmp.infoHeader = bmp.infoHeader;
    memcpy(newBmp.rgbquad, bmp.rgbquad, sizeof(bmp.rgbquad));
    save8Image(dstPath, newBmp);
}


