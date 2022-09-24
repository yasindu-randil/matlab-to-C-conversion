
#ifndef MATSTACK_H
#define MATSTACK_H

#include "matSupport.h"

class matStack : public matSupport
{
	private:
		void initialize();
		void diffOperatorFFT();
		void fftConjugate(cv::Mat,  cv::Mat &, cv::Mat & ); 
		void printImageVectorMat( std::string, int);
		void printImageMat(std::string, const cv::Mat);

		int width;
		int height;
		int frames;
		int zbei;
		int siranu;
		double lamda;

		std::string printFile;

		std::vector<cv::Mat> imgS;
		cv::Mat frac[180];
		cv::Mat divide;

	public:

		matStack(std::string, std::string );
		
};

#endif

