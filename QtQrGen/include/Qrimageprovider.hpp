#include <qquickimageprovider.h>

#include <QtCore/QtGlobal>
#if defined(WINDOWS_GEN)
# define GEN_EXPORT Q_DECL_EXPORT
#else
#define GEN_EXPORT Q_DECL_IMPORT
#endif

class GEN_EXPORT QRImageProvider : public QQuickImageProvider
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



