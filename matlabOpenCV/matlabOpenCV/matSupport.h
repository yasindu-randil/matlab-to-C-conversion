/**
/* matSupport works as the base calss which contains all the basic supporting 
/*  functions for this program. 
/*
/*  Functions related to:
/*		Fast fourier Transformatiom,
/*      Inverse DFT,
/*		Basic print functions for cv::Mat,
/*		Functions for retriving Complex or Real part of a cv::Mat.
/*
/*  This class is designed to add more supporting functions so the derived classes
/*  can be more efficient and user-friendly.
*/

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

		void inverseDFT(const cv::Mat , cv::Mat& , int , int );
	
};

#endif

