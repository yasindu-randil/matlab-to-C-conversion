#include "matDifferentiate.h"

matDifferentiate::matDifferentiate(std::string readPath, std::string write_path):
	matStack(readPath, writePath),
	writePath(write_path)
{
	std::cout << "Inside Mat Differentiate Constructor" << std::endl;
	frac = getVectorFrac();

	iterateMat();

	
}

void matDifferentiate::iterateMat()
{
	cv::Mat x[180], u[180], signd[180], d[180];
	cv::Mat b1[180], b2[180], b3[180], b4[180], b5[180], b6[180];

	// Initialize  empty cv::Mat to zero
	for (int i = 0; i < frames; i++)
	{
		u[i].convertTo(u[i], CV_32F);
		signd[i].convertTo(signd[i], CV_32F);
		d[i].convertTo(d[i], CV_32F);

		b1[i] = { cv::Mat::zeros(height, width, CV_32F) };
		b2[i] = { cv::Mat::zeros(height, width, CV_32F) };
		b3[i] = { cv::Mat::zeros(height, width, CV_32F) };
		b4[i] = { cv::Mat::zeros(height, width, CV_32F) };
		b5[i] = { cv::Mat::zeros(height, width, CV_32F) };
		b6[i] = { cv::Mat::zeros(height, width, CV_32F) };
		x[i] = { cv::Mat::zeros(height, width, CV_32F) };
	}

	// This if-condition should be converted to a for loop.
	// currently, it is always true if condition.
	//for( int i=0; i<100; i++)
	if (true)
	{
		//this loop mimics fftn dunction in matlab
		for (int i = 0; i < frames; i++)
		{
			fft2(frac[i], frac[i], height, width);
		}



		//If-else for itration greater than 1
		for (int j = 0; j < frames; j++)
		{
			cv::idft(frac[j] / (siranu / lamda), x[j], cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT);
		}
		printImageMat(writePath, x[179]);
	}





}
