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


    unsigned char* newImageData = (unsigned char*)malloc(rowSize * infoHeader.biHeight);   // 用于处理的图像数据
    int conv1[3][3] = { {-1,-1,-1},{0,0,0},{1,1,1}};                                 // 卷积核
    int conv2[3][3] = { {-1,0,1},{-1,0,1},{-1,0,1}};                                 // 卷积核

    // 动态生成二维数组
    unsigned char ** tempData = (unsigned char **)malloc(sizeof(unsigned char *) * (infoHeader.biHeight+2));
    for (int i = 0; i < infoHeader.biHeight+2 ; i++) {
        tempData[i] = (unsigned char *)malloc(sizeof(unsigned char) * (rowSize+2));
    }

    // 将图像数据拷贝到tempData中
    for (int i = 0; i < infoHeader.biHeight; i++) {
        for (int j = 0; j < rowSize; j++) {
            tempData[i+1][j+1] = imageData[i*rowSize + j];
        }
    }
    // 对边界进行处理，使其扩充为相邻的像素值
    for (int i = 0; i < infoHeader.biHeight; i++) {
        tempData[i+1][0] = tempData[i+1][1];
        tempData[i+1][rowSize+1] = tempData[i+1][rowSize];
    }
    for (int i = 0; i < rowSize; i++) {
        tempData[0][i+1] = tempData[1][i+1];
        tempData[infoHeader.biHeight+1][i+1] = tempData[infoHeader.biHeight][i+1];
    }
    tempData[0][0] = tempData[0][1];
    tempData[0][rowSize+1] = tempData[0][rowSize];
    tempData[infoHeader.biHeight+1][0] = tempData[infoHeader.biHeight+1][1];
    tempData[infoHeader.biHeight+1][rowSize+1] = tempData[infoHeader.biHeight+1][rowSize];

    // 卷积操作
    for (int i = 0; i < infoHeader.biHeight; i++) {
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

    char savePath[]="../lab7/ProcessedPic/prowitt.bmp";
    FILE *f=fopen(savePath,"wb");
    if(f==NULL){
    perror("can not open file!");
    return -2;
    }
    fwrite(&fileHeader,sizeof(fileHeader),1,f);
    fwrite(&infoHeader,sizeof(infoHeader),1,f);
    fwrite(rgbquad,1024,1,f);
    fwrite(newImageData,sizeof(unsigned char)*infoHeader.biSizeImage,1,f);
    fclose(f);
    free(imageData);
    fclose(file);
    free(newImageData);


}
