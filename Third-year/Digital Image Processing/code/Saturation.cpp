///图像饱和度
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat image;
Mat src;
int increment_value = 100;
int max_increment = 200;

///对于RGB图像，所谓色相/饱和度调整，就是把 RGB 转为 HSL， 再对色相(H),  饱和度(S), 明度(L)进行调整，然后再转回RGB
///算法：1、计算每个像素点三基色最小值和最大值
///      2、delta=两值之差 / 255，如果两值之差为0，则不做操作；value=两值之和 / 255
///		3、RGB图像空间转化成HSL（H色调，S饱和度，L亮度）
///		L = sum / 2,如果L < 0.5 ,则 S = sub / sum;否则   S = sub / (2 - sum);
///		4、Increment / 100 为饱和度,计算新的rgb值

void Saturation(int, void *) {
    ///先计算饱和度的增长幅度
	float increment = (increment_value - 100)* 1.0 / max_increment;///increment (-100.0, 100.0)

	image = src.clone();

	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
		    ///计算每个像素点三基色最小值和最大值
			float b = image.at<Vec3b>(row, col).val[0];
			float g = image.at<Vec3b>(row, col).val[1];
			float r = image.at<Vec3b>(row, col).val[2];
			float max_val,min_val;
			max_val = std::max(r,g);
			max_val = std::max(max_val,b);
			min_val = std::min(r,g);
			min_val = std::min(min_val,b) ;

			///RGB转HSL，对H、S、L的值调整
			float sub, sum,alpha;
			float r_new, g_new, b_new;
			float L, S;
			///先求两个值的差，如果为0，HSL不变
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

            ///HSL转回RGB,计算新的rgb值
			if (increment >= 0)///调高饱和度
			{
                alpha = std::max(S,1 - increment);
				alpha = 1 / alpha - 1;

				r_new = r + (r - L * 255) * alpha;
				g_new = g + (g - L * 255) * alpha;
				b_new = b + (b - L * 255) * alpha;
			}
			else///调低饱和度
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
	createTrackbar("饱和度", "image", &increment_value, 200, Saturation);

	Saturation(0, 0);//饱和度


	waitKey();
	image.release();
	src.release();

	return 0;
}
