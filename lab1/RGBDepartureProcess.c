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
    FILE* file = fopen("E:/myLab/PicProcessLib/pic/rgb.bmp", "rb");
    if (!file) {
        printf("Failed to open file\n");
        return 1;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    fread(&fileHeader, sizeof(fileHeader), 1, file);    // 读取文件头
    fread(&infoHeader, sizeof(infoHeader), 1, file);    // 读取信息头

    int rowSize = ((infoHeader.biWidth * infoHeader.biBitCount + 31) / 32) * 4;         // 每行像素所占字节数
    unsigned char* imageData = (unsigned char*)malloc(rowSize * infoHeader.biHeight);   // 图像数据
    fread(imageData, rowSize * infoHeader.biHeight, 1, file);                           // 读取图像数据

    // 编写调色板
    RGBQUAD rgbquad[256];
    for (int i = 0; i < 256; i++) {
        rgbquad[i].rgbBlue = (unsigned char)i;
        rgbquad[i].rgbGreen = (unsigned char)i;
        rgbquad[i].rgbRed = (unsigned char)i;
        rgbquad[i].rgbReserved = (unsigned char)0;
    }

    // 更改文件头信息
    infoHeader.biBitCount = 8;                                                          // 位数改为8
    int newRowSize = ((infoHeader.biWidth * infoHeader.biBitCount + 31) / 32) * 4;      // 每行像素所占字节数

    fileHeader.bfOffBits = sizeof(fileHeader) + sizeof(infoHeader) + sizeof(rgbquad);  // 偏移量
    fileHeader.bfsize = fileHeader.bfOffBits + newRowSize * infoHeader.biHeight;        // 文件大小
                              
    // 更改信息头信息
    infoHeader.biSizeImage = newRowSize * infoHeader.biHeight;                          // 图像数据大小

    unsigned char * BImageData = (unsigned char*)malloc(infoHeader.biSizeImage);    // B通道
    unsigned char * GImageData = (unsigned char*)malloc(infoHeader.biSizeImage);    // G通道
    unsigned char * RImageData = (unsigned char*)malloc(infoHeader.biSizeImage);    // R通道

    // 分离RGB通道
    for(int i = 0;i<infoHeader.biHeight;i++){
        for(int j = 0;j<infoHeader.biWidth;j++){
            int index = i * rowSize + j * 3;
            BImageData[i * newRowSize + j] = imageData[index];
            GImageData[i * newRowSize + j] = imageData[index + 1];
            RImageData[i * newRowSize + j] = imageData[index + 2];
        }
    }



    // 保存B通道文件
    char savePath1[]="E:/myLab/PicProcessLib/lab1/ProcessedPic/departure/B.bmp";
    FILE *f1=fopen(savePath1,"wb");
    if(f1==NULL){
    perror("can not open file!");
    return -2;
    }
    fwrite(&fileHeader,sizeof(fileHeader),1,f1);
    fwrite(&infoHeader,sizeof(infoHeader),1,f1);
    fwrite(rgbquad,1024,1,f1);
    fwrite(BImageData,sizeof(unsigned char)*infoHeader.biSizeImage,1,f1);

    // 保存G通道文件
    char savePath2[]="E:/myLab/PicProcessLib/lab1/ProcessedPic/departure/G.bmp";
    FILE *f2=fopen(savePath2,"wb");
    if(f2==NULL){
    perror("can not open file!");
    return -2;
    }
    fwrite(&fileHeader,sizeof(fileHeader),1,f2);
    fwrite(&infoHeader,sizeof(infoHeader),1,f2);
    fwrite(rgbquad,1024,1,f2);
    fwrite(GImageData,sizeof(unsigned char)*infoHeader.biSizeImage,1,f2);

    // 保存R通道文件
    char savePath3[]="E:/myLab/PicProcessLib/lab1/ProcessedPic/departure/R.bmp";
    FILE *f3=fopen(savePath3,"wb");
    if(f3==NULL){
    perror("can not open file!");
    return -2;
    }

    
    fwrite(&fileHeader,sizeof(fileHeader),1,f3);
    fwrite(&infoHeader,sizeof(infoHeader),1,f3);
    fwrite(rgbquad,1024,1,f3);
    fwrite(RImageData,sizeof(unsigned char)*infoHeader.biSizeImage,1,f3);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    free(imageData);
    fclose(file);
    free(BImageData);
    free(GImageData);
    free(RImageData);
    return 0;
}