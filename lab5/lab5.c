#include <stdio.h>
#include <stdlib.h>
#include "lab5.h"

#include <string.h>

#include "../tools/ImagefileHelper.h"

void makeHistogramAndNewImage(char* srcPath, char* imgDstPath,char* histogramDstPath, int T) {
    if(srcPath == NULL) {
        srcPath = "../img/lena.bmp";
    }
    if(histogramDstPath == NULL) {
        histogramDstPath = "../lab5/img/T_hitogram.bmp";
    }
    if(imgDstPath == NULL) {
        imgDstPath = "../lab5/img/T_newImage.bmp";
    }

    BMP8bit  bmp = read8Image(srcPath);
    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数



    int max = 0;            // 存储出现的像素数量的最大值，用于normalization

    int* histogram = (int*)malloc(sizeof(int) * 256);    // 直方图,下标为对应的像素值，值为出现的次数
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    for(int i = 0; i < rowSize * bmp.infoHeader.biHeight; i++) {

        // 统计直方图信息
        histogram[bmp.imageData[i]]++;
        if (histogram[bmp.imageData[i]] > max) {
            max = histogram[bmp.imageData[i]];
        }

        // 二值化
        if(bmp.imageData[i] > T) {
            bmp.imageData[i] = 255;
        } else {
            bmp.imageData[i] = 0;
        }

    }

    //绘制直方图
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
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < histogram[i]; j++)
            temp[j][i] = 0;
    unsigned char histogramData[200 * 256];  // 直方图数据
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < 256; j++) {
            histogramData[i * 256 + j] = temp[i][j];
        }
    }
    // 在直方图中标记阈值
    for(int i = 0; i < 200; i++) histogramData[i * 256 + T] = 150;


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

    // 写入直方图
    BMP8bit histogramBmp;
    histogramBmp.fileHeader = histogramFileHeader;
    histogramBmp.infoHeader = histogramInfoHeader;
    histogramBmp.imageData = histogramData;
    memcpy(histogramBmp.rgbquad, bmp.rgbquad, 1024);
    save8Image(histogramDstPath, histogramBmp);

    //写入新图像
    save8Image(imgDstPath, bmp);
}

void iterate( char* srcPath, char* imgDstPath,char* histogramDstPath) {
    if(srcPath == NULL) {
        srcPath = "../img/lena.bmp";
    }
    if(histogramDstPath == NULL) {
        histogramDstPath = "../lab5/img/iterate_hitogram.bmp";
    }
    if(imgDstPath == NULL) {
        imgDstPath = "../lab5/img/iterate_newImage.bmp";
    }
    BMP8bit  bmp = read8Image(srcPath);

    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数



    // 统计原始直方图信息
    int pixData[255] = {0};
    for(int i = 0 ; i< rowSize * bmp.infoHeader.biHeight; i++) {
        pixData[bmp.imageData[i]]++;
    }
    int T = 128;
    int delta = 0;
    do{
        int m1 = 0, m2 = 0; // 分子
        int n1 = 0, n2 = 0; // 分母
        for( int i = 0; i< 255 ;i ++) {
            if(i < T) {
                m1 += i * pixData[i];
                n1 += pixData[i];
            }
            else {
                m2 += i * pixData[i];
                n2 += pixData[i];
            }
        }
        int newT = 0.5*(m1/n1 + m2/n2);
        delta = abs(newT - T);
        T = newT;
    }while(delta > 1);

    makeHistogramAndNewImage(srcPath,imgDstPath,histogramDstPath,T);

}

void Otsu( char* srcPath, char* imgDstPath, char* histogramDstPath) {
    if(srcPath == NULL) {
        srcPath = "../img/lena.bmp";
    }
    if(histogramDstPath == NULL) {
        histogramDstPath = "../lab5/img/Otsu_hitogram.bmp";
    }
    if(imgDstPath == NULL) {
        imgDstPath = "../lab5/img/Otsu_newImage.bmp";
    }

    BMP8bit bmp = read8Image(srcPath);

    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数


    // 统计原始直方图信息
    int pixData[256] = {0};
    for(int i = 0 ; i< rowSize * bmp.infoHeader.biHeight; i++) {
        pixData[bmp.imageData[i]]++;
    }

    // 统计概率
    double P[256] = {0};
    int allCount = rowSize * bmp.infoHeader.biHeight;
    for(int i = 0 ; i<256; i++) {
        P[i] = (double)pixData[i] / allCount;
    }

    double maxValue = 0;   // 最大类间方差
    int bestT = 0;      // 最佳阈值
    for(int T = 0; T < 255 ;T ++){
        int value = 0;
        double w1 = 0, w2 = 0;
        double u1 = 0, u2 = 0;
        for(int i = 0; i < 255; i++ ) {
            if(i < T) {
                w1 += P[i];
                u1 += i * P[i];
            }
            else {
                w2 += P[i];
                u2 += i * P[i];
            }
        }
        // 当前类间方差
        value = w1 * w2 * (u1 - u2) * (u1 - u2);
        if(value > maxValue) {
            maxValue = value;
            bestT = T;
        }
    }
    makeHistogramAndNewImage(srcPath, imgDstPath, histogramDstPath, bestT);
}
