
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
    FILE* file = fopen("../pic/lena.bmp", "rb");
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

    unsigned char *newImageData1 = (unsigned char*)malloc(rowSize * infoHeader.biHeight);
    unsigned char *newImageData2 = (unsigned char*)malloc(rowSize * infoHeader.biHeight);

    for(int i = 0; i< infoHeader.biHeight ; i ++) {
        for(int j = 0; j < rowSize ; j ++ ) {
            newImageData1[i*rowSize+j]=imageData[i*rowSize+rowSize-j-1];
            newImageData2[i*rowSize+j]=imageData[(infoHeader.biHeight-i-1)*rowSize+j];
        }
    }



    // 写入文件
    char savePath1[]="../lab4/ProcessedPic/mirror1.bmp";
    char savePath2[]="../lab4/ProcessedPic/mirror2.bmp";
    FILE *f1=fopen(savePath1,"wb");
    FILE *f2=fopen(savePath2,"wb");
    if(f1==NULL || f2 == NULL){
        perror("can not open file!");
        return -2;
    }
    fwrite(&fileHeader,sizeof(fileHeader),1,f1);
    fwrite(&infoHeader,sizeof(infoHeader),1,f1);
    fwrite(rgbquad,1024,1,f1);
    fwrite(newImageData1,sizeof(unsigned char)*infoHeader.biSizeImage,1,f1);
    fwrite(&fileHeader,sizeof(fileHeader),1,f2);
    fwrite(&infoHeader,sizeof(infoHeader),1,f2);
    fwrite(rgbquad,1024,1,f2);
    fwrite(newImageData2,sizeof(unsigned char)*infoHeader.biSizeImage,1,f2);

    fclose(f1);
    fclose(f2);
    free(imageData);
    fclose(file);
    free(newImageData1);
    free(newImageData2);
}

