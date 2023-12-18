#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"../tools/ImagefileHelper.h"
#include "lab7.h"

void prewitt(char* srcPath, char* dstPath)
{
    if(srcPath == NULL) {
        srcPath = "../img/lena.bmp";
    }
    if(dstPath == NULL) {
        dstPath = "../lab7/img/prewitt.bmp";
    }
    BMP8bit  bmp = read8Image(srcPath);


    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数


    unsigned char* newImageData = (unsigned char*)malloc(rowSize * bmp.infoHeader.biHeight);   // 用于处理的图像数据
    int conv1[3][3] = { {-1,-1,-1},{0,0,0},{1,1,1}};                                 // 卷积核
    int conv2[3][3] = { {-1,0,1},{-1,0,1},{-1,0,1}};                                 // 卷积核

    // 动态生成二维数组
    unsigned char ** tempData = (unsigned char **)malloc(sizeof(unsigned char *) * (bmp.infoHeader.biHeight+2));
    for (int i = 0; i < bmp.infoHeader.biHeight+2 ; i++) {
        tempData[i] = (unsigned char *)malloc(sizeof(unsigned char) * (rowSize+2));
    }

    // 将图像数据拷贝到tempData中
    for (int i = 0; i < bmp.infoHeader.biHeight; i++) {
        for (int j = 0; j < rowSize; j++) {
            tempData[i+1][j+1] = bmp.imageData[i*rowSize + j];
        }
    }
    // 对边界进行处理，使其扩充为相邻的像素值
    for (int i = 0; i < bmp.infoHeader.biHeight; i++) {
        tempData[i+1][0] = tempData[i+1][1];
        tempData[i+1][rowSize+1] = tempData[i+1][rowSize];
    }
    for (int i = 0; i < rowSize; i++) {
        tempData[0][i+1] = tempData[1][i+1];
        tempData[bmp.infoHeader.biHeight+1][i+1] = tempData[bmp.infoHeader.biHeight][i+1];
    }
    tempData[0][0] = tempData[0][1];
    tempData[0][rowSize+1] = tempData[0][rowSize];
    tempData[bmp.infoHeader.biHeight+1][0] = tempData[bmp.infoHeader.biHeight+1][1];
    tempData[bmp.infoHeader.biHeight+1][rowSize+1] = tempData[bmp.infoHeader.biHeight+1][rowSize];

    // 卷积操作
    for (int i = 0; i < bmp.infoHeader.biHeight; i++) {
        for (int j = 0; j < rowSize; j++) {
            double sum = 0;
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++){
                    sum += tempData[i+k][j+l] * conv1[k][l];
                    sum += tempData[i+k][j+l] * conv2[k][l];
                }
            }
            // 阈值化处理
            if(sum > 128)
                newImageData[i*rowSize + j] = 255;
            else
                newImageData[i*rowSize + j] = 0;
        }
    }
    BMP8bit newBmp = bmp;
    newBmp.imageData = newImageData;
    newBmp.fileHeader = bmp.fileHeader;
    newBmp.infoHeader = bmp.infoHeader;
    memcpy(newBmp.rgbquad, bmp.rgbquad, sizeof(RGBQUAD) * 256);
    save8Image(dstPath, newBmp);
}

void sobel(char * srcPath, char * dstPath)
{
    if(srcPath == NULL) {
        srcPath = "../img/lena.bmp";
    }
    if(dstPath == NULL) {
        dstPath = "../lab7/img/sobel.bmp";
    }

    BMP8bit  bmp = read8Image(srcPath);

    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数



    unsigned char* newImageData = (unsigned char*)malloc(rowSize * bmp.infoHeader.biHeight);   // 用于处理的图像数据
    int conv1[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1}};                                 // 卷积核
    int conv2[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1}};                                 // 卷积核

    // 动态生成二维数组
    unsigned char ** tempData = (unsigned char **)malloc(sizeof(unsigned char *) * (bmp.infoHeader.biHeight+2));
    for (int i = 0; i < bmp.infoHeader.biHeight+2 ; i++) {
        tempData[i] = (unsigned char *)malloc(sizeof(unsigned char) * (rowSize+2));
    }

    // 将图像数据拷贝到tempData中
    for (int i = 0; i < bmp.infoHeader.biHeight; i++) {
        for (int j = 0; j < rowSize; j++) {
            tempData[i+1][j+1] = bmp.imageData[i*rowSize + j];
        }
    }
    // 对边界进行处理，使其扩充为相邻的像素值
    for (int i = 0; i < bmp.infoHeader.biHeight; i++) {
        tempData[i+1][0] = tempData[i+1][1];
        tempData[i+1][rowSize+1] = tempData[i+1][rowSize];
    }
    for (int i = 0; i < rowSize; i++) {
        tempData[0][i+1] = tempData[1][i+1];
        tempData[bmp.infoHeader.biHeight+1][i+1] = tempData[bmp.infoHeader.biHeight][i+1];
    }
    tempData[0][0] = tempData[0][1];
    tempData[0][rowSize+1] = tempData[0][rowSize];
    tempData[bmp.infoHeader.biHeight+1][0] = tempData[bmp.infoHeader.biHeight+1][1];
    tempData[bmp.infoHeader.biHeight+1][rowSize+1] = tempData[bmp.infoHeader.biHeight+1][rowSize];

    // 卷积操作
    for (int i = 0; i < bmp.infoHeader.biHeight; i++) {
        for (int j = 0; j < rowSize; j++) {
            double sum = 0;
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++){
                    sum += tempData[i+k][j+l] * conv1[k][l];
                    sum += tempData[i+k][j+l] * conv2[k][l];
                }
            }
            // 阈值化处理
            if(sum > 128)
                newImageData[i*rowSize + j] = 255;
            else
                newImageData[i*rowSize + j] = 0;
        }
    }

    BMP8bit newBmp = bmp;
    newBmp.imageData = newImageData;
    newBmp.fileHeader = bmp.fileHeader;
    newBmp.infoHeader = bmp.infoHeader;
    memcpy(newBmp.rgbquad, bmp.rgbquad, sizeof(RGBQUAD) * 256);
    save8Image(dstPath, newBmp);

}

void LOG(char * srcPath, char * dstPath)
{
    if(srcPath == NULL) {
        srcPath = "../img/lena.bmp";
    }
    if(dstPath == NULL) {
        dstPath = "../lab7/img/LOG.bmp";
    }

    BMP8bit  bmp = read8Image(srcPath);

    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数



    unsigned char* newImageData = (unsigned char*)malloc(rowSize * bmp.infoHeader.biHeight);   // 用于处理的图像数据
    int conv[5][5] = {{0,0,-1,0,0},
                       {0,-1,-2,-1,0},
                       {-1,-2,16,-2,-1},
                       {0,-1,-2,-1,0},
                       {0,0,-1,0,0}};                                 // 卷积核

    // 动态生成二维数组
    unsigned char ** tempData = (unsigned char **)malloc(sizeof(unsigned char *) * (bmp.infoHeader.biHeight+4));
    for (int i = 0; i < bmp.infoHeader.biHeight+4 ; i++) {
        tempData[i] = (unsigned char *)malloc(sizeof(unsigned char) * (rowSize+4));
    }
    // 初始化
    for (int i = 0; i < bmp.infoHeader.biHeight+4; i++) {
        for (int j = 0; j < rowSize+4; j++) {
            tempData[i][j] = 0;
        }
    }

    // 将图像数据拷贝到tempData中
    for (int i = 0; i < bmp.infoHeader.biHeight; i++) {
        for (int j = 0; j < rowSize; j++) {
            tempData[i+2][j+2] = bmp.imageData[i*rowSize + j];
        }
    }
    // 对边界进行处理，使其扩充为相邻的像素值
    for (int i = 0; i < bmp.infoHeader.biHeight; i++) {
        // 左右两边
        tempData[i+2][1] = tempData[i+2][2];
        tempData[i+2][0] = tempData[i+2][2];

        tempData[i+2][rowSize+2] = tempData[i+2][rowSize+1];
        tempData[i+2][rowSize+3] = tempData[i+2][rowSize+1];
    }
    for (int i = 0; i < rowSize; i++) {
        // 上下两边
        tempData[0][i+2] = tempData[2][i+2];
        tempData[1][i+2] = tempData[2][i+2];

        tempData[bmp.infoHeader.biHeight+2][i+2] = tempData[bmp.infoHeader.biHeight+1][i+2];
        tempData[bmp.infoHeader.biHeight+3][i+2] = tempData[bmp.infoHeader.biHeight+1][i+2];
    }
    // 四个角,每个角有四个点
    tempData[0][0] = tempData[2][2];
    tempData[0][1] = tempData[2][2];
    tempData[1][0] = tempData[2][2];
    tempData[1][1] = tempData[2][2];

    tempData[0][rowSize+2] = tempData[2][rowSize+1];
    tempData[0][rowSize+3] = tempData[2][rowSize+1];
    tempData[1][rowSize+2] = tempData[2][rowSize+1];
    tempData[1][rowSize+3] = tempData[2][rowSize+1];

    tempData[bmp.infoHeader.biHeight+2][0] = tempData[bmp.infoHeader.biHeight+1][2];
    tempData[bmp.infoHeader.biHeight+2][1] = tempData[bmp.infoHeader.biHeight+1][2];
    tempData[bmp.infoHeader.biHeight+3][0] = tempData[bmp.infoHeader.biHeight+1][2];
    tempData[bmp.infoHeader.biHeight+3][1] = tempData[bmp.infoHeader.biHeight+1][2];

    tempData[bmp.infoHeader.biHeight+2][rowSize+2] = tempData[bmp.infoHeader.biHeight+1][rowSize+1];
    tempData[bmp.infoHeader.biHeight+2][rowSize+3] = tempData[bmp.infoHeader.biHeight+1][rowSize+1];
    tempData[bmp.infoHeader.biHeight+3][rowSize+2] = tempData[bmp.infoHeader.biHeight+1][rowSize+1];
    tempData[bmp.infoHeader.biHeight+3][rowSize+3] = tempData[bmp.infoHeader.biHeight+1][rowSize+1];

    // 卷积操作
    for (int i = 0; i < bmp.infoHeader.biHeight; i++) {
        for (int j = 0; j < rowSize; j++) {
            double sum = 0;
            for (int k = 0; k < 5; k++) {
                for (int l = 0; l < 5; l++){
                    sum += tempData[i+k][j+l] * conv[k][l];
                }
            }
            // 阈值化处理
            if(sum > 200)
                newImageData[i*rowSize + j] = 255;
            else
                newImageData[i*rowSize + j] = 0;
        }
    }

    BMP8bit newBmp = bmp;
    newBmp.imageData = newImageData;
    newBmp.fileHeader = bmp.fileHeader;
    newBmp.infoHeader = bmp.infoHeader;
    memcpy(newBmp.rgbquad, bmp.rgbquad, sizeof(RGBQUAD) * 256);
    save8Image(dstPath, newBmp);
}