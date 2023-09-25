#pragma once
#include<opencv2/opencv.hpp>
#include<string>

class MyQRCodeDetector : public cv::QRCodeDetector
{

public:
    MyQRCodeDetector(){};
    std::string decode_grey(unsigned char* img, int rows,int cols);
};

