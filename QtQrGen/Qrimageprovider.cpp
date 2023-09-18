#include <QPainter>
#include <QSvgRenderer>
#include "qrcodegen.hpp"
#include "Qrimageprovider.hpp"
#include <QDebug>

namespace fooQtQrGen
{
QString fooPrint(void)
{
    return "fooPrint";
}
}
using namespace qrcodegen;

QPixmap QRImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
	const int width = 100;

	const auto max=(requestedSize.width()>requestedSize.height())?requestedSize.width():requestedSize.height();

	QPixmap pixmap(max > 0 ? max : width,
			max> 0 ? max : width);
	pixmap.fill( Qt::transparent );
	*size = pixmap.size();
	const QrCode qr = QrCode::encodeText(id.toStdString().c_str(), static_cast<QrCode::Ecc>(errC));
	const auto qrSVGstr=toSvgString(qr, color.name().toStdString());

	auto qrImage=QSvgRenderer(QByteArray::fromStdString(qrSVGstr));
	QPainter Painter;

	Painter.begin(&pixmap);
	qrImage.render(&Painter);
	Painter.end();
	return pixmap;
}

