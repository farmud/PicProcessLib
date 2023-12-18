#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"lab1/lab1.h"
#include"lab2/lab2.h"
#include "lab3/lab3.h"
#include "lab4/lab4.h"
#include "lab5/lab5.h"
#include "lab6/lab6.h"
#include "lab7/lab7.h"
#include "lab8/lab8.h"
#include "lab9/lab9.h"
#include "lab10/lab10.h"
void menu();

int main() {

   menu();

}

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
    printf("==============11. 自动运行所有函数===============\n");
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
                    printf("1.1success!\n");
                    break;
                }
                case 2: {
                    reverseProcess(NULL,NULL);
                    printf("1.2success!\n");
                    break;
                }
                case 3: {
                    depatureRGB(NULL,NULL,NULL,NULL);
                    printf("1.3success!\n");
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
                    printf("2.1success!\n");
                    break;
                }
                case 2: {
                    histogramEqualization(NULL,NULL);
                    makeHistogram("../lab2/img/Equalization.bmp","../lab2/img/EqualizationHistogram.bmp");
                    printf("2.2success!\n");
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
                    printf("3.1success!\n");
                    break;
                }
                case 2: {
                    mid(NULL,NULL);
                    printf("3.2success!\n");
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
                    printf("4.1success!\n");
                    break;
                }
                case 2: {
                    translate(NULL,NULL);
                    printf("4.2success!\n");
                    break;
                }
                case 3: {
                    mirror(NULL,NULL,NULL);
                    printf("4.3success!\n");
                    break;
                }
                case 4: {
                    revolve(NULL,NULL);
                    printf("4.4success!\n");
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
                    makeHistogramAndNewImage(NULL,NULL,NULL,125 );
                    printf("5.1success!\n");
                    break;
                }
                case 2: {
                    iterate(NULL,NULL,NULL);
                    printf("5.2success!\n");
                    break;
                }
                case 3: {
                    Otsu(NULL,NULL,NULL);
                    printf("5.3success!\n");
                    break;
                }
                default: {
                    printf("输入错误，请重新输入！\n");
                    break;
                }
            }
        }
            break;
        case 6: {
            system("cls");
            printf("1. 基于种子点进行区域增长\n");
            printf("2. 区域分裂\n");
            printf("请输入您的选择，输入0返回：\n");
            int i ;
            scanf("%d",&i);
            switch (i) {
                case 1: {
                    regional_growth(NULL,NULL);
                    printf("6.1success!\n");
                    break;
                }
                case 2: {
                    regionalFragmentation(NULL,NULL);
                    printf("6.2success!\n");
                    break;
                }

                default: {
                    printf("输入错误，请重新输入！\n");
                    break;
                }
            }
        }

            break;
        case 7:{
            system("cls");
            printf("1. Prewitt\n");
            printf("2. Sobel\n");
            printf("3. LOG\n");
            printf("请输入您的选择，输入0返回：\n");
            int i ;
            scanf("%d",&i);
            switch (i) {
                case 1: {
                    prewitt(NULL,NULL);
                    printf("7.1success!\n");
                    break;
                }
                case 2: {
                    sobel(NULL,NULL);
                    printf("7.2success!\n");
                    break;
                }
                case 3: {
                    LOG(NULL,NULL);
                    printf("7.3success!\n");
                    break;
                }
                default: {
                    printf("输入错误，请重新输入！\n");
                    break;
                }
            }
        }
            break;
        case 8:{
            system("cls");
            printf("1. 直线检测\n");
            printf("请输入您的选择，输入0返回：\n");
            int i ;
            scanf("%d",&i);
            switch (i) {
                case 1: {
                    houghTransform(NULL,NULL);
                    printf("8.1success!\n");
                    break;
                }
                default: {
                    printf("输入错误，请重新输入！\n");
                    break;
                }
            }
        }
            break;
        case 9:{
            system("cls");
            printf("1. 区域标记\n");
            printf("请输入您的选择，输入0返回：\n");
            int i ;
            scanf("%d",&i);
            switch (i) {
                case 1: {
                    regionalMark(NULL,NULL);
                    printf("9.1success!\n");
                    break;
                }
                default: {
                    printf("输入错误，请重新输入！\n");
                    break;
                }
            }
        }
            break;
        case 10:{
            system("cls");
            printf("1. 轮廓提取\n");
            printf("请输入您的选择，输入0返回：\n");
            int i ;
            scanf("%d",&i);
            switch (i) {
                case 1: {
                    extraction(NULL,NULL);
                    printf("10.1success!\n");
                    break;
                }
                default: {
                    printf("输入错误，请重新输入！\n");
                    break;
                }
            }
        }
        break;
        case 11:{
            system("cls");
            printf("下面以默认参数运行所有图像处理函数：\n");
            grayProcess(NULL,NULL);
            printf("1.1success!\n");
            reverseProcess(NULL,NULL);
            printf("1.2success!\n");
            depatureRGB(NULL,NULL,NULL,NULL);
            printf("1.3success!\n");
            makeHistogram(NULL,NULL);
            printf("2.1success!\n");
            histogramEqualization(NULL,NULL);
            printf("2.2success!\n");
            avag(NULL,NULL);
            printf("3.1success!\n");
            mid(NULL,NULL);
            printf("3.2success!\n");
            shrink(NULL,NULL);
            printf("4.1success!\n");
            translate(NULL,NULL);
            printf("4.2success!\n");
            mirror(NULL,NULL,NULL);
            printf("4.3success!\n");
            revolve(NULL,NULL);
            printf("4.4success!\n");
            makeHistogramAndNewImage(NULL,NULL,NULL,100 );
            printf("5.1success!\n");
            iterate(NULL,NULL,NULL);
            printf("5.2success!\n");
            Otsu(NULL,NULL,NULL);
            printf("5.3success!\n");
            regional_growth(NULL,NULL);
            printf("6.1success!\n");
            regionalFragmentation(NULL,NULL);
            printf("6.2success!\n");
            prewitt(NULL,NULL);
            printf("7.1success!\n");
            sobel(NULL,NULL);
            printf("7.2success!\n");
            LOG(NULL,NULL);
            printf("7.3success!\n");
            houghTransform(NULL,NULL);
            printf("8.1success!\n");
            regionalMark(NULL,NULL);
            printf("9.1success!\n");
            extraction(NULL,NULL);
            printf("10.1success!\n");
            printf("批处理完成!\n");


        }
            break;
        default:
            printf("输入错误，请重新输入！\n");
    }


    printf("按任意键继续：\n");
    getch();
    system("cls");
    menu();
}

