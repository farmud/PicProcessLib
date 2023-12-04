#include "lab2.h"

#include <stdlib.h>
#include <string.h>
#include "../tools/ImagefileHelper.h"

void makeHistogram(char *srcPath, char *dstPath)
{
    if(srcPath == NULL){
        srcPath = "../img/dim.bmp";
    }
    if(dstPath == NULL){
        dstPath = "../lab2/img/Histogram.bmp";
    }
    BMP8bit bmp = read8Image(srcPath);
    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数
    int max = 0;            // 存储出现的像素数量的最大值，用于normalization
    int histogram[256];    // 直方图,下标为对应的像素值，值为出现的次数
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }
    for(int i = 0; i < rowSize * bmp.infoHeader.biHeight; i++) {
        histogram[bmp.imageData[i]]++;
        if (histogram[bmp.imageData[i]] > max) {
            max = histogram[bmp.imageData[i]];
        }
    }
    double rate = 200.0 / max;  // normalization的比例
    // 归一化
    for(int i = 0; i < 256; i++) {
        histogram[i] = (int)(histogram[i] * rate);
    }
    unsigned char temp [200][256];  // 用于存储直方图
    // 初始化成全白色
    for(int i = 0; i< 256;i++){
        for(int j = 0;j<200;j++){
            temp[j][i] = 255;
        }
    }
    for(int i = 0; i < 256; i++) {
        for(int j = 0; j < histogram[i]; j++) {
            temp[j][i] = 0;
        }
    }
    unsigned char histogramData[200 * 256];  // 直方图数据
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < 256; j++) {
            histogramData[i * 256 + j] = temp[i][j];
        }
    }
    BITMAPFILEHEADER histogramFileHeader;
    BITMAPINFOHEADER histogramInfoHeader;

    // 直方图文件头
    histogramFileHeader.bfType[0] = 'B';
    histogramFileHeader.bfType[1] = 'M';
    histogramFileHeader.bfsize = 200 * 256 + 14 + 40 + 1024;
    histogramFileHeader.bfReserved = 0;
    histogramFileHeader.bfOffBits = 14 + 40 + 1024;

    // 直方图信息头
    histogramInfoHeader.biSize = 40;
    histogramInfoHeader.biWidth = 256;
    histogramInfoHeader.biHeight = 200;
    histogramInfoHeader.biPlanes = 1;
    histogramInfoHeader.biBitCount = 8;
    histogramInfoHeader.biCompression = bmp.infoHeader.biCompression;
    histogramInfoHeader.biSizeImage = 200 * 256;
    histogramInfoHeader.biXPixelsPerMeter = bmp.infoHeader.biXPixelsPerMeter;
    histogramInfoHeader.biYPixelsPerMeter = bmp.infoHeader.biYPixelsPerMeter;
    histogramInfoHeader.biCirsUsed = 0;
    histogramInfoHeader.biClrImportant = 0;

    // 写入文件
    BMP8bit histogramBmp;
    histogramBmp.fileHeader = histogramFileHeader;
    histogramBmp.infoHeader = histogramInfoHeader;
    memcpy(histogramBmp.rgbquad, bmp.rgbquad, sizeof(bmp.rgbquad));
    histogramBmp.imageData = histogramData;
    save8Image(dstPath, histogramBmp);
}

void  histogramEqualization(char *srcPath, char *dstPath)
{
    if(srcPath == NULL){
        srcPath = "../img/dim.bmp";
    }
    if(dstPath == NULL){
        dstPath = "../lab2/img/Equalization.bmp";
    }
    BMP8bit bmp =  read8Image(srcPath);

    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数

    int max = 0;                // 存储出现的像素数量的最大值，用于normalization

    int* histogram = malloc(sizeof(int) * 256);    // 直方图,下标为对应的像素值，值为出现的次数
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    for(int i = 0; i < rowSize * bmp.infoHeader.biHeight; i++) {
        histogram[bmp.imageData[i]]++;
    }

    // 储存每个像素值出现的概率
    double rate[256] = {0};
    for(int i = 0;i< 256;i++){
        rate[i] = histogram[i] *1.0 / (rowSize * bmp.infoHeader.biHeight);
    }

    // 储存每个像素值的累计概率
    double sum[256] = {0};
    sum[0] = rate[0];
    for(int i = 1;i< 256;i++){
        sum[i] = sum[i-1] + rate[i];
    }

    // 储存每个像素值的新值
    int newPixel[256] = {0};
    for(int i = 0;i< 256;i++){
        newPixel[i] = (int)(sum[i] * 255);
    }

    // 生成新的图像数据
    unsigned char* newImageData = (unsigned char*)malloc(rowSize * bmp.infoHeader.biHeight);
    for(int i = 0;i< rowSize * bmp.infoHeader.biHeight;i++){
        newImageData[i] = newPixel[bmp.imageData[i]];
    }


    // 保存灰度图片
    BMP8bit newBmp;
    newBmp.fileHeader = bmp.fileHeader;
    newBmp.infoHeader = bmp.infoHeader;
    memcpy(newBmp.rgbquad, bmp.rgbquad, sizeof(bmp.rgbquad));
    newBmp.imageData = newImageData;
    save8Image(dstPath, newBmp);


}
