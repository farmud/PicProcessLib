#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)

// 位图的文件头
typedef struct {
    char bfType[2];      // "BM"
    int bfsize;           // bfSize
    int bfReserved;        // 有两个保留字：1，2
    int bfOffBits;         // 偏移量
} BITMAPFILEHEADER;


// 位图信息头
typedef struct {
    int biSize;                 // 结构体长度
    int biWidth;                // 宽度
    int biHeight;               // 高度
    short biPlanes;             // 位平面数，必须为1
    short biBitCount;           // 颜色位数, x标识x/8个字节存储1个像素信息
    unsigned biCompression;     // 是否压缩
    unsigned biSizeImage;       // 实际位图数据占用的字节数
    int biXPixelsPerMeter;      // 目标设备水平分辨率
    int biYPixelsPerMeter;      // 目标设备垂直分辨率
    int biCirsUsed;             // 实际使用的颜色数
    int biClrImportant;         // 重要颜色数
} BITMAPINFOHEADER;

// 调色板
typedef struct {
    unsigned char rgbBlue;      // 蓝色分量
    unsigned char rgbGreen;     // 绿色分量
    unsigned char rgbRed;       // 红色分量
    unsigned char rgbReserved;  // 保留值
} RGBQUAD;

#pragma pack(pop)

int main()
{
    FILE* file = fopen("E:/myLab/PicProcessLib/pic/dim.bmp", "rb");
    if (!file) {
        printf("Failed to open file\n");
        return 1;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    RGBQUAD rgbquad[256];

    fread(&fileHeader, sizeof(fileHeader), 1, file);    // 读取文件头
    fread(&infoHeader, sizeof(infoHeader), 1, file);    // 读取信息头

    int rowSize = ((infoHeader.biWidth * infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数

    fread(rgbquad, 1024, 1, file);                                                      // 读取调色板

    unsigned char* imageData = (unsigned char*)malloc(rowSize * infoHeader.biHeight);   // 图像数据
    fread(imageData, rowSize * infoHeader.biHeight, 1, file);                           // 读取图像数据

    int max = 0;            // 存储出现的像素数量的最大值，用于normalization

    int* histogram = (int*)malloc(sizeof(int) * 256);    // 直方图,下标为对应的像素值，值为出现的次数
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    for(int i = 0; i < rowSize * infoHeader.biHeight; i++) {
        histogram[imageData[i]]++;
        if (histogram[imageData[i]] > max) {
            max = histogram[imageData[i]];
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
    histogramInfoHeader.biCompression = infoHeader.biCompression;
    histogramInfoHeader.biSizeImage = 200 * 256;
    histogramInfoHeader.biXPixelsPerMeter = infoHeader.biXPixelsPerMeter;
    histogramInfoHeader.biYPixelsPerMeter = infoHeader.biYPixelsPerMeter;
    histogramInfoHeader.biCirsUsed = 0;
    histogramInfoHeader.biClrImportant = 0;

    // 保存直方图文件
    char savePath[]="E:/myLab/PicProcessLib/lab2/ProcessedPic/Histogram.bmp";
    FILE *f=fopen(savePath,"wb");
    if(f==NULL){
    perror("can not open file!");
    return -2;
    }
    fwrite(&histogramFileHeader,sizeof(histogramFileHeader),1,f);
    fwrite(&histogramInfoHeader,sizeof(histogramInfoHeader),1,f);
    fwrite(rgbquad,1024,1,f);
    fwrite(histogramData,200 * 256,1,f);
    fclose(f);

    fclose(file);

    
}
