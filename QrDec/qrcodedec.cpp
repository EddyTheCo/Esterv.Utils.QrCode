#include<qrcodedec.hpp>
#include <QDebug>
std::string MyQRCodeDetector::decode_grey(unsigned char* img,int rows ,int cols)
{
    cv::Mat greyImg = cv::Mat(rows,cols, CV_8UC1, img);

    cv::Mat corners;
    auto str=detectAndDecode(greyImg,corners);

    qDebug()<<"cols:"<<corners.cols;
    qDebug()<<"rows:"<<corners.rows;

    for(int i = 0 ; i < corners.rows ; i++)
    {
        for(int j = 0 ; j < corners.cols ; j++)
        {
            qDebug()<<corners.at<float>(i,j);
            cv::line(greyImg, cv::Point2i(corners.at<float>(i,j)), cv::Point2i(corners.at<float>(i,j+1)), cv::Scalar(100,200,155), 10);
        }

    }
    return str;
}



