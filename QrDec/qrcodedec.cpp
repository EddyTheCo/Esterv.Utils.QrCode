#include<qrcodedec.hpp>

std::string QRDecoder::decode_grey(unsigned char* img,int rows ,int cols)
{
    cv::Mat greyImg = cv::Mat(rows,cols, CV_8UC1, img);
    return detectAndDecode(greyImg);
}



