#include <QPainter>
#include <QSvgRenderer>
#include "qrcodegen.hpp"
#include "Qrimageprovider.hpp"
#include <QDebug>

using namespace qrcodegen;

QPixmap QRImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
	const int width = 100;
    QStringList strlist=id.split('/');
    const auto color=strlist.front();
    strlist.removeFirst();
    const auto data=strlist.join('/');
	const auto max=(requestedSize.width()>requestedSize.height())?requestedSize.width():requestedSize.height();

	QPixmap pixmap(max > 0 ? max : width,
			max> 0 ? max : width);
	pixmap.fill( Qt::transparent );
	*size = pixmap.size();
    const QrCode qr = QrCode::encodeText(data.toStdString().c_str(), static_cast<QrCode::Ecc>(errC));
    const auto qrSVGstr=toSvgString(qr, color.toStdString());

	auto qrImage=QSvgRenderer(QByteArray::fromStdString(qrSVGstr));
	QPainter Painter;

	Painter.begin(&pixmap);
	qrImage.render(&Painter);
	Painter.end();
	return pixmap;
}

