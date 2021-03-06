#include "stdafx.h"

#include <cv.h>
#include <highgui.h>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include<iostream>

using namespace std;

int main() {
	IplImage *pic1 = cvLoadImage("C:snap89.pgm", 1);
	IplImage *pic2 = cvLoadImage("C:snap88.jpg", 1);
	IplImage *pic3;
	pic3 = cvCreateImage(cvGetSize(pic1), pic1->depth, pic1->nChannels);
	
	long long int sigma = 0;
	long long int squre = 0;
	double MSE = 0.0;
	double SNR = 0.0;
	double PSNR = 0.0;
	int frameSize = pic1->height*pic1->width * 3;
	int blue1 = 0, blue2 = 0;
	int green1 = 0, green2 = 0;
	int red1 = 0, red2 = 0;


	for (int i = 0; i<pic1->height; i++) {
		for (int j = 0; j<pic1->widthStep; j = j + 3) {
			blue1 = (int)(uchar)pic1->imageData[i*pic1->widthStep + j];
//Blue
			green1 = (int)(uchar)pic1->imageData[i*pic1->widthStep + j + 1];
//Green
			red1 = (int)(uchar)pic1->imageData[i*pic1->widthStep + j + 2];
//Red
			blue2 = (int)(uchar)pic2->imageData[i*pic2->widthStep + j];
//Blue
			green2 = (int)(uchar)pic2->imageData[i*pic2->widthStep + j + 1];
//Green
			red2 = (int)(uchar)pic2->imageData[i*pic2->widthStep + j + 2];
//Red
			sigma += (blue1 - blue2)*(blue1 - blue2) +
				(green1 - green2)*(green1 - green2) +
				(red1 - red2)*(red1 - red2);
			squre += blue1*blue1 + green1*green1 + red1*red1;
		}
	}
	for (int x = 0; x < pic1->width; x++)
	{
		for (int y = 0; y < pic1->height; y++)
		{
			/* 索引值 */
			int index = y * pic1->widthStep + x;
			/* 影像相加 */
			pic3->imageData[index] = pic1->imageData[index] + pic2->imageData[index];
		}
	}
	MSE = sigma / (double)frameSize;
	PSNR = 10 * log10(255 * 255 / MSE);
	SNR = 10 * log10(squre / sigma);
	//顯示圖片

	cvNamedWindow("a", 1);
	cvShowImage("a", pic1);
	cvNamedWindow("b", 1);
	cvShowImage("b", pic2);
	cvNamedWindow("c", 1);
	cvShowImage("c", pic3);
	//顯示差值
	cout << "MSE: " << MSE << endl;;
	cout << "PSNR: " << PSNR << endl;;
	cout << "SNR: " << SNR << endl;;
	
	system("pause");
	cvWaitKey(0);
	return EXIT_SUCCESS;
}