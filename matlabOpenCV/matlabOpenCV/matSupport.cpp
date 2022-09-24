#include "matSupport.h"

matSupport::matSupport()
{
	std::cout << "Inside Mat Support Constructor" << std::endl;
}

void matSupport::printTest()
{
	std::cout << "Inside Mat Support printTest **************************************" << std::endl;

}

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
