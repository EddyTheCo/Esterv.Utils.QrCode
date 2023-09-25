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

        }
    }
    if(corners.rows&&corners.cols)
    {
        cv::line(greyImg, cv::Point2i(corners.at<float>(0,0),corners.at<float>(0,1)), cv::Point2i(corners.at<float>(0,2),corners.at<float>(0,1)), cv::Scalar(100,200,155), 11);
        cv::line(greyImg, cv::Point2i(corners.at<float>(0,2),corners.at<float>(0,1)),cv::Point2i(corners.at<float>(0,2),corners.at<float>(0,3)), cv::Scalar(30,100,0), 8);
        cv::line(greyImg, cv::Point2i(corners.at<float>(0,0),corners.at<float>(0,1)), cv::Point2i(corners.at<float>(0,0),corners.at<float>(0,3)), cv::Scalar(150,4,255), 5);
        cv::line(greyImg, cv::Point2i(corners.at<float>(0,0),corners.at<float>(0,3)),cv::Point2i(corners.at<float>(0,2),corners.at<float>(0,3)), cv::Scalar(75,75,75), 2);
    }
    return str;
}



