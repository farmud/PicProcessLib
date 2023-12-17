#include "lab8.h"
#include "../tools/ImagefileHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void houghTransform(char *srcPath, char *dstPath)
{
    if (srcPath == NULL)
    {
        srcPath = "../img/8.bmp";
    }
    if (dstPath == NULL)
    {
        dstPath = "../lab8/img/hough.bmp";
    }

    BMP8bit bmp = read8Image(srcPath);
    int threshold = 300;
    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;

    // 霍夫变换参数
    int thetaRes = 180;
    int maxRho = (int)sqrt(bmp.infoHeader.biWidth * bmp.infoHeader.biWidth + bmp.infoHeader.biHeight * bmp.infoHeader.biHeight);

    // 累加器数组
    int *accumulator = (int *)calloc(thetaRes * maxRho, sizeof(int));

    // 执行霍夫变换
    for (int y = 0; y < bmp.infoHeader.biHeight; y++)
    {
        for (int x = 0; x < bmp.infoHeader.biWidth; x++)
        {

            // 如果是白色像素
            if (bmp.imageData[y * rowSize + x] == 255)
            {
                // 对于每一个白色像素，计算其对应的rho和theta
                for (int theta = 0; theta < thetaRes; theta++)
                {
                    double radianTheta = theta * M_PI / 180.0;  // 角度转弧度
                    int rho = (int)(x * cos(radianTheta) + y * sin(radianTheta));
                    // 累加器中对应的位置加一
                    accumulator[theta * maxRho + rho]++;
                }
            }
        }
    }

    // 在累加器中找到峰值并绘制直线
    for (int theta = 0; theta < thetaRes; theta++)
    {
        for (int rho = 0; rho < maxRho; rho++)
        {
            // 如果累加器中的值大于阈值
            if (accumulator[theta * maxRho + rho] > threshold)
            {
                // 将直线画在原图片上
                for (int x = 0; x < bmp.infoHeader.biWidth; x++)
                {
                    // y = (rho - x * cos(theta)) / sin(theta)
                    int y = (int)((rho - x * cos(theta * M_PI / 180.0)) / sin(theta * M_PI / 180.0));
                    if (y >= 0 && y < bmp.infoHeader.biHeight)
                    {
                        bmp.imageData[y * rowSize + x] = 255;
                    }
                }
            }
        }
    }

    // 保存结果图片
    save8Image(dstPath, bmp);

}
