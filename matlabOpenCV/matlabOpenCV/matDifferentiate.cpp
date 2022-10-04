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

/*
*  Calculate the derivate of x.
*/
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
		subIterationTwo();
		subIterationThree();
		subIterationFour();
		subIterationFive();
		subIterationSix();
		printImageMatStack(writePath, frac);
	}





}
/*
*  Calculate new frac using forward and backward differentiation.
*/
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

/*
*  Calculate new frac using forward and backward differentiation.
*/
void matDifferentiate::subIterationTwo()
{
	for (int count = 0; count < frames; count++)
	{
		//u = back_diff(forward_diff(x,1,2),1,2);
		u[count] = backwardDiffFunction(forwardDiffFunction(x[count], 1, 2, 180), 1, 2, 180);
		//signd = abs(u + b2) - 1 / lamda
		signd[count] = cv::abs(u[count] + b2[count]) - 1 / lamda;

		//signd=signd.*sign(u+b2);
		for (int j = 0; j < width; j++) {
			for (int i = 0; i < height; i++) {
				if (signd[count].at<float>(i, j) < 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}

				if ((u[count].at<float>(i, j) + b2[count].at<float>(i, j)) > 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * 1.0;
				}
				else if ((u[count].at<float>(i, j) + b2[count].at<float>(i, j)) == 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}
				else if ((u[count].at<float>(i, j) + b2[count].at<float>(i, j)) < 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * (-1);
				}
			}
		}

		d[count] = signd[count];
		// b2 = b2+(u-d);
		b2[count] = b2[count] + (u[count] - d[count]);

		//frac = frac+back_diff(forward_diff(d-b2,1,2),1,2);
		frac[count] = frac[count] + backwardDiffFunction(forwardDiffFunction(d[count] - b2[count], 1, 2, 180), 1, 2, 180);

	}

}

/*
*  Calculate new frac using forward and backward differentiation.
*/
void matDifferentiate::subIterationThree()
{
	for (int count = 0; count < frames; count++)
	{
		u[count] = backwardDiffFunction(forwardDiffFunction(x[count], 1, 3, 180), 1, 3, 180);

		// signd = abs(u+b3)-1/lamda;
		signd[count] = cv::abs(u[count] + b3[count]) - 1 / lamda;

		//signd=signd.*sign(u+b3);
		for (int j = 0; j < width; j++) {
			for (int i = 0; i < height; i++) {
				if (signd[count].at<float>(i, j) < 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}

				if ((u[count].at<float>(i, j) + b3[count].at<float>(i, j)) > 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * 1.0;
				}
				else if ((u[count].at<float>(i, j) + b3[count].at<float>(i, j)) == 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}
				else if ((u[count].at<float>(i, j) + b3[count].at<float>(i, j)) < 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * (-1);
				}
			}
		}

		d[count] = signd[count];
		// b3 = b3+(u-d);
		b3[count] = b3[count] + (u[count] - d[count]);

		// frac = frac+(zbei^2)*back_diff(forward_diff(d-b3,1,3),1,3);
		frac[count] = frac[count] + (zbei * zbei) * backwardDiffFunction(forwardDiffFunction(d[count] - b3[count], 1, 3, 180), 1, 3, 180);

	}
}

/*
*  Calculate new frac using forward and backward differentiation.
*/
void matDifferentiate::subIterationFour()
{
	for (int count = 0; count < frames; count++)
	{
		// u = forward_diff(forward_diff(x,1,1),1,2);
		u[count] = forwardDiffFunction(forwardDiffFunction(x[count], 1, 1, 180), 1, 2, 180);

		//signd = abs(u+b4)-1/lamda;
		signd[count] = cv::abs(u[count] + b4[count]) - 1 / lamda;

		//    signd(signd<0)=0;
		//signd = signd.*sign(u + b4);
		for (int j = 0; j < width; j++) {
			for (int i = 0; i < height; i++) {
				if (signd[count].at<float>(i, j) < 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}

				if ((u[count].at<float>(i, j) + b4[count].at<float>(i, j)) > 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * 1.0;
				}
				else if ((u[count].at<float>(i, j) + b4[count].at<float>(i, j)) == 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}
				else if ((u[count].at<float>(i, j) + b4[count].at<float>(i, j)) < 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * (-1);
				}
			}
		}
		d[count] = signd[count];
		// b4 = b4+(u-d);
		b4[count] = b4[count] + (u[count] - d[count]);

		//frac = frac+ 2 * back_diff(back_diff(d-b4,1,2),1,1);
		frac[count] = frac[count] + 2 * backwardDiffFunction(backwardDiffFunction(d[count] - b4[count], 1, 2, 180), 1, 1, 180);
	}
}

/*
*  Calculate new frac using forward and backward differentiation.
*/
void matDifferentiate::subIterationFive()
{
	for (int count = 0; count < frames; count++)
	{
		//u = forward_diff(forward_diff(x,1,1),1,3);
		u[count] = forwardDiffFunction(forwardDiffFunction(x[count], 1, 1, 180), 1, 3, 180);

		//signd = abs(u+b5)-1/lamda;
		signd[count] = cv::abs(u[count] + b5[count]) - 1 / lamda;

		//    signd(signd<0)=0;
		//signd = signd.*sign(u + b5);
		for (int j = 0; j < width; j++) {
			for (int i = 0; i < height; i++) {
				if (signd[count].at<float>(i, j) < 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}

				if ((u[count].at<float>(i, j) + b5[count].at<float>(i, j)) > 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * 1.0;
				}
				else if ((u[count].at<float>(i, j) + b5[count].at<float>(i, j)) == 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}
				else if ((u[count].at<float>(i, j) + b5[count].at<float>(i, j)) < 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * (-1);
				}
			}
		}

		d[count] = signd[count];
		// b5 = b5+(u-d);
		b5[count] = b5[count] + (u[count] - d[count]);

		//frac = frac+ 2 * (zbei)*back_diff(back_diff(d-b5,1,3),1,1);
		frac[count] = frac[count] + 2 * zbei * backwardDiffFunction(backwardDiffFunction(d[count] - b5[count], 1, 3, 180), 1, 1, 180);

	}
}

/*
*  Calculate new frac using forward and backward differentiation.
*/
void matDifferentiate::subIterationSix()
{
	for (int count = 0; count < frames; count++)
	{
		//u = forward_diff(forward_diff(x,1,2),1,3);
		u[count] = forwardDiffFunction(forwardDiffFunction(x[count], 1, 2, 180), 1, 3, 180);

		//signd = abs(u+b6)-1/lamda;
		signd[count] = cv::abs(u[count] + b6[count]) - 1 / lamda;

		//    signd(signd<0)=0;
		//signd = signd.*sign(u + b5);
		for (int j = 0; j < width; j++) {
			for (int i = 0; i < height; i++) {
				if (signd[count].at<float>(i, j) < 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}

				if ((u[count].at<float>(i, j) + b6[count].at<float>(i, j)) > 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * 1.0;
				}
				else if ((u[count].at<float>(i, j) + b6[count].at<float>(i, j)) == 0)
				{
					signd[count].at<float>(i, j) = 0.0;
				}
				else if ((u[count].at<float>(i, j) + b6[count].at<float>(i, j)) < 1)
				{
					signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * (-1);
				}
			}
		}

		d[count] = signd[count];
		// b6 = b6+(u-d);
		b6[count] = b6[count] + (u[count] - d[count]);

		//frac = frac+ 2 * (zbei)*back_diff(back_diff(d-b6,1,3),1,2);
		frac[count] = frac[count] + 2 * zbei * backwardDiffFunction(backwardDiffFunction(d[count] - b6[count], 1, 3, 180), 1, 2, 180);
	}
}