#include<QObject>
#include<QString>
#include <QtQml>
class QRImageDecoder : public QObject
{
	Q_OBJECT
		Q_PROPERTY(QString text READ get_text NOTIFY text_changed)
        Q_PROPERTY(QString source READ get_source WRITE set_source NOTIFY source_changed)
		QML_ELEMENT
		QML_SINGLETON

	public:
    QRImageDecoder()=default;
		QString get_text(void)
		{
			return text;
		}
        QString get_source(void)
        {
            return source;
        }

        void set_source(const QString &file );
signals:
		void text_changed();
		void source_changed();
	private:
        QString text,source;
};



