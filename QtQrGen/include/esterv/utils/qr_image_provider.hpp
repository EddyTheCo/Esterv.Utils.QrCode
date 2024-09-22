#include <qquickimageprovider.h>


#if defined(QTQRGEN_SHARED)
#include <QtCore/QtGlobal>
  #ifdef WINDOWS_EXPORT
    #define GEN_EXPORT Q_DECL_EXPORT
  #else
    #define GEN_EXPORT Q_DECL_IMPORT
  #endif
#else
  #define GEN_EXPORT
#endif

namespace Esterv::Utils::QrGen {

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


}
