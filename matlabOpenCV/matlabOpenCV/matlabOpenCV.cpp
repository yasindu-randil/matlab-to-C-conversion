// matlabOpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "matDifferentiate.h"



void printTxt(cv::Mat img, std::ofstream& myfile);
void printTxtStack(cv::Mat img[], std::ofstream& myfile);
void fft2(const cv::Mat in, cv::Mat& complexI, int rows, int cols);
cv::Mat converToRealNumbers(cv::Mat img);
cv::Mat backwardDiffFunction(cv::Mat img, int step, int dim, int frameCount);
cv::Mat forwardDiffFunction(cv::Mat img, int step, int dim, const int framesCount);

int main()
{
	std::ofstream myfile;
	std::string printPath = "C:\\Users\\yryas\\OneDrive\\Desktop\\HessianSIM\\Output\\cppHessian.txt";
	std::string printPath2 = "C:\\Users\\yryas\\OneDrive\\Desktop\\HessianSIM\\Output\\optimized.txt";
	myfile.open(printPath, std::ios::out | std::ios::binary);

	
    std::cout << "Hello World!\n";
    std::string fileName = "C:\\Users\\yryas\\OneDrive\\Desktop\\HessianSIM\\Hessian_SIM\\raw-data\\Actin_97hz_7ms exposure raw data.tif";

    std::vector<cv::Mat> img;
	matDifferentiate obj(fileName, printPath2);
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

	}

	int sizeX[] = { width, height, numberofFrames };

	// Second Portion ****************************************
		float data[3] = { 1, -2, 1 };
		float data2[3][1] = { {1}, {-2}, { 1} };
		float dataZtiduzz[3] = { 0 };
		float data3[2][2][2][2] = { {{1, -1}, {1, -1}}, {{-1, 1}, {-1, 1}} };
		float data4[2][2] = { {1 ,-1},{-1 ,1} };
		float data5[2][2][2] = { { {1}, {-1} }, { {-1}, {1} } };

		cv::Mat fftData = cv::Mat(1, 3, CV_32F, data);
		cv::Mat fftData2 = cv::Mat(3, 1, CV_32F, data2);
		cv::Mat ztiduzz = cv::Mat(1, 3, CV_32F, dataZtiduzz);
		cv::Mat fftData4 = cv::Mat(2, 2, CV_32F, data4);
		cv::Mat ztiduxz = cv::Mat(2, 2, CV_32F, data3);
		cv::Mat ztiduyz = cv::Mat(2, 2, CV_32F, data5);

		cv::Mat fftOutput;
		cv::Mat fftOutput2;
		cv::Mat fftOutput3;
		cv::Mat fftOutput4;
		cv::Mat fftOutput5;
		cv::Mat fftOutput6;

		cv::Mat fftConj;
		cv::Mat fftConj2;
		cv::Mat fftConj3;
		cv::Mat fftConj4;
		cv::Mat fftConj5;
		cv::Mat fftConj6;

		fft2(fftData, fftOutput, height, width);
		// Get multiplication of two cv::Mat. In this case the conjugate of second 
		// Mat will be used. 
		// 
		cv::mulSpectrums(fftOutput, fftOutput, fftConj, 0, true);
		

		fft2(fftData2, fftOutput2, height, width);
		cv::mulSpectrums(fftOutput2, fftOutput2, fftConj2, 0, true);
		cv::add(fftConj, fftConj2, fftConj2); //small differences 4th decimal place



		//tmp_fft=fftn(ztiduzz,sizex).*conj(fftn(ztiduzz,sizex));
		fft2(ztiduzz, fftOutput3, height, width);
		cv::mulSpectrums(fftOutput3, fftOutput3, fftConj3, 0, true);
		//fftConj3 = fftConj3 * (zbei * zbei);
		fftConj3.mul(fftConj3 * (zbei * zbei));
		cv::add(fftConj2, fftConj3, fftConj3);

		//tmp_fft=fftn([1 -1;-1 1],sizex).*conj(fftn([1 -1;-1 1],sizex));
		fft2(fftData4, fftOutput4, height, width);
		cv::mulSpectrums(fftOutput4, fftOutput4, fftConj4, 0, true);
		fftConj4 = fftConj4 * 2;
		//fftConj4.mul(fftConj4 * 2);
		cv::add(fftConj3, fftConj4, fftConj4);

		//tmp_fft=fftn(ztiduxz,sizex).*conj(fftn(ztiduxz,sizex));
		fft2(ztiduxz, fftOutput5, height, width);
		cv::mulSpectrums(fftOutput5, fftOutput5, fftConj5, 0, true);
		fftConj5 = fftConj5 * (zbei) * 2;
		//fftConj5.mul(fftConj5* 2 * zbei);
		cv::add(fftConj4, fftConj5, fftConj5);



		fft2(ztiduyz, fftOutput6, height, width);
		cv::mulSpectrums(fftOutput6, fftOutput6, fftConj6, 0, true);
		fftConj6 = fftConj6 * (2 * zbei);
		cv::add(fftConj5, fftConj6, fftConj6);



		//divide = single((siranu/lamda) + Frefft);
		fftConj6 = fftConj6 + (siranu / lamda);

		// frac = (siranu/lamda)*(y); 
		cv::Mat frac[180];
		for (int i = 0; i < numberofFrames; i++) {
			frac[i].convertTo(frac[i], CV_32F);
			frac[i] = img[i] * (siranu / lamda);
		}



	// End of Second portion

		cv::Mat tempFrac[2], tempFracFinal, divide;
		divide.convertTo(divide, CV_32F);
		divide = converToRealNumbers(fftConj6);


		//******************** ITERATION ***************************
		cv::Mat x[180], u[180], signd[180], d[180];
		cv::Mat b1[180], b2[180], b3[180], b4[180], b5[180], b6[180];

		for (int i = 0; i < numberofFrames; i++)
		{
			u[i].convertTo(u[i], CV_32F);
			signd[i].convertTo(signd[i], CV_32F);
			d[i].convertTo(d[i], CV_32F);

			b1[i] = { cv::Mat::zeros(height, width, CV_32F) };
			b2[i] = { cv::Mat::zeros(height, width, CV_32F) };
			b3[i] = { cv::Mat::zeros(height, width, CV_32F) };
			b4[i] = { cv::Mat::zeros(height, width, CV_32F) };
			b5[i] = { cv::Mat::zeros(height, width, CV_32F) };
			b6[i] = { cv::Mat::zeros(height, width, CV_32F) };
			x[i] = { cv::Mat::zeros(height, width, CV_32F) };
		}
		//100 iterations
		if (true)
		{
			// frac = fftn(frac);
			for (int i = 0; i < numberofFrames; i++)
			{
				fft2(frac[i], frac[i], height, width);
			}


			for (int j = 0; j < numberofFrames; j++)
			{
				//x = real(ifftn(frac./(siranu/lamda)));
				//frac[j] = frac[j] / (siranu / lamda);
				cv::idft(frac[j] / (siranu / lamda), x[j], cv::DFT_SCALE | cv::DFT_COMPLEX_OUTPUT);
			}


			//**************************** Block One *******************************
			for (int count = 0; count < numberofFrames; count++)
			{
				frac[count] = img[count] * (siranu / lamda);
				u[count] = backwardDiffFunction(forwardDiffFunction(x[count], 1, 1, 180), 1, 1, 180);

				signd[count] = cv::abs(u[count] + b1[count]) - 1 / lamda;

				//// signd=signd.*sign(u+b1);
				for (int j = 0; j < width; j++) {
					for (int i = 0; i < height; i++) {
						if (signd[count].at<float>(i, j) < 0)
						{
							signd[count].at<float>(i, j) = 0.0;
						}

						if ((u[count].at<float>(i, j) + b1[count].at<float>(i, j)) > 1)
						{
							signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * 1.0;
						}
						else if ((u[count].at<float>(i, j) + b1[count].at<float>(i, j)) == 0)
						{
							signd[count].at<float>(i, j) = 0.0;
						}
						else if ((u[count].at<float>(i, j) + b1[count].at<float>(i, j)) < 1)
						{
							signd[count].at<float>(i, j) = signd[count].at<float>(i, j) * (-1);
						}
					}
				}

				d[count] = signd[count];
				// b1 = b1+(u-d);
				b1[count] = b1[count] + (u[count] - d[count]);

				//frac = frac+back_diff(forward_diff(d-b1,1,1),1,1);
				frac[count] = frac[count] + backwardDiffFunction(forwardDiffFunction(d[count] - b1[count], 1, 1, 180), 1, 1, 180);

			}
			printTxtStack(frac, myfile);
			//**************************** END - Block One *******************************

		}

		//******************** END - ITERATION ***************************

		

			
			





		//**************************** End of Block One *******************************

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

void printTxtStack(cv::Mat img[], std::ofstream& myfile)
{
	float tempVal = 0.0;
	for (int i = 0; i < 180; i++)
	{
		myfile << img[i] << std::endl;
	}

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

cv::Mat converToRealNumbers(cv::Mat img)
{
	cv::Mat temp(cv::Size(256, 128), CV_32F, cv::Scalar(0));
	std::complex<float> tempVal = 0.0;
	float realVal = 0.0;
	for (int col = 0; col < img.cols; col++) {
		for (int row = 0; row < img.rows; row++) {
			//process pixel:
			realVal = img.at<std::complex<float> >(row, col).real();
			temp.at<float>(row, col) = realVal;
			realVal = 0.0;
		}
	}

	return temp;
}

cv::Mat backwardDiffFunction(cv::Mat img, int step, int dim, int frameCount)
{
	int width = img.cols;
	int height = img.rows;
	int numberOfFrames = frameCount;
	int cols = width;
	int rows = height;
	int rowStart = 0;
	int colStart = 0;
	int depth = 0;

	const int frames = frameCount + 1;
	cv::Mat temp1[2];
	cv::Mat temp2[2];
	cv::Mat out;

	//Initialize the Mat
	temp1[0].convertTo(temp1[0], CV_32F);
	temp1[0] = { cv::Mat::zeros(rows + 1, cols + 1, CV_32F) };

	temp1[1].convertTo(temp1[1], CV_32F);
	temp1[1] = { cv::Mat::zeros(rows + 1, cols + 1, CV_32F) };

	out.convertTo(out, CV_32F);
	out = { cv::Mat::zeros(rows, cols , CV_32F) };

	temp2[0].convertTo(temp2[0], CV_32F);
	temp2[0] = { cv::Mat::zeros(rows + 1, cols + 1, CV_32F) };

	temp2[1].convertTo(temp2[1], CV_32F);
	temp2[1] = { cv::Mat::zeros(rows + 1, cols + 1, CV_32F) };

	// temp1(position(1):SIZE(1),position(2):SIZE(2),position(3):SIZE(3))=data;
	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			temp1[depth].at<float>(i, j) = img.at<float>(i, j);
		}
	}

	// temp2(position(1):SIZE(1),position(2):SIZE(2),position(3):SIZE(3))=data;
	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			temp2[depth].at<float>(i, j) = img.at<float>(i, j);
		}
	}

	if (dim == 1)
	{
		height = height + 1;
		rowStart++;
	}
	else if (dim == 2)
	{
		width = width + 1;
		colStart++;
	}
	else if (dim == 3)
	{
		depth++;
	}
	// temp2(position(1):SIZE(1),position(2):SIZE(2),position(3):SIZE(3))=data;
	for (int j = colStart; j < width; j++) {
		for (int i = rowStart; i < height; i++) {
			if (dim == 1)
			{
				temp2[depth].at<float>(i, j) = img.at<float>(i - 1, j);
			}
			else if (dim == 2)
			{
				temp2[depth].at<float>(i, j) = img.at<float>(i, j - 1);
			}
			else if (dim == 3)
			{
				temp2[depth].at<float>(i, j) = img.at<float>(i, j);
			}
		}
	}

	temp1[depth] = (temp1[depth] - temp2[depth]) / step;
	if (dim == 3)
	{
		temp1[depth - 1] = (temp1[depth - 1] - temp2[depth - 1]) / step;
	}

	if (dim == 1)
	{
		height = height - 1;
	}
	else if (dim == 2)
	{
		width = width - 1;
	}
	else if (dim == 3)
	{
		depth--;
	}

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			out.at<float>(i, j) = temp1[depth].at<float>(i, j);
		}
	}

	// out = temp2[0];
	return out;
}

cv::Mat forwardDiffFunction(cv::Mat img, int step, int dim, const int framesCount)
{



	int width = img.cols;
	int height = img.rows;
	int numberOfFrames = framesCount;
	int cols = width;
	int rows = height;
	int rowStart = 0;
	int colStart = 0;
	int depth = 0;

	if (dim == 1)
	{
		height = height + 1;
		rowStart++;
	}
	else if (dim == 2)
	{
		width = width + 1;
		colStart++;
	}
	else if (dim == 3)
	{
		depth++;
	}

	const int frames = framesCount + 1;
	cv::Mat temp1[2];
	cv::Mat temp2[2];
	cv::Mat out;

	//Initialize the Mat
	temp1[0].convertTo(temp1[0], CV_32F);
	temp1[0] = { cv::Mat::zeros(rows + 1, cols + 1, CV_32F) };

	temp1[1].convertTo(temp1[1], CV_32F);
	temp1[1] = { cv::Mat::zeros(rows + 1, cols + 1, CV_32F) };

	out.convertTo(out, CV_32F);
	out = { cv::Mat::zeros(rows, cols , CV_32F) };

	temp2[0].convertTo(temp2[0], CV_32F);
	temp2[0] = { cv::Mat::zeros(rows + 1, cols + 1, CV_32F) };

	temp2[1].convertTo(temp2[1], CV_32F);
	temp2[1] = { cv::Mat::zeros(rows + 1, cols + 1, CV_32F) };

	// temp1(position(1):SIZE(1),position(2):SIZE(2),position(3):SIZE(3))=data;
	for (int j = colStart; j < width; j++) {
		for (int i = rowStart; i < height; i++) {
			if (dim == 1)
			{
				temp1[depth].at<float>(i, j) = img.at<float>(i - 1, j);
			}
			else if (dim == 2)
			{
				temp1[depth].at<float>(i, j) = img.at<float>(i, j - 1);
			}
			else if (dim == 3)
			{
				temp1[depth].at<float>(i, j) = img.at<float>(i, j);
			}
		}
	}

	// temp2(position(1):SIZE(1),position(2):SIZE(2),position(3):SIZE(3))=data;
	for (int j = colStart; j < width; j++) {
		for (int i = rowStart; i < height; i++) {

			if (dim == 1)
			{
				temp2[depth].at<float>(i, j) = img.at<float>(i - 1, j);
			}
			else if (dim == 2)
			{
				temp2[depth].at<float>(i, j) = img.at<float>(i, j - 1);
			}
			else if (dim == 3)
			{
				temp2[depth].at<float>(i, j) = img.at<float>(i, j);
			}
		}
	}

	if (dim == 1)
	{
		height = height - 1;
		// rowStart++;
	}
	else if (dim == 2)
	{
		width = width - 1;
		//colStart++;
	}
	else if (dim == 3)
	{
		depth--;
	}

	//temp2(1:SIZE(1),1:SIZE(2),1:SIZE(3))=data;
	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			temp2[depth].at<float>(i, j) = img.at<float>(i, j);
		}
	}

	temp1[depth] = (temp1[depth] - temp2[depth]) / step;

	if (dim == 3)
	{
		temp1[depth + 1] = (temp1[depth + 1] - temp2[depth + 1]) / step;
	}

	if (dim == 1)
	{
		height = height + 1;
		// rowStart++;
	}
	else if (dim == 2)
	{
		width = width + 1;
		//colStart++;
	}
	else if (dim == 3)
	{
		depth++;
	}

	// out = temp1(position(1):SIZE(1),position(2):SIZE(2),position(3):SIZE(3)); 
	for (int j = colStart; j < width; j++) {
		for (int i = rowStart; i < height; i++) {

			if (dim == 1)
			{
				out.at<float>(i - 1, j) = temp1[depth].at<float>(i, j);
			}
			else if (dim == 2)
			{
				out.at<float>(i, j - 1) = temp1[depth].at<float>(i, j);
			}
			else if (dim == 3)
			{
				//std::cout << "Depth " << depth << std::endl;
				out.at<float>(i, j) = temp1[depth].at<float>(i, j);
			}
		}
	}

	out = out * (-1);





	//std::cout << "Forward Diff " << img.rows << " " << temp1[0].rows << " " << temp1[0].size()<< " - " << img.size() << std::endl;


	return out;

}

