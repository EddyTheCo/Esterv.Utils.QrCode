#include<qrcodedec.hpp>
#include<opencv2/opencv.hpp>

namespace qrcodedec {
    using namespace std;
    using namespace cv;
    string decode_grey(unsigned char* img,int rows ,int cols)
	{
        Mat greyImg = Mat(rows,cols, CV_8UC1, img);
        std::cout<<greyImg<<std::endl;
        QRCodeDetector* decoder = new QRCodeDetector();
        auto str=decoder->detectAndDecode(greyImg);
        delete decoder;
        return str;
	}


}
#ifdef USE_EMSCRIPTEN
EMSCRIPTEN_BINDINGS(qrcodedec) {
        function("decode_grey", &qrcodedec::decode_grey);
}
#endif
