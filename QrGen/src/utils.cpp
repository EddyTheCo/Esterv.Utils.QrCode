#include "esterv/utils/qrcode_gen.hpp"
namespace Esterv::Utils::QrGen {

    std::string toSvgString(const QrCode &qr, std::string fill) {


		std::ostringstream sb;
		sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
		sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
        sb << (qr.getSize() ) << " " << (qr.getSize() ) << "\" stroke=\"none\">\n";
		sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"none\"/>\n";
		sb << "\t<path d=\"";
		for (int y = 0; y < qr.getSize(); y++) {
			for (int x = 0; x < qr.getSize(); x++) {
				if (qr.getModule(x, y)) {
					if (x != 0 || y != 0)
						sb << " ";
                    sb << "M" << (x) << "," << (y) << "h1v1h-1z";
				}
			}
		}
		sb << "\" fill=\""<<fill<<"\"/>\n";
		sb << "</svg>\n";
		return sb.str();
	}
}
