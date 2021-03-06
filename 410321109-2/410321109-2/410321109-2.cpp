#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#include <highgui.h>
#include <math.h>


int main()
{
	IplImage *insert, *outo, *outo2;

	char InputFileName[] = "C:\\Users\\Bao\\Desktop\\ezreal.jpg";
	insert = cvLoadImage(InputFileName, CV_LOAD_IMAGE_COLOR);

	if (!insert)
	{
		printf("Can't open the image.\n");
		system("pause");
	}
	outo = cvCreateImage(cvSize(insert->width, insert->height), 8, 3);
	outo2 = cvCreateImage(cvSize(insert->width, insert->height), 8, 3);

	unsigned short *GrayArr = (unsigned short *)calloc(insert->height*insert->width, sizeof(unsigned short));
	unsigned short *BlackWhiteArr = (unsigned short *)calloc(insert->height*insert->width, sizeof(unsigned short));

	int width = insert->width;
	int height = insert->height;

	for (int i = 0; i < insert -> height; i++) {
		for (int j = 0; j < insert -> width; j++) {
			CvScalar x = cvGet2D(insert, i, j);

			int y = 0.299*x.val[2] + 0.587*x.val[1] + 0.114*x.val[0];
			GrayArr[i*insert->width + j] = y;

			cvSet2D(outo2, i, j, CV_RGB(GrayArr[i*insert->width + j], GrayArr[i*insert->width + j], GrayArr[i*insert->width + j]));
		}
	}
	int table[2][2] = {{0,128},{192,64}};

	int skipX = 2, skipY = 2, gray = 0;
	for (int r = 0; r<height - skipY; r += skipY)
	{
		for (int c = 0; c<width - skipX; c += skipX)
		{
			for (int row = 0; row<skipY; ++row)
			{
				for (int col = 0; col<skipX; ++col)
				{
					CvScalar xa = cvGet2D(insert, r + row, c + col);
					int gray = 0.299*xa.val[2] + 0.587*xa.val[1] + 0.114*xa.val[0];//gray
					if (gray >= table[row][col]) {
						BlackWhiteArr[r *insert->width + c] = 256;
					}
					else {
						BlackWhiteArr[r *insert->width + c] = 0;
					}
					cvSet2D(outo, (r + row), (c + col), CV_RGB(BlackWhiteArr[r*insert->width + c], BlackWhiteArr[r*insert->width + c], BlackWhiteArr[r*insert->width + c]));
				}
			}
		}
	}

	cvNamedWindow("none", 0);
	cvNamedWindow("gray", 0);
	cvNamedWindow("black", 0);

	cvShowImage("none", insert);
	cvShowImage("gray", outo2);
	cvShowImage("black", outo);


	cvWaitKey(0);
	free(GrayArr);

	cvReleaseImage(&insert);
	cvReleaseImage(&outo);

	cvDestroyWindow("First");
	cvDestroyWindow("Gray");
	cvDestroyWindow("BlackWhite");

	return 0;
}