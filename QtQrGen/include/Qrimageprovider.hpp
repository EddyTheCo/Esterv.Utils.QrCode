#include <qquickimageprovider.h>


class QRImageProvider : public QQuickImageProvider
{
public:
    QRImageProvider(int erc=0)
        : QQuickImageProvider(QQuickImageProvider::Pixmap),errC(erc)
    {

    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
private:
    const int errC;
};



