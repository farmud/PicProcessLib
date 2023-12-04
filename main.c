#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"lab1/lab1.h"
#include"lab2/lab2.h"
#include "lab3/lab3.h"
#include "lab4/lab4.h"
#include "lab5/lab5.h"
#include "lab7/lab7.h"

void menu() {

    printf("=================================================\n");
    printf("=================================================\n");
    printf("==============1. BMP文件处理=====================\n");
    printf("==============2. 直方图处理======================\n");
    printf("==============3. 空间域滤波======================\n");
    printf("==============4. 图像变换========================\n");
    printf("==============5. 阈值分割========================\n");
    printf("==============6. 基于区域的分割==================\n");
    printf("==============7. 边缘检测========================\n");
    printf("==============8. Hough变换=======================\n");
    printf("==============9. 区域标记========================\n");
    printf("==============10. 轮廓提取=======================\n");
    printf("=================================================\n");
    printf("=================================================\n");
    printf("请输入您的选择，输入0终止：\n");
    int num;
    scanf("%d",&num);
    switch (num) {
        case 0: {
            printf("程序结束！\n");
            return ;
        }
        case 1:{
            system("cls");
            printf("1. 将24位彩色图像转换为8位灰度图\n");
            printf("2. 对8位灰度图进行反色\n");
            printf("3. 将24位彩色图像按R,G,B三个分量进行分离，产生3幅新的8位灰度图像\n");
            printf("请输入您的选择，输入0返回：\n");
            int i ;
            scanf("%d",&i);
            switch (i) {
                case 0: {
                    system("cls");
                    break;
                }
                case 1: {
                    grayProcess(NULL,NULL);
                    printf("success!\n");
                    break;
                }
                case 2: {
                    reverseProcess(NULL,NULL);
                    printf("success!\n");
                    break;
                }
                case 3: {
                    depatureRGB(NULL,NULL,NULL,NULL);
                    printf("success!\n");
                    break;
                }
                default: {
                    printf("输入错误，请重新输入！\n");
                    break;
                }
            }
        }
            break;
        case 2: {
            system("cls");
            printf("1. 直方图统计\n");
            printf("2. 直方图均衡化\n");
            printf("请输入您的选择，输入0返回：\n");
            int i ;
            scanf("%d",&i);
            switch (i) {
                case 1: {
                    makeHistogram(NULL,NULL);
                    printf("success!\n");
                    break;
                }
                case 2: {
                    histogramEqualization(NULL,NULL);
                    printf("success!\n");
                    break;
                }
                default: {
                    printf("输入错误，请重新输入！\n");
                    break;
                }
            }
        }
            break;
        case 3: {
            system("cls");
            printf("1. 平均滤波\n");
            printf("2. 中值滤波\n");
            printf("请输入您的选择，输入0返回：\n");
            int i ;
            scanf("%d",&i);
            switch (i) {
                case 1: {
                    avag(NULL,NULL);
                    printf("success!\n");
                    break;
                }
                case 2: {
                    mid(NULL,NULL);
                    printf("success!\n");
                    break;
                }
                default: {
                    printf("输入错误，请重新输入！\n");
                    break;
                }
            }
        }
            break;
        case 4: {
            system("cls");
            printf("1. 图像缩放\n");
            printf("2. 图像平移\n");
            printf("3. 图像镜像\n");
            printf("4. 图像旋转\n");
            printf("请输入您的选择，输入0返回：\n");
            int i ;
            scanf("%d",&i);
            switch (i) {
                case 1: {
                    shrink(NULL,NULL);
                    printf("success!\n");
                    break;
                }
                case 2: {
                    translate(NULL,NULL);
                    printf("success!\n");
                    break;
                }
                case 3: {
                    mirror(NULL,NULL,NULL);
                    printf("success!\n");
                    break;
                }
                case 4: {
                    revolve(NULL,NULL);
                    printf("success!\n");
                    break;
                }
                default: {
                    printf("输入错误，请重新输入！\n");
                    break;
                }
            }
        }
            break;
        case 5: {
            system("cls");
            printf("1. 给定阈值T\n");
            printf("2. 迭代阈值法\n");
            printf("3. Otsu\n");
            printf("请输入您的选择，输入0返回：\n");
            int i ;
            scanf("%d",&i);
            switch (i) {
                case 1: {
                    makeHistogramAndNewImage(NULL,NULL,NULL,100 );
                    printf("success!\n");
                    break;
                }
                case 2: {
                    iterate(NULL,NULL,NULL);
                    printf("success!\n");
                    break;
                }
                case 3: {
                    Otsu(NULL,NULL,NULL);
                    printf("success!\n");
                    break;
                }
                default: {
                    printf("输入错误，请重新输入！\n");
                    break;
                }
            }
        }
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        default:
            printf("输入错误，请重新输入！\n");
    }


    printf("按任意键继续：\n");
    getch();
    system("cls");
    menu();
}


int main() {

   menu();

}
