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
    printf("==============1. BMP�ļ�����=====================\n");
    printf("==============2. ֱ��ͼ����======================\n");
    printf("==============3. �ռ����˲�======================\n");
    printf("==============4. ͼ��任========================\n");
    printf("==============5. ��ֵ�ָ�========================\n");
    printf("==============6. ��������ķָ�==================\n");
    printf("==============7. ��Ե���========================\n");
    printf("==============8. Hough�任=======================\n");
    printf("==============9. ������========================\n");
    printf("==============10. ������ȡ=======================\n");
    printf("=================================================\n");
    printf("=================================================\n");
    printf("����������ѡ������0��ֹ��\n");
    int num;
    scanf("%d",&num);
    switch (num) {
        case 0: {
            printf("���������\n");
            return ;
        }
        case 1:{
            system("cls");
            printf("1. ��24λ��ɫͼ��ת��Ϊ8λ�Ҷ�ͼ\n");
            printf("2. ��8λ�Ҷ�ͼ���з�ɫ\n");
            printf("3. ��24λ��ɫͼ��R,G,B�����������з��룬����3���µ�8λ�Ҷ�ͼ��\n");
            printf("����������ѡ������0���أ�\n");
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
                    printf("����������������룡\n");
                    break;
                }
            }
        }
            break;
        case 2: {
            system("cls");
            printf("1. ֱ��ͼͳ��\n");
            printf("2. ֱ��ͼ���⻯\n");
            printf("����������ѡ������0���أ�\n");
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
                    printf("����������������룡\n");
                    break;
                }
            }
        }
            break;
        case 3: {
            system("cls");
            printf("1. ƽ���˲�\n");
            printf("2. ��ֵ�˲�\n");
            printf("����������ѡ������0���أ�\n");
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
                    printf("����������������룡\n");
                    break;
                }
            }
        }
            break;
        case 4: {
            system("cls");
            printf("1. ͼ������\n");
            printf("2. ͼ��ƽ��\n");
            printf("3. ͼ����\n");
            printf("4. ͼ����ת\n");
            printf("����������ѡ������0���أ�\n");
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
                    printf("����������������룡\n");
                    break;
                }
            }
        }
            break;
        case 5: {
            system("cls");
            printf("1. ������ֵT\n");
            printf("2. ������ֵ��\n");
            printf("3. Otsu\n");
            printf("����������ѡ������0���أ�\n");
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
                    printf("����������������룡\n");
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
            printf("����������������룡\n");
    }


    printf("�������������\n");
    getch();
    system("cls");
    menu();
}


int main() {

   menu();

}
