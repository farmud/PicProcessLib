#include "../tools/ImagefileHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab6.h"

# define LIM 225
void regional_growth(char *srcPath, char *dstPath)
{
    if (srcPath == NULL)
    {
        srcPath = "../img/61.bmp";
    }
    if (dstPath == NULL)
    {
        dstPath = "../lab6/img/growth.bmp";
    }

    BMP8bit bmp = read8Image(srcPath);
    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;
    int colSize = bmp.infoHeader.biHeight;

    int *queue = (int *)malloc(rowSize * colSize * sizeof(int)); // 队列,下标为像素点的索引
    int *region = (int *)malloc(rowSize * colSize * sizeof(int)); // 区域,下标为像素点的索引,默认区域为0
    int *visited = (int *)malloc(rowSize * colSize * sizeof(int)); // 访问标记,下标为像素点的索引,0为未访问,1为已访问

    for (int i = 0; i < rowSize * colSize; i++)
    {
        region[i] = 0;
        visited[i] = 0;
        queue[i] = 0;
    }

    const int T = 7; // 阈值

    int seed1x = 100, seed1y = 100; // 种子点
    int indexX = seed1y * rowSize + seed1x;
    int regionIndex = 1; // 区域索引

    int queueHead = 0;
    int queueTail = 0;

    // 初始化
    queue[queueTail++] = indexX;

    region[indexX] = regionIndex;


    // 迭代
    while (queueTail != queueHead)
    {
        int p = queue[queueHead++]; // 出队, p为像素点的索引
        if (visited[p] == 1)
        {
            continue;
        }
        visited[p] = 1;
        int x = p % rowSize;
        int y = p / rowSize;

        if (x > 0 && visited[p - 1] == 0)
        {
            if (fabs(bmp.imageData[p] - bmp.imageData[p - 1]) < T)
            {
                region[p - 1] = region[p];
                queue[queueTail++] = p - 1; // 入队
            }
        }
        if (x < rowSize - 1 && visited[p + 1] == 0)
        {
            if (fabs(bmp.imageData[p] - bmp.imageData[p + 1]) < T)
            {
                region[p + 1] = region[p];
                queue[queueTail++] = p + 1; // 入队
            }
        }
        if (y > 0 && visited[p - rowSize] == 0)
        {
            if (fabs(bmp.imageData[p] - bmp.imageData[p - rowSize]) < T)
            {
                region[p - rowSize] = region[p];
                queue[queueTail++] = p - rowSize; // 入队
            }
        }
        if (y < colSize - 1 && visited[p + rowSize] == 0)
        {
            if (fabs(bmp.imageData[p] - bmp.imageData[p + rowSize]) < T)
            {
                region[p + rowSize] = region[p];
                queue[queueTail++] = p + rowSize; // 入队
            }
        }
    }



    // 合并区域模块
    // 因为只有一个种子点，所以只有两个区域
    int sum1 = 0, sum2 = 0;
    int count1 = 0, count2 = 0;

    for (int i = 0; i < rowSize * colSize; i++)
    {
        // 统计每个区域的均值
        if (region[i] == 1)
        {
            sum1 += bmp.imageData[i];
            count1++;
        }
        else
        {
            sum2 += bmp.imageData[i];
            count2++;
        }
    }
    int avg1 = sum1 / count1;
    int avg2 = sum2 / count2;
    if(abs(avg1 - avg2) < 10){
        // 区域相似，合并
        for (int i = 0; i < rowSize * colSize; i++)
        {
            if (region[i] == 2)
            {
                region[i] = 1;
            }
        }
    }



    // 将区域填充到图像中
    for (int i = 0; i < rowSize * colSize; i++)
    {
        if (region[i] == 1)
        {
            bmp.imageData[i] = 255;
        }
        else
        {
            bmp.imageData[i] = 0;
        }
    }

    // 标记种子点
    bmp.imageData[seed1y * rowSize + seed1x] = 128;


    // 保存图片
    save8Image(dstPath, bmp);


}


int row = 0;


void devide(int ** imageData,unsigned char * initialData ,int lefttopX ,int lefttopY,int rightbottomX,int rightbottomY);
void regionalFragmentation(char * srcPath, char* dstPath){
    if (srcPath == NULL)
    {
        srcPath = "../img/62.bmp";
    }
    if (dstPath == NULL)
    {
        dstPath = "../lab6/img/fragmentation.bmp";
    }
    BMP8bit bmp = read8Image(srcPath);
    int rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;
    row = rowSize;
    int colSize = bmp.infoHeader.biHeight;

    // 动态生成二维数组,并将图像数据拷贝到二维数组中
    int **imageData = (int **)malloc(sizeof(int *) * colSize);
    for(int i = 0;i < colSize;i++){
        imageData[i] = (int *)malloc(sizeof(int) * rowSize);
        for(int j = 0;j < rowSize;j++){
            imageData[i][j] = bmp.imageData[i*rowSize + j];
        }
    }

    int lefttopX = 0,lefttopY = 0,rightbottomX = rowSize,rightbottomY = colSize;
    devide(imageData, bmp.imageData,lefttopX,lefttopY,rightbottomX,rightbottomY);

    // 保存图片
    save8Image(dstPath, bmp);
}
void devide(int **imageData,unsigned char *initialData, int lefttopX ,int lefttopY,int rightbottomX,int rightbottomY){

    int min = 0,max = 0;
    // 计算区域内最大最小值
    for(int i = lefttopY;i < rightbottomY;i++){
        for(int j = lefttopX;j < rightbottomX;j++){
            if(imageData[i][j] < min){
                min = imageData[i][j];
            }
            if(imageData[i][j] > max){
                max = imageData[i][j];
            }
        }
    }
    // 如果区域太小不可分
    int limit = 5;
    if(fabs(rightbottomX - lefttopX) < limit || fabs(rightbottomY - lefttopY) < limit){
        return;
    }

    // 如果区域内最大最小值相差小于LIM，则不再分割
    if(max - min < LIM){
        return;
    }

    // 绘图，画出区域内四等分的线
    int midX = (lefttopX + rightbottomX) / 2;
    int midY = (lefttopY + rightbottomY) / 2;

    for(int i = lefttopX;i < rightbottomX;i++){
        initialData[lefttopY * row + i] = 0;
        initialData[rightbottomY * row + i] = 0;
    }
    for(int i = lefttopY;i < rightbottomY;i++){
        initialData[i * row + lefttopX] = 0;
        initialData[i * row + rightbottomX] = 0;
    }


    // 递归分割
    devide(imageData,initialData,lefttopX,lefttopY,midX,midY);
    devide(imageData,initialData,midX,lefttopY,rightbottomX,midY);
    devide(imageData,initialData,lefttopX,midY,midX,rightbottomY);
    devide(imageData,initialData,midX,midY,rightbottomX,rightbottomY);

}

