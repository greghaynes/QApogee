#ifndef APOGEEIMAGE_H
#define APOGEEIMAGE_H

#include <QImage>
#include <QByteArray>

class ApogeeImage : public QObject, public QImage
{
	Q_OBJECT

public:
	ApogeeImage();
	~ApogeeImage();

	void load8BitRaw(long columns, long rows, QByteArray &data);
	void load16BitRaw(long columns, long rows, QByteArray &data);

Q_SIGNALS:
	void changed();

private:
	void scale8Bit(QByteArray &data);

};

#endif // APOGEEIMAGE_H
