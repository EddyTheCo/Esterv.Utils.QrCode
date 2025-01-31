#include <esterv/utils/qrcode_dec.hpp>

namespace Esterv::Utils::QrDec {

std::string QRDecoder::decode_grey(unsigned char *img, int rows, int cols) {
  cv::Mat greyImg = cv::Mat(rows, cols, CV_8UC1, img);
  const auto str = detectAndDecode(greyImg);
  if (str != "")
    return str;
  cv::bitwise_not(greyImg, greyImg);

  return detectAndDecode(greyImg);
}

} // namespace Esterv::Utils::QrDec
