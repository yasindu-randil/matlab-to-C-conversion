
#ifndef MATSTACK_H
#define MATSTACK_H

#include "matSupport.h"

class matStack : public matSupport
{
	private:
		void initialize();
		void diffOperatorFFT();
		void printImageText( std::string, int);

		int width;
		int height;
		int frames;

		std::string printFile;

		std::vector<cv::Mat> imgS;

	public:

		matStack(std::string, std::string );
		
};

#endif

