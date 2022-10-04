#include "matSupport.h"

matSupport::matSupport()
{

}

void matSupport::printTest()
{
	std::cout << "Inside Mat Support printTest " << std::endl;

}

/* Calculate Discrete Fourier transformation on received cv::Mat
/* Use complex output
*/
void matSupport :: fft2(const cv::Mat in, cv::Mat& complexI, int rows, int cols) {
	cv::Mat padded;
	int m = cv::getOptimalDFTSize(rows);
	int n = cv::getOptimalDFTSize(cols);
	//copyMakeBorder(in, padded, 0, m - in.rows, 0, n - in.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	copyMakeBorder(in, padded, 0, m - in.rows, 0, n - in.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	merge(planes, 2, complexI);
	dft(complexI, complexI, cv::DFT_COMPLEX_OUTPUT);
}


/* Extract real numbers from cv::Mat.
/* return the real numbers as a cv::Mat
*/
cv::Mat matSupport::converToRealNumbers( cv::Mat img )
{
	cv::Mat temp(cv::Size(256, 128), CV_32F, cv::Scalar(0));
	std::complex<float> tempVal = 0.0;
	float realVal = 0.0;
	for (int col = 0; col < img.cols; col++) {
		for (int row = 0; row < img.rows; row++) {
			//process pixel:
			realVal = img.at<std::complex<float> >(row, col).real();
			temp.at<float>(row, col) = realVal;
			realVal = 0.0;
		}
	}

	return temp;
}

/* Calculate Inverse Discrete Fourier transformation on received cv::Mat
*/
void matSupport :: inverseDFT(const cv::Mat in, cv::Mat& complexI, int rows, int cols) {
	cv::Mat padded;
	int m = cv::getOptimalDFTSize(rows);
	int n = cv::getOptimalDFTSize(cols);
	//copyMakeBorder(in, padded, 0, m - in.rows, 0, n - in.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	copyMakeBorder(in, padded, 0, m - in.rows, 0, n - in.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	//merge(planes, 2, complexI);
	dft(complexI, complexI);
}

// Helper functions and debug functions
std::string matSupport :: type2str(int type) {
	std::string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}



