#include "matStack.h"


matStack::matStack( std::string filename, std::string printfile):
	printFile(printfile)
{
	std::cout << "Inside matStack Constructor" << std::endl;

	// Read the mulit framed imaged into a  vector of cv::Mat
	imreadmulti(filename, imgS, cv::IMREAD_UNCHANGED);
	initialize();
	diffOperatorFFT();
	printTest();

}

void matStack::initialize()
{
	int tempVal = 0;
	double testMaxval = 0;

	width = imgS[0].cols;
	height = imgS[0].rows;
	frames = imgS.size();
	
	// Convert to 4 byte floating values 
	// Get the max value
	for (int i = 0; i < frames; i++) {
		imgS[i].convertTo(imgS[i], CV_32F);

		minMaxIdx(imgS[i], 0, &testMaxval);
		if (tempVal < testMaxval)
		{
			tempVal = testMaxval;
		}


	}

	for (int i = 0; i < frames; i++)
	{
		imgS[i] /= tempVal;

	}


	printImageText(printFile, 179);


	std::cout << " Max Value from class = " << tempVal << std::endl;
}

void matStack::diffOperatorFFT()
{

}

void matStack::printImageText( std::string printfile, int index)
{
	std::ofstream myfile;
	myfile.open(printfile, std::ios::out | std::ios::binary);


	myfile << imgS[index] << std::endl;



	//}
	//float tempVal = 0.0;
	//for (int col = 0; col < width; col++) {
	//	for (int row = 0; row < height; row++) {
	//		//process pixel:
	//		tempVal = imgS[index].at<float>(row, col);
	//		//std::cout << tempVal << std::endl;
	//		myfile << std::fixed << std::setprecision(4) << tempVal << std::endl;
	//		tempVal = 0.0;
	//	}
	//}

	myfile.close();
}
