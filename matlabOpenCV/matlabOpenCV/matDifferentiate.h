#ifndef MATDIFFERENTIATE_H
#define MATDIFFERENTIATE_H

#include "matStack.h"
#include "matDiff.h"

// Define a pixel
typedef cv::Point_<uchar> Pixel;


class matDifferentiate : protected matStack, matDiff
{
	public:

		matDifferentiate(std::string, std::string);

	private:

		struct Operator {
			void operator ()(Pixel& pixel, const int* position) const
			{
				//std::cout << cv::format("[%d,%d]= %d \n", position[0], position[1], (int)pixel.x);
			}
		};

		std::vector<cv::Mat> frac;
		std::vector<cv::Mat> imgD;
		std::string writePath;

		std::vector<cv::Mat> x;
		std::vector<cv::Mat> u;
		std::vector<cv::Mat> signd;
		std::vector<cv::Mat> d;

		std::vector<cv::Mat> b1;
		std::vector<cv::Mat> b2;
		std::vector<cv::Mat> b3;
		std::vector<cv::Mat> b4;
		std::vector<cv::Mat> b5;
		std::vector<cv::Mat> b6;

		void initialize();
		void iterateMat();

		void subIterationOne();
		void subIterationTwo();
		void subIterationThree();
		void subIterationFour();
		void subIterationFive();
		void subIterationSix();
};

#endif

