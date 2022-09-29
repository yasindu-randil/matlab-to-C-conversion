#ifndef MATDIFFERENTIATE_H
#define MATDIFFERENTIATE_H

#include "matStack.h"
#include "matDiff.h"

class matDifferentiate : public matStack, matDiff
{
	public:

		matDifferentiate(std::string, std::string);

	private:

		std::vector<cv::Mat> frac;
		std::string writePath;

		void iterateMat();
};

#endif

