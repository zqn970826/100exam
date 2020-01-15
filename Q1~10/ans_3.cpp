#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
using namespace cv;

Mat thresholding(Mat img)
{
    Mat srcGray;
    Mat dstimg;
    cvtColor(img, srcGray, CV_RGB2GRAY);  // 转化为灰度图
    imshow("gray", srcGray);
    int thresh = 128;  //  阈值
    /*
    0: 二进制阈值 1: 反二进制阈值 2: 截断阈值 3: 0阈值 4: 反0阈值
     */
    int threshType = 0;
    const int maxVal = 255;  // 预设最大值
    threshold(srcGray, dstimg, thresh, maxVal, threshType);
    return dstimg;
}

int main(int argc, char const *argv[])
{
    Mat src = imread("imori.jpg");
    Mat ans = imread("./ans_img/answer_3.jpg");  // 与结果进行对比
    if (src.empty())  // 判断源图像是否存在
    {
        printf("No exist\n");
        return -1;
    }

    Mat res = thresholding(src);
    imshow("res", res);
    imwrite("ans_3.jpg", res);
    imshow("ans", ans);

    waitKey(0);
    return 0;
}