#ifndef MATDIFF_H
#define MATDIFF_H
#include <opencv2/core/core.hpp>


class matDiff
{
	public:
		matDiff();

		cv::Mat forwardDiffFunction(cv::Mat, int, int, const int);
};

#endif

