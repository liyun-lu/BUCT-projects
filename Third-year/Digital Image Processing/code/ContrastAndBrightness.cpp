//ͼ�����ȺͶԱȶ�
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Mat image;
Mat src;
int contrast = 100;
int brightness = 0;

///�ı�ͼ������ȺͶԱȶ� g(i, j) = af(i, j) + b
void ContrastAndBrightness(int, void*)
{
	image = src.clone();//ÿ�ε��ö�����һ�������ͼ��
	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			float b = image.at<Vec3b>(row, col).val[0];
			float g = image.at<Vec3b>(row, col).val[1];
			float r = image.at<Vec3b>(row, col).val[2];

			float alpha;//����ʹͼ�����سɱ����������򽵵ͣ���<1�����ı�����ͼ��ĶԱȶ�
			float beta;//�¿�Ϊ����Ҳ��Ϊ��,��ʵ�������ɫ�����ɫ����(0Ϊ�ڣ�255Ϊ��)�����Ըı����ͼ�������
			alpha = contrast / 100.0;
			beta = brightness / 1.0;

			float b_new,g_new,r_new;
			// �κ�һ�����ض���(0, 255)֮��,saturate_cast ����ȷ������ֵ��0��255֮�䡣
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
	createTrackbar("�Աȶ�", "image", &contrast, 100, ContrastAndBrightness);
	createTrackbar("����", "image", &brightness, 255, ContrastAndBrightness);

	ContrastAndBrightness(0, 0);


	waitKey();
	image.release();
	src.release();

	return 0;
}
