/**
/*  Provides the forward and backward differentiation functions.
/*  This will work as another base class.
/*
/*  Functions:
/*		Calculate the forward differentiation of a single cv::Mat
/*		Calculate the backward differentiation of a single cv::Mat
/*
*/

#ifndef MATDIFF_H
#define MATDIFF_H
#include <opencv2/core/core.hpp>


class matDiff
{
	public:
		matDiff();

		cv::Mat forwardDiffFunction(cv::Mat, int, int, const int);

		cv::Mat backwardDiffFunction(cv::Mat, int, int, const int);
};

#endif

