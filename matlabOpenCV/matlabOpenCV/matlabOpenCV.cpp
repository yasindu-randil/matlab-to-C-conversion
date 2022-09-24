// matlabOpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "matStack.h"



void printTxt(cv::Mat img, std::ofstream& myfile);

int main()
{
	std::ofstream myfile;
	std::string printPath = "C:\\Users\\yryas\\OneDrive\\Desktop\\HessianSIM\\Output\\cppHessian.txt";
	std::string printPath2 = "C:\\Users\\yryas\\OneDrive\\Desktop\\HessianSIM\\Output\\optimized.txt";
	myfile.open(printPath, std::ios::out | std::ios::binary);

	
    std::cout << "Hello World!\n";
    std::string fileName = "C:\\Users\\yryas\\OneDrive\\Desktop\\HessianSIM\\Hessian_SIM\\raw-data\\Actin_97hz_7ms exposure raw data.tif";

    std::vector<cv::Mat> img;
	matStack obj(fileName, printPath2);
    // Read the mulit framed imaged into a  vector of cv::Mat
    imreadmulti(fileName, img, cv::IMREAD_UNCHANGED);

	std::cout << "After reading image" << std::endl;
	int width = img[0].cols;
	int height = img[0].rows;
	int numberofFrames = img.size();
	std::string filenameTemp = "";
	cv::Mat decImg(cv::Size(width, height), CV_32F, cv::Scalar(0));
	// Convert to CV_32FC1 from CV_16U

	for (int i = 0; i < numberofFrames; i++) {
		img[i].convertTo(img[i], CV_32F);
	}
	std::cout << "After converting" << std::endl;




	// *********************************** Initialization *************************************

	int iterBregman = 100; //number of iiterations
	double lamda = 0.5;
	int gexiang = 1;
	int siranu = 150; //mu value
	int zbei = 1; // sigma value
	double minVal;
	double maxVal, tempVal = 0.0;
	cv::Point minLoc;
	cv::Point maxLoc;
	// get the time 

	int yFlag = numberofFrames;

	if (yFlag < 3)
	{
		zbei = 0;
		//y(:,:,end+1:end+(3-size(y,3)))=repmat(y(:,:,end),[1,1,3-size(y,3)]);
		std::cout << "Number of data frame is smaller than 3, the t and z-axis of Hessian was turned off(sigma=0) " << std::endl;
	}

	// Get the maimum elemnt value
	for (int i = 0; i < numberofFrames; i++)
	{
		cv::minMaxLoc(img[i], &minVal, &maxVal, &minLoc, &maxLoc);
		if (tempVal < maxVal)
		{
			tempVal = maxVal;
		}
	}
	std::cout << "Max value from main = " << tempVal << std::endl;
	int yMax = tempVal;

	// Divide each element by yMax
	std::string filename = "";
	for (int i = 0; i < numberofFrames; i++) {
		img[i] = img[i] / yMax;
		//if (i == 179) {
			//printTxt(img[i], myfile);
		//}

		//filename = "C:\\Users\\yryas\\OneDrive\\Desktop\\Hessian SIM\\TIIFMULT\\openCV32F" + std::to_string(i + 1) + ".tiff";
		//cv::imwrite(filename, img[i]);
		if (i == 179) {
			printTxt(img[i], myfile);
		}
	}

	int sizeX[] = { width, height, numberofFrames };



	myfile.close();

}

void printTxt(cv::Mat img, std::ofstream& myfile)
{
	float tempVal = 0.0;
	//for (int col = 0; col < img.cols; col++) {
	//	for (int row = 0; row < img.rows; row++) {
	//		//process pixel:
	//		tempVal = img.at<float>(row, col);
	//		//std::cout << tempVal << std::endl;
	//		myfile << std::fixed << std::setprecision(4) << tempVal << std::endl;
	//		tempVal = 0.0;
	//	}
	//}

	myfile << img << std::endl;

}

void fft2(const cv::Mat in, cv::Mat& complexI, int rows, int cols) {
	cv::Mat padded;
	int m = cv::getOptimalDFTSize(rows);
	int n = cv::getOptimalDFTSize(cols);
	//copyMakeBorder(in, padded, 0, m - in.rows, 0, n - in.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	copyMakeBorder(in, padded, 0, m - in.rows, 0, n - in.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	merge(planes, 2, complexI);
	dft(complexI, complexI, cv::DFT_COMPLEX_OUTPUT);
}


