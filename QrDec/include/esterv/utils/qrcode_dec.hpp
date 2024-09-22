#pragma once
#include <opencv2/objdetect.hpp>
#include<string>

namespace Esterv::Utils::QrDec
{
class QRDecoder : public cv::QRCodeDetectorAruco
{

public:
    QRDecoder(){};
    std::string decode_grey(unsigned char* img, int rows,int cols);
};
}
