#ifndef APOGEEIMAGE_H
#define APOGEEIMAGE_H

#include <QImage>
#include <QByteArray>

class ApogeeImage : public QImage
{
public:
	ApogeeImage();
	~ApogeeImage();

	void load8bit(long columns, long rows, const QByteArray &data);
	void load16bit(long columns, long rows, const QByteArray &data);
	void doLeveling(qreal threshold);

};

#endif // APOGEEIMAGE_H
