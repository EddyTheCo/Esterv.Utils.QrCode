#include"qrcodedec.hpp"
#include <opencv2/opencv.hpp>
#undef NDEBUG
#include <assert.h>

using namespace qrcodedec;

using namespace cv;

int main(int argc, char** argv)
{
	Mat img = imread(argv[1]);
	Mat gray;

	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

	assert(decode_grey(gray.data,gray.rows,gray.cols)=="http://LearnOpenCV.com");

	return 0;

}
