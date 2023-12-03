
#include "tool/tool.h"


int main() {
    char* sourceFile = "../pic/lena.bmp";
    char* histogramFile  = "../lab5/ProcessedPic/T_hitogram.bmp";
    char* imageFile = "../lab5/ProcessedPic/T_newImage.bmp";

    int T = 100;
    makeHistogramAndNewImage(sourceFile,histogramFile,imageFile,T);
}
