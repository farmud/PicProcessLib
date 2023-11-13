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


int main() {
    FILE* file = fopen("E:/myLab/PicProcessLib/lab1/ProcessedPic/GrayRGB.bmp", "rb");
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
    unsigned char* imageData = (unsigned char*)malloc(rowSize * infoHeader.biHeight);   // 图像数据

    fread(rgbquad, 1024, 1, file);                                                      // 读取调色板
    fread(imageData, rowSize * infoHeader.biHeight, 1, file);                           // 读取图像数据


    // 反色
    for (int i = 0; i < rowSize * infoHeader.biHeight; i++) {
        imageData[i] = 255 - imageData[i];
    }

    // 保存反色图文件
    char savePath[]="E:/myLab/PicProcessLib/lab1/ProcessedPic/ReverseRGB.bmp";
    FILE *f=fopen(savePath,"wb");
    if(f==NULL){
    perror("can not open file!");
    return -2;
    }

    fwrite(&fileHeader,sizeof(fileHeader),1,f);
    fwrite(&infoHeader,sizeof(infoHeader),1,f);
    fwrite(rgbquad,1024,1,f);
    fwrite(imageData,sizeof(unsigned char)*infoHeader.biSizeImage,1,f);
    fclose(f);
    



    free(imageData);
    fclose(file);

    return 0;
}