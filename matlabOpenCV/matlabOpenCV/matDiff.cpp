#include "matDiff.h"

matDiff::matDiff()
{
}

cv::Mat matDiff::forwardDiffFunction(cv::Mat img, int step, int dim, const int framesCount)
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
                temp1[depth].at<float>(i, j) = img.at<float>(i - 1, j, 0);
            }
            else if (dim == 2)
            {
                temp1[depth].at<float>(i, j) = img.at<float>(i, j - 1, 0);
            }
            else if (dim == 3)
            {
                temp1[depth].at<float>(i, j) = img.at<float>(i, j, 0);
            }
        }
    }

    // temp2(position(1):SIZE(1),position(2):SIZE(2),position(3):SIZE(3))=data;
    for (int j = colStart; j < width; j++) {
        for (int i = rowStart; i < height; i++) {

            if (dim == 1)
            {
                temp2[depth].at<float>(i, j) = img.at<float>(i - 1, j, 0);
            }
            else if (dim == 2)
            {
                temp2[depth].at<float>(i, j) = img.at<float>(i, j - 1, 0);
            }
            else if (dim == 3)
            {
                temp2[depth].at<float>(i, j) = img.at<float>(i, j, 0);
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
            temp2[depth].at<float>(i, j) = img.at<float>(i, j, 0);
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

