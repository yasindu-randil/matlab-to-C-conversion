
/**
/*  matStack calculates on the main Image stack ( std::vector< cv::Mat )
/*  and run fast fourier transformations on the images.
/*
/*  Functions:
/*		Initialize the images vectors, arrays and cv::Mat
/*		Calculate the FFT and conjugate FFT
/*		Final output is cv::Mat frac and divide
/*
*/

#ifndef MATSTACK_H
#define MATSTACK_H

#include "matSupport.h"

class matStack : public matSupport
{
	private:
		//! Initialize 
		void initialize();
		void diffOperatorFFT();
		void fftConjugate(cv::Mat,  cv::Mat &, cv::Mat & ); 
		void printImageVectorMat( std::string, int);

		//! Variables


		std::string printFile;

		std::vector<cv::Mat> imgS;
		std::vector<cv::Mat> frac;

		cv::Mat divide;

	public:

		int zbei;
		int siranu;
		double lamda;

		int width;
		int height;
		int frames;
		matStack(std::string, std::string );

		std::vector<cv::Mat> getVectorFrac();
		std::vector<cv::Mat> getVectorImg();
		
		void printImageMat(std::string, const cv::Mat);
		
		void printImageMatStack(std::string, std::vector<cv::Mat> img);

};

#endif

