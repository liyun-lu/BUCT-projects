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
int size=3;///�˵Ĵ�С��sigma�̶�ʱ����Խ��ͼ��Խģ������ԽСͼ��仯ԽС��
int sigma = 2;///sigmaȡֵԽ��ͼ��Խƽ����sigmaȡֵԽС��ͼ��Խ����

///��һ����(�ֳ�Ϊ����ˡ���ģ������)ɨ��ͼ����ÿһ�����ص㣬�������ڸ�������ֵ���Ӧλ�õ�Ȩֵ��Ʋ����.
///����ѧ�ĽǶ���������˹�˲��Ĺ�����ͼ�����˹��̬�ֲ����������
void Gaussian(int, void *)
{
    image = src.clone();///ÿ�ε��ö�����һ�������ͼ��

    int window=2*size;///�˲����ڴ�С
    double *temp = new double[window];

    ///����߽�
    Mat INPUT;
    copyMakeBorder(image, INPUT, window / 2, window / 2, window / 2, window / 2, BORDER_REFLECT_101);

    double sum = 0;
    for(int i = 0; i < window; i++)///һά�˲�������t(x)=e(-x*x)/(2*sigme*sigma)
    {
        int mid = i - window / 2;///(-window/2) < x < (window/2)
        temp[i] = exp(-(mid * mid) / (2 * sigma * sigma));///t(x)=e(-x*x)/(2*sigme*sigma)
        sum += temp[i];
    }

    ///��һ���˲��ˣ���Ȩֵ�ķ�ΧԼ����[0,1]֮�䣬�������е�ֵ���ܺ�Ϊ1
    for(int i = 0; i < window; i++)
    {
        temp[i] = temp[i] / sum;
    }

    int rows, cols;
    cols = image.cols;
    rows = image.rows;

    ///�ȶ�ÿ�н���һά��˹�˲�
    for(int row = window / 2; row < rows + window / 2; row++) ///��
    {
        for(int col = window / 2; col < cols + window / 2; col++)  ///��
        {
            int t = 0;
            double s=0;
            double sum[3] = { 0 };///�������ͨ��������
            for(int k = col - window / 2; k < col + window / 2; k++)
            {
                for(int c = 0; c < INPUT.channels(); c++)
                {
                    sum[c] += (INPUT.at<Vec3b>(row, k)[c]) * temp[t]; ///�в��䣬������仯������ˮƽ����ľ��
                }
                t++;
            }
            for(int c = 0; c < INPUT.channels(); c++)
            {
                INPUT.at<Vec3b>(row, col)[c] = sum[c];
            }
        }
    }

    ///�ٶ�ÿ�н���һά��˹�˲�
    for(int col = window / 2; col < cols + window / 2; col++)  ///��
    {
        for(int row = window / 2; row < rows + window / 2; row++)  ///��
        {
            int t = 0;
            double sum[3] = { 0 };
            for(int k = row - window / 2; k < row + window / 2; k++)
            {
                for(int c = 0; c < INPUT.channels(); c++)
                {
                    sum[c] += (INPUT.at<Vec3b>(k, col)[c]) * temp[t];///������
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
    src = image.clone();//����һ��ͼƬ
    imshow("src", src);

    namedWindow("image");
    createTrackbar("�˴�С", "image", &size, 10, Gaussian);
    createTrackbar("sigma", "image", &sigma, 10, Gaussian);
    Gaussian(0, 0);

    waitKey();
    image.release();
    src.release();

    return 0;
}
