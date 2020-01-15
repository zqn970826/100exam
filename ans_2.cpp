#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
using namespace cv;

// 图像灰度化
// 灰度是一种图像亮度的表示方法，通过下式计算：
// Y = 0.2126*R + 0.7152*G + 0.0722*B
Mat graypic(Mat img)
{
    // 复制原图像的大小，设置输出图像的通道数8UC1（单通道）
    Mat out = Mat::zeros(img.size(), CV_8UC1);
    for (int i = 0; i < out.rows; i++)  // 遍历行
    {
        for (int j = 0; j < out.cols; j++)  // 遍历列
        {
            out.at<uchar>(i, j) = 0.0722*(long long)img.at<cv::Vec3b>(i, j)[2] + 0.7152*(long long)img.at<cv::Vec3b>(i, j)[0] + 0.2126*(long long)img.at<cv::Vec3b>(i, j)[1];
        }
    }
    return out;
}

int main(int argc, char const *argv[])
{
    Mat src = imread("imori.jpg");
    Mat ans = imread("./ans_img/answer_2.jpg");  // 与结果进行对比
    if (src.empty())  // 判断源图像是否存在
    {
        printf("No exist\n");
        return -1;
    }

    Mat res = graypic(src);
    imshow("res", res);
    imwrite("ans_2.jpg", res);
    imshow("ans", ans);

    waitKey(0);
    return 0;
}