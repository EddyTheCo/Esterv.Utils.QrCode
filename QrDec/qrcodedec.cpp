#include<qrcodedec.hpp>
#include<opencv2/opencv.hpp>



namespace qrcodedec {
	using namespace std;
	using namespace cv;
    string decode_grey(unsigned char* img,int rows ,int cols)
	{
        Mat greyImg = cv::Mat(rows,cols, CV_8UC1, img);

        QRCodeDetector decoder = QRCodeDetector();
        return decoder.detectAndDecode(greyImg);
	}


}

