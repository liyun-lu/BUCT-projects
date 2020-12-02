#include<opencv2/opencv.hpp>
#include<cxcore.h>
#include<cmath>
#include<math.h>
#include<cv.h>
#include<highgui.h>
#include<iostream>

using namespace std;
using namespace cv;

Mat src, image;
int size=3;///核的大小。sigma固定时，核越大图像越模糊，核越小图像变化越小。
int sigma = 2;///sigma取值越大，图像越平缓，sigma取值越小，图像越尖锐

///用一个核(又称为卷积核、掩模、矩阵)扫描图像中每一个像素点，将邻域内各个像素值与对应位置的权值相称并求和.
///从数学的角度来看，高斯滤波的过程是图像与高斯正态分布做卷积操作
void Gaussian(int, void *)
{
    image = src.clone();///每次调用都复制一次最初的图像

    int window=2*size;///滤波窗口大小
    double *temp = new double[window];

    ///扩充边界
    Mat INPUT;
    copyMakeBorder(image, INPUT, window / 2, window / 2, window / 2, window / 2, BORDER_REFLECT_101);

    double sum = 0;
    for(int i = 0; i < window; i++)///一维滤波的数组t(x)=e(-x*x)/(2*sigme*sigma)
    {
        int mid = i - window / 2;///(-window/2) < x < (window/2)
        temp[i] = exp(-(mid * mid) / (2 * sigma * sigma));///t(x)=e(-x*x)/(2*sigme*sigma)
        sum += temp[i];
    }

    ///归一化滤波核，将权值的范围约束在[0,1]之间，并且所有的值的总和为1
    for(int i = 0; i < window; i++)
    {
        temp[i] = temp[i] / sum;
    }

    int rows, cols;
    cols = image.cols;
    rows = image.rows;

    ///先对每行进行一维高斯滤波
    for(int row = window / 2; row < rows + window / 2; row++) ///行
    {
        for(int col = window / 2; col < cols + window / 2; col++)  ///列
        {
            int t = 0;
            double s=0;
            double sum[3] = { 0 };///存放三个通道的数组
            for(int k = col - window / 2; k < col + window / 2; k++)
            {
                for(int c = 0; c < INPUT.channels(); c++)
                {
                    sum[c] += (INPUT.at<Vec3b>(row, k)[c]) * temp[t]; ///行不变，列坐标变化，先做水平方向的卷积
                }
                t++;
            }
            for(int c = 0; c < INPUT.channels(); c++)
            {
                INPUT.at<Vec3b>(row, col)[c] = sum[c];
            }
        }
    }

    ///再对每列进行一维高斯滤波
    for(int col = window / 2; col < cols + window / 2; col++)  ///列
    {
        for(int row = window / 2; row < rows + window / 2; row++)  ///行
        {
            int t = 0;
            double sum[3] = { 0 };
            for(int k = row - window / 2; k < row + window / 2; k++)
            {
                for(int c = 0; c < INPUT.channels(); c++)
                {
                    sum[c] += (INPUT.at<Vec3b>(k, col)[c]) * temp[t];///行坐标
                }
                t++;
            }
            for(int c = 0; c < INPUT.channels(); c++)
            {
                INPUT.at<Vec3b>(row, col)[c] = sum[c];
            }
        }
    }

    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            image.at<Vec3b>(row, col) = INPUT.at<Vec3b>(row + window / 2, col + window / 2);
        }
    }

    imshow("image", image);
}


int main()
{
    image = imread("images/1.jpg");
    src = image.clone();//复制一张图片
    imshow("src", src);

    namedWindow("image");
    createTrackbar("核大小", "image", &size, 10, Gaussian);
    createTrackbar("sigma", "image", &sigma, 10, Gaussian);
    Gaussian(0, 0);

    waitKey();
    image.release();
    src.release();

    return 0;
}
