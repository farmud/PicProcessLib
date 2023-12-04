#include "lab3.h"
#include <stdlib.h>
#include <string.h>
#include "../tools/ImagefileHelper.h"
void avag(char * srcPath, char * dstPath)
{
    if(srcPath == NULL){
        srcPath = "../img/lena.bmp";
    }
    if(dstPath == NULL){
        dstPath = "../lab3/img/avag.bmp";
    }

    BMP8bit bmp = read8Image(srcPath);


    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数



    unsigned char* newImageData = (unsigned char*)malloc(rowSize * bmp.infoHeader.biHeight);   // 用于处理的图像数据
    double conv[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };                                 // 卷积核

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
                    sum += tempData[i+k][j+l] * conv[k][l];
                }
            }
            newImageData[i*rowSize + j] = sum / 9;
        }
    }

    // 保存灰度图片
    BMP8bit newBmp;
    newBmp.fileHeader = bmp.fileHeader;
    newBmp.infoHeader = bmp.infoHeader;
    memcpy(newBmp.rgbquad, bmp.rgbquad, sizeof(bmp.rgbquad));
    newBmp.imageData = newImageData;
    save8Image(dstPath, newBmp);
}


int midPooling(unsigned char ** tempData,int i,int j){
    int arr[9];
    arr[0] = tempData[i-1][j-1];
    arr[1] = tempData[i-1][j];
    arr[2] = tempData[i-1][j+1];
    arr[3] = tempData[i][j-1];
    arr[4] = tempData[i][j];
    arr[5] = tempData[i][j+1];
    arr[6] = tempData[i+1][j-1];
    arr[7] = tempData[i+1][j];
    arr[8] = tempData[i+1][j+1];
    for(int i = 0;i < 9;i ++){
        for(int j = 0;j < 9 - i - 1;j ++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return arr[4];
}

void mid(char * srcPath,char * dstPath){
    if(srcPath==NULL) {
        srcPath="../img/noise.bmp";
    }
    if(dstPath==NULL) {
        dstPath="../lab3/img/mid.bmp";
    }

    BMP8bit bmp = read8Image(srcPath);

    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数




    unsigned char* newImageData = (unsigned char*)malloc(rowSize * bmp.infoHeader.biHeight);   // 用于处理的图像数据

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

    // 中值滤波
    for(int i = 0; i < bmp.infoHeader.biHeight; i ++){
        for(int j = 0;j < rowSize ; j ++){
            newImageData[i*rowSize + j] = midPooling(tempData,i+1,j+1);
        }
    }
    BMP8bit newBmp = bmp;
    newBmp.fileHeader = bmp.fileHeader;
    newBmp.infoHeader = bmp.infoHeader;
    newBmp.imageData = newImageData;
    memcpy(newBmp.rgbquad, bmp.rgbquad, sizeof(bmp.rgbquad));
    save8Image(dstPath,newBmp);
}
