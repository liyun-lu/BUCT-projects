//图像亮度和对比度
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Mat image;
Mat src;
int contrast = 100;
int brightness = 0;

///改变图像的亮度和对比度 g(i, j) = af(i, j) + b
void ContrastAndBrightness(int, void*)
{
	image = src.clone();//每次调用都复制一次最初的图像
	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			float b = image.at<Vec3b>(row, col).val[0];
			float g = image.at<Vec3b>(row, col).val[1];
			float r = image.at<Vec3b>(row, col).val[2];

			float alpha;//α能使图像像素成倍数的增长或降低（α<1），改变了是图像的对比度
			float beta;//β可为负，也可为正,其实就是向白色或向黑色靠近(0为黑，255为白)，所以改变的是图像的亮度
			alpha = contrast / 100.0;
			beta = brightness / 1.0;

			float b_new,g_new,r_new;
			// 任何一个像素都在(0, 255)之间,saturate_cast 函数确保像素值在0到255之间。
			b_new = saturate_cast<uchar>(b*alpha + beta);
			g_new = saturate_cast<uchar>(g*alpha + beta);
			r_new = saturate_cast<uchar>(r*alpha + beta);
			image.at<Vec3b>(row, col).val[0] = b_new;
			image.at<Vec3b>(row, col).val[1] = g_new;
			image.at<Vec3b>(row, col).val[2] = r_new;
		}
	}
	imshow("image", image);
}

int main()
{
	image = imread("images/1.jpg");
	src = image.clone();


	namedWindow("image");
	createTrackbar("对比度", "image", &contrast, 100, ContrastAndBrightness);
	createTrackbar("亮度", "image", &brightness, 255, ContrastAndBrightness);

	ContrastAndBrightness(0, 0);


	waitKey();
	image.release();
	src.release();

	return 0;
}
