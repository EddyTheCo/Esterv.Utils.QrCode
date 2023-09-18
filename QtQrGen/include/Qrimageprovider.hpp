#include <qquickimageprovider.h>


//foo namespace to force the linker to link the backing library composed only of qml files
namespace fooQtQrGen
{
QString fooPrint(void);
};

class QRImageProvider : public QQuickImageProvider
{
public:
    QRImageProvider(QColor col="black",int erc=0)
        : QQuickImageProvider(QQuickImageProvider::Pixmap),color(col),errC(erc)
    {

    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
private:
    const QColor color;
    const int errC;
};



