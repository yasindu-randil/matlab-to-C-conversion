#include "matDifferentiate.h"

matDifferentiate::matDifferentiate(std::string readPath, std::string write_path):
	matStack(readPath, writePath),
	writePath(write_path)
{
	std::cout << "Inside Mat Differentiate Constructor" << std::endl;
	frac = getVectorFrac();
	imgD = getVectorImg();
	initialize();
	iterateMat();

	
}

void matDifferentiate::initialize()
{

	// Prevents re-allocation of the vector as push_back is used.
	u.reserve(frames);
	signd.reserve(frames);
	d.reserve(frames);
	x.reserve(frames);

	b1.reserve(frames);
	b2.reserve(frames);
	b3.reserve(frames);
	b4.reserve(frames);
	b5.reserve(frames);
	b6.reserve(frames);

	// Initialize  empty cv::Mat to zero
	for (int i = 0; i < frames; i++)
	{
		u.push_back(cv::Mat::zeros(height, width, CV_32F));
		signd.push_back(cv::Mat::zeros(height, width, CV_32F));
		d.push_back(cv::Mat::zeros(height, width, CV_32F));
		x.push_back(cv::Mat::zeros(height, width, CV_32F));

		b1.push_back(cv::Mat::zeros(height, width, CV_32F));
		b2.push_back(cv::Mat::zeros(height, width, CV_32F));
		b3.push_back(cv::Mat::zeros(height, width, CV_32F));
		b4.push_back(cv::Mat::zeros(height, width, CV_32F));
		b5.push_back(cv::Mat::zeros(height, width, CV_32F));
		b6.push_back(cv::Mat::zeros(height, width, CV_32F));
	}
}

void matDifferentiate::iterateMat()
{

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


		subIterationOne();
		printImageMatStack(writePath, frac);
	}





}

void matDifferentiate::subIterationOne()
{
	
	for (int count=0; count < frames; count++)
	{
		frac[count] = imgD[count] * (siranu / lamda);
		u[count] = backwardDiffFunction(forwardDiffFunction(x[count], 1, 1, 180), 1, 1, 180);

		signd[count] = cv::abs(u[count] + b1[count]) - 1 / lamda;

		//// signd=signd.*sign(u+b1);
		for (int j = 0; j < width; j++) {
			for (int i = 0; i < height; i++) {
				if (signd[count].at<float>(i, j) < 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}

				if ((u[count].at<float>(i, j) + b1[count].at<float>(i, j)) > 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * 1.0;
				}
				else if ((u[count].at<float>(i, j) + b1[count].at<float>(i, j)) == 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}
				else if ((u[count].at<float>(i, j) + b1[count].at<float>(i, j)) < 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * (-1);
				}
			}
		}

		d[count] = signd[count];
		// b1 = b1+(u-d);
		b1[count] = b1[count] + (u[count] - d[count]);

		//frac = frac+back_diff(forward_diff(d-b1,1,1),1,1);
		frac[count] = frac[count] + backwardDiffFunction(forwardDiffFunction(d[count] - b1[count], 1, 1, 180), 1, 1, 180);
	}
}
