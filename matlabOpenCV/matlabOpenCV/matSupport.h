#ifndef MATSUPPORT_H
#define MATSUPPORT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

#include <fstream>
#include <math.h>
#include <string>
#include <iomanip>


class matSupport
{
	public:

		matSupport();

		void printTest();

		void fft2(const cv::Mat , cv::Mat& , int , int );

		cv::Mat converToRealNumbers( cv::Mat );
};

#endif

