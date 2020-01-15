#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
using namespace cv;

// 读取图像，然后将通道RGB替换成通道BGR。
// 注意: cv2.imread()的系数是按顺序BGR排列的！
Mat channel_swap(Mat img)
{
	// 创建与源图像一样的图像（高、宽、通道）
    Mat out = img.clone();
    for (int i = 0; i < out.rows; i++)  // 遍历行
    {
        for (int j = 0; j < out.cols; j++)  // 遍历列
        {
            // b g r = 0 1 2
            out.at<cv::Vec3b>(i, j)[0] = img.at<cv::Vec3b>(i, j)[2];
            out.at<cv::Vec3b>(i, j)[2] = img.at<cv::Vec3b>(i, j)[0];
            out.at<cv::Vec3b>(i, j)[1] = img.at<cv::Vec3b>(i, j)[1];
        }
    }
    return out;
}

int main(int argc, char const *argv[])
{
	Mat src = imread("imori.jpg");
    Mat ans = imread("./ans_img/answer_1.jpg");  // 与结果进行对比
    if (src.empty())  // 判断源图像是否存在
    {
        printf("No exist\n");
        return -1;
    }

	Mat res = channel_swap(src);
	imshow("res", res);
	imwrite("ans_1.jpg", res);
	imshow("ans", ans);

	waitKey(0);
	return 0;
}