///ͼ�񱥺Ͷ�
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat image;
Mat src;
int increment_value = 100;
int max_increment = 200;

///����RGBͼ����νɫ��/���Ͷȵ��������ǰ� RGB תΪ HSL�� �ٶ�ɫ��(H),  ���Ͷ�(S), ����(L)���е�����Ȼ����ת��RGB
///�㷨��1������ÿ�����ص�����ɫ��Сֵ�����ֵ
///      2��delta=��ֵ֮�� / 255�������ֵ֮��Ϊ0������������value=��ֵ֮�� / 255
///		3��RGBͼ��ռ�ת����HSL��Hɫ����S���Ͷȣ�L���ȣ�
///		L = sum / 2,���L < 0.5 ,�� S = sub / sum;����   S = sub / (2 - sum);
///		4��Increment / 100 Ϊ���Ͷ�,�����µ�rgbֵ

void Saturation(int, void *) {
    ///�ȼ��㱥�Ͷȵ���������
	float increment = (increment_value - 100)* 1.0 / max_increment;///increment (-100.0, 100.0)

	image = src.clone();

	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
		    ///����ÿ�����ص�����ɫ��Сֵ�����ֵ
			float b = image.at<Vec3b>(row, col).val[0];
			float g = image.at<Vec3b>(row, col).val[1];
			float r = image.at<Vec3b>(row, col).val[2];
			float max_val,min_val;
			max_val = std::max(r,g);
			max_val = std::max(max_val,b);
			min_val = std::min(r,g);
			min_val = std::min(min_val,b) ;

			///RGBתHSL����H��S��L��ֵ����
			float sub, sum,alpha;
			float r_new, g_new, b_new;
			float L, S;
			///��������ֵ�Ĳ���Ϊ0��HSL����
			sub = (max_val - min_val) / 255;
			if (sub == 0)
				continue;
			sum = (max_val + min_val) / 255;
			L = sum / 2;
			///L<0.5,S=(max-min)/(max+min); L>0.5,S=(max-min)/2-(max+min)
			if (L < 0.5)
				S = sub / sum;
			else
				S = sub / (2 - sum);

            ///HSLת��RGB,�����µ�rgbֵ
			if (increment >= 0)///���߱��Ͷ�
			{
                alpha = std::max(S,1 - increment);
				alpha = 1 / alpha - 1;

				r_new = r + (r - L * 255) * alpha;
				g_new = g + (g - L * 255) * alpha;
				b_new = b + (b - L * 255) * alpha;
			}
			else///���ͱ��Ͷ�
			{
				alpha = increment;

				r_new = L * 255 + (r - L * 255) * (1 + alpha);
				g_new = L * 255 + (g - L * 255) * (1 + alpha);
				b_new = L * 255 + (b - L * 255) * (1 + alpha);
			}

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
	createTrackbar("���Ͷ�", "image", &increment_value, 200, Saturation);

	Saturation(0, 0);//���Ͷ�


	waitKey();
	image.release();
	src.release();

	return 0;
}
