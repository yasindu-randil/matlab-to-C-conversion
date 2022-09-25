#include "matDifferentiate.h"

matDifferentiate::matDifferentiate(std::string readPath, std::string writePath):
	matStack(readPath, writePath)
{
	std::cout << "Inside Mat Differentiate Constructor" << std::endl;
	imgS = getInitialMatVector();
	printImageMat( writePath, imgS[179]);
}
