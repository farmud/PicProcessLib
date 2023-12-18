#include "../tools/ImagefileHelper.h"
#include <stdio.h>
#include <stdlib.h>

int rowSize;
int colSize;

void iterativeLabel(BMP8bit *bmp, int x, int y, int label, int *visited);

void regionalMark(char *srcPath, char *dstPath)
{
    if (srcPath == NULL)
    {
        srcPath = "../img/9.bmp";
    }
    if (dstPath == NULL)
    {
        dstPath = "../lab9/img/mark.bmp";
    }
    BMP8bit bmp = read8Image(srcPath);
    rowSize = ((bmp.infoHeader.biWidth * bmp.infoHeader.biBitCount + 31) / 32) * 4;
    colSize = bmp.infoHeader.biHeight;

    // visited数组用于标记像素是否被访问过
    int* visited = (int*)malloc(rowSize * colSize * sizeof(int));
    for(int i = 0; i < rowSize * colSize; i++) {
        visited[i] = 0;
    }
    int label = 1; // 标记的值


    for (int i = 0; i < colSize; i++)
    {
        for (int j = 0; j < rowSize; j++)
        {
            // 如果是黑色像素且未被访问过
            if (bmp.imageData[i * rowSize + j] == 0 && visited[i * rowSize + j] == 0)
            {
                // 使用迭代版本进行标记，深度优先搜索
                iterativeLabel(&bmp, j, i, label, visited);
                label++;
            }
        }
    }

    save8Image(dstPath, bmp);
}

void iterativeLabel(BMP8bit *bmp, int x, int y, int label, int *visited)
{
    int queueSize = rowSize * colSize;
    // 队列
    int *queue = (int *)malloc(queueSize * sizeof(int));
    int front = 0, rear = 0;

    queue[rear++] = y * rowSize + x;

    while (front != rear)
    {
        // 队首出队
        int p = queue[front++];
        int px = p % rowSize;
        int py = p / rowSize;

        if (px >= 0 && px < rowSize && py >= 0 && py < colSize && visited[p] == 0 && bmp->imageData[p] == 0)
        {
            bmp->imageData[p] = (unsigned char)(label*70);
            visited[p] = 1;

            // 将相邻未访问的像素入队
            queue[rear++] = py * rowSize + px - 1; // 左
            queue[rear++] = py * rowSize + px + 1; // 右
            queue[rear++] = (py - 1) * rowSize + px; // 上
            queue[rear++] = (py + 1) * rowSize + px; // 下
        }
    }

}

