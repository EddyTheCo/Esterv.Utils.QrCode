#pragma once
#include<opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include<string>

class QRDecoder : public cv::QRCodeDetector
{

public:
    QRDecoder(){};
    std::string decode_grey(unsigned char* img, int rows,int cols);
};

