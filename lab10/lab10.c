#include "lab10.h"
#include "../tools/ImagefileHelper.h"
#include<stdio.h>
#include <malloc.h>

void extraction(char *srcPath, char *dstPath){
    if (srcPath == NULL)
    {
        srcPath = "../img/10.bmp";
    }
    if(dstPath == NULL)
    {
        dstPath = "../lab10/img/extraction.bmp";
    }

    BMP8bit bmp = read8Image(srcPath);
    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;
    int colSize = bmp.infoHeader.biHeight;
    int* label = (int*)malloc(rowSize * colSize * sizeof(int));

    for(int i = 0; i < colSize; i++)
    {
        for(int j = 0; j < rowSize; j++)
        {
            // 初始化label
            label[i * rowSize + j] = 0;

            // 如果是白色像素,跳过
            if(bmp.imageData[i * rowSize + j]==255) continue;

            int flag = 0;

            // 左侧
            if(j > 0 && bmp.imageData[i * rowSize + j - 1] == 0)flag++;
            // 右侧
            if(j < rowSize - 1 && bmp.imageData[i * rowSize + j + 1] == 0)flag++;
            // 上侧
            if(i > 0 && bmp.imageData[(i - 1) * rowSize + j] == 0)flag++;
            // 下侧
            if(i < colSize - 1 && bmp.imageData[(i + 1) * rowSize + j] == 0)flag++;
            // 左上
            if(i > 0 && j > 0 && bmp.imageData[(i - 1) * rowSize + j - 1] == 0)flag++;
            // 右上
            if(i > 0 && j < rowSize - 1 && bmp.imageData[(i - 1) * rowSize + j + 1] == 0)flag++;
            // 左下
            if(i < colSize - 1 && j > 0 && bmp.imageData[(i + 1) * rowSize + j - 1] == 0)flag++;
            // 右下
            if(i < colSize - 1 && j < rowSize - 1 && bmp.imageData[(i + 1) * rowSize + j + 1] == 0)flag++;

            if(flag == 8)
            {
                // 如果周围8个像素都是黑色，则该像素为内部像素,标记为1
                label[i * rowSize + j] = 1;
            }
            else
            {
                // 否则为边缘像素，标记为2
                label[i * rowSize + j] = 2;
            }
        }
    }

    for(int i = 0; i < colSize; i++)
    {
        for(int j = 0; j < rowSize; j++)
        {
            if(label[i * rowSize + j] == 2)
            {
                // 如果是边缘像素，将其置为黑色
                bmp.imageData[i * rowSize + j] = 0;
            }
            else if(label[i * rowSize + j] == 1)
            {
                // 如果是内部像素，将其置为白色
                bmp.imageData[i * rowSize + j] = 255;
            }
        }
    }

    save8Image(dstPath, bmp);

}