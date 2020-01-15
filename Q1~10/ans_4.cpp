#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
using namespace cv;

// 大津算法，也被称作最大类间方差法，是一种可以自动确定二值化中阈值的算法。
// 注意：请传入灰度图
// opencv中调用函数为: threshold(image,image2,0,255,CV_THRESH_OTSU) 实现，
// 该函数就会使用大律法OTSU得到的全局自适应阈值来进行二值化图片，而参数中的threshold不再起作用
// 参考：朱伟《图像处理》、维基百科
int otsu(Mat img)
{
    int ncols = img.cols;
    int nrows = img.rows;
    int threshold = 0;

    // 初始化统计参数
    int nSumPix[256] = {0}; // 0~255
    float nProDis[256] = {0};

    // 统计灰度级中每个像素在整幅图像中的个数
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            nSumPix[(int)img.at<uchar>(i, j)]++;
        }
    }

    // 计算每个灰度级占图像中的概率分布
    for (int i = 0; i < 256; i++)
    {
        nProDis[i] = (float)nSumPix[i] / (ncols*nrows);
    }

    // 遍历灰度级[0， 255]， 计算出最大类间方差下的阈值
    double w0, w1, u0, u1, delta_temp;
    double delta_max = 0.0;

    for (int i = 0; i < 256; i++)
    {
        w0 = 0;
        w1 = 0;
        u0 = 0;
        u1 = 0;
        delta_temp = 0;
        for (int j = 0; j < 256; j++)
        {
            if (j <= i) // 背景部分
            {
                // 当前i为分割阈值， 第一类总的概率
                w0 += nProDis[j];
                u0 += j * nProDis[j];
            }
            else // 前景部分
            {
                // 当前i为分割阈值， 第一类总的概率
                w1 += nProDis[j];
                u1 += j * nProDis[j];
            }
        }
        // 分别计算平均灰度
        u0 /= w0;
        u1 /= w1;
        double u = u0 + u1;
        delta_temp  = (double)(w0*w1*pow((u0-u1), 2));
        // 依次好的最大类间方差下的阈值
        if (delta_temp > delta_max)
        {
            delta_max = delta_temp;
            threshold = i;
        }
    }
    return threshold;
}

int main()
{
    // 读取图像源
    Mat src = imread("imori.jpg");
    Mat ans = imread("./ans_img/answer_4.jpg");
    Mat srcGray;
    Mat otsu_res = Mat::zeros(src.size(), CV_8UC1);
    if (src.empty())
    {
        printf("No exist\n");
        return -1;
    }
    cvtColor(src, srcGray, CV_RGB2GRAY); // 转为为灰度图
    int otsuthreshold = otsu(srcGray);
    printf("%d\n", otsuthreshold);
    for (int i = 0; i < otsu_res.rows; i++)
    {
        for (int j = 0; j < otsu_res.cols; j++)
        {
            if (srcGray.at<uchar>(i, j) > otsuthreshold)
            {
                otsu_res.at<uchar>(i, j) = 255;
            }
            else
            {
                otsu_res.at<uchar>(i, j) = 0;
            }
        }
    }
    imshow("res", otsu_res);
    imwrite("ans_4.jpg", otsu_res);
    imshow("ans", ans);

    waitKey(0);
    return 0;
}