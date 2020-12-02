#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<map>
#include<algorithm>
#include<set>

using namespace std;
using namespace cv;

///���㰵ͨ��ͼ����������ͨ����ɫͼ��(rgb����ͨ����ȡ��Сֵ��ɻҶ�ͼ��Ȼ���ٽ���һ����Сֵ�˲��õ���)
Mat dark_channel(Mat src)
{
	int border = 7;
	std::vector<cv::Mat> rgbChannels(3);
	Mat min_mat(src.size(), CV_8UC1, Scalar(0));
	Mat min_mat_expansion;
	Mat dark_channel_mat(src.size(), CV_8UC1, Scalar(0));///����rgbͼ��

	split(src, rgbChannels);///�Ը���ͨ�����з��룬rgb����ͨ����ȡ��Сֵ��ɻҶ�ͼ
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			int min_val = 0;
			int val_1, val_2, val_3;
			val_1 = rgbChannels[0].at<uchar>(i, j);
			val_2 = rgbChannels[1].at<uchar>(i, j);
			val_3 = rgbChannels[2].at<uchar>(i, j);

			min_val = std::min(val_1, val_2);
			min_val = std::min(min_val, val_3);

			min_mat.at<uchar>(i, j) = min_val;

		}
	}

	///������Ҷ�ͼ������Сֵ�˲����˲��İ뾶�ɴ��ڴ�С������һ����WindowSize = 2 * Radius + 1
	copyMakeBorder(min_mat, min_mat_expansion, border, border, border, border, BORDER_REPLICATE);///��ͼ�ν��б߽������

	for (int m = border; m < min_mat_expansion.rows - border; m++)
	{
		for (int n = border; n < min_mat_expansion.cols - border; n++)
		{
			Mat imageROI;
			int min_num = 256;
			imageROI = min_mat_expansion(Rect(n - border, m - border, 2 * border + 1, 2 * border + 1));
			for (int i = 0; i < imageROI.rows; i++)
			{
				for (int j = 0; j < imageROI.cols; j++)
				{
					int val_roi = imageROI.at<uchar>(i, j);
					min_num = std::min(min_num, val_roi);
				}
			}
			dark_channel_mat.at<uchar>(m - border, n - border) = min_num;
		}
	}
	return dark_channel_mat;
}

///   A
int calculate_A(Mat src, Mat dark_channel_mat)
{
	std::vector<cv::Mat> rgbChannels(3);
	split(src, rgbChannels);
	map<int, Point> pair_data;
	map<int, Point>::iterator iter;
	vector<Point> cord;
	int max_val = 0;
	//cout << dark_channel_mat.rows << " " << dark_channel_mat.cols << endl;
	for (int i = 0; i < dark_channel_mat.rows; i++)
	{
		for (int j = 0; j < dark_channel_mat.cols; j++)
		{
			int val = dark_channel_mat.at<uchar>(i, j);
			Point pt;
			pt.x = j;
			pt.y = i;
			pair_data.insert(make_pair(val, pt));
		}
	}

	for (iter = pair_data.begin(); iter != pair_data.end(); iter++)
	{
		//cout << iter->second << endl;
		cord.push_back(iter->second);
	}
	for (int m = 0; m < cord.size(); m++)
	{
		Point tmp = cord[m];
		int val_1, val_2, val_3;
		val_1 = rgbChannels[0].at<uchar>(tmp.y, tmp.x);
		val_2 = rgbChannels[1].at<uchar>(tmp.y, tmp.x);
		val_3 = rgbChannels[2].at<uchar>(tmp.y, tmp.x);
		max_val = std::max(val_1, val_2);
		max_val = std::max(max_val, val_3);
		//cout<<max_val<<endl;
	}

	return max_val;
}

///  t(x)=1-w*(dark_channel_mat/A)
Mat calculate_tx(Mat &src, int A, Mat &dark_channel_mat)
{
	Mat dst;//����������t(x)
	Mat tx;
	float dark_channel_num;
	dark_channel_num = A / 255.0;
	dark_channel_mat.convertTo(dst, CV_32FC3, 1 / 255.0);//��������t(x)
	dst = dst / dark_channel_num;
	tx = 1 - 0.95*dst;//���յ�txͼ

	return tx;
}

///�����˲��������Ż�t(x)����Ե�ͨ��
Mat guidedfilter(Mat &srcImage, Mat &tx, int r, double eps)///��dst���Ҷ�ͼ����tx��30,0.001��
{
	//ת��Դͼ����Ϣ
	srcImage.convertTo(srcImage, CV_32FC1, 1 / 255.0);
	tx.convertTo(tx, CV_32FC1);
	int nRows = srcImage.rows;
	int nCols = srcImage.cols;

	//����һ�������ֵ
	Mat boxResult;
	boxFilter(Mat::ones(nRows, nCols, srcImage.type()),boxResult, CV_32FC1, Size(r, r));
	//���ɵ����ֵmean_I
	Mat mean_I;
	boxFilter(srcImage, mean_I, CV_32FC1, Size(r, r));
	//����ԭʼ��ֵmean_p
	Mat mean_p;
	boxFilter(tx, mean_p, CV_32FC1, Size(r, r));
	//���ɻ���ؾ�ֵmean_Ip
	Mat mean_Ip;
	boxFilter(srcImage.mul(tx), mean_Ip,CV_32FC1, Size(r, r));
	Mat cov_Ip = mean_Ip - mean_I.mul(mean_p);
	//��������ؾ�ֵmean_II
	Mat mean_II;
	//Ӧ�ú��˲���������ص�ֵ
	boxFilter(srcImage.mul(srcImage), mean_II,CV_32FC1, Size(r, r));
	//��������������ϵ��
	Mat var_I = mean_II - mean_I.mul(mean_I);
	Mat var_Ip = mean_Ip - mean_I.mul(mean_p);
	//���������������ϵ��a,b
	Mat a = cov_Ip / (var_I + eps);
	Mat b = mean_p - a.mul(mean_I);
	//�����ģ�����ϵ��a\b�ľ�ֵ
	Mat mean_a;
	boxFilter(a, mean_a, CV_32FC1, Size(r, r));
	mean_a = mean_a / boxResult;
	Mat mean_b;
	boxFilter(b, mean_b, CV_32FC1, Size(r, r));
	mean_b = mean_b / boxResult;
	//�����壺�����������
	Mat resultMat = mean_a.mul(srcImage) + mean_b;
	return resultMat;
}

/// J(x)=[I(x)-A / max_t] + A
Mat haze_removal_img(Mat &src, int A, Mat &tx)
{
	Mat result_img(src.rows, src.cols, CV_8UC3);
	vector<Mat> srcChannels(3), resChannels(3);
	split(src, srcChannels);
	split(result_img, resChannels);///���ͨ��������j(x)

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			for (int m = 0; m < 3; m++)
			{
				int value_num = srcChannels[m].at<uchar>(i, j);
				float max_t = tx.at<float>(i, j);
				if (max_t < 0.1)
				{
					max_t = 0.1;
				}
				resChannels[m].at<uchar>(i, j) = (value_num - A) / max_t + A;
			}
		}
	}
	merge(resChannels, result_img);///�ϲ�ͨ��

	return result_img;
}


int main()
{
	Mat src = imread("images/5.jpg");
	Mat dst;

    namedWindow("ԭʼͼ��", 0);
	imshow("ԭʼͼ��", src);

	cvtColor(src, dst, CV_BGR2GRAY);///ԭͼsrcת��Ϊ�Ҷ�ͼrgb2grayu�����ڵ����˲��Ż�tx

	Mat dark_channel_mat = dark_channel(src);///������ǰ�ͨ��ͼ��

	int A = calculate_A(src, dark_channel_mat);///����A

	Mat tx = calculate_tx(src, A, dark_channel_mat);///����tx
	Mat tx_ = guidedfilter(dst, tx, 30, 0.001);///�����˲����tx��r=30��eps=0.001

	Mat haze_removal_image = haze_removal_img(src, A, tx_);///����J(x)

	namedWindow("ȥ����ͼ��", 0);
	imshow("ȥ����ͼ��", haze_removal_image);


	waitKey(0);
	return 0;
}
