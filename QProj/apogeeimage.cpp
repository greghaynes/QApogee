#include "apogeeimage.h"

#include <QStringBuilder>
#include <QByteArray>
#include <QImageReader>

#include <QFile>
#include <QDebug>

#define PGM_MAGIC_NUM "P5"

ApogeeImage::ApogeeImage()
	: QImage()
{
}

ApogeeImage::~ApogeeImage()
{
}

void ApogeeImage::load8bit(long columns, long rows, const QByteArray &data)
{
	QString header = QString(PGM_MAGIC_NUM) % QString("\n") %
		             QString::number(columns) % " " % QString::number(rows) % QString("\n") %
					 QString("255") % QString("\n");

	QByteArray pgmData = header.toAscii();
	pgmData.append(data);

	QFile outf("image.pgm");
	outf.open(QIODevice::ReadWrite);
	outf.write(pgmData);
	outf.close();

	if(!loadFromData(pgmData, "pgm"))
		qDebug() << "Could not load image from data.";
}

void ApogeeImage::load16bit(long columns, long rows, const QByteArray &data)
{
	long oldSize = columns * rows;
	long newSize = oldSize / 2;

	// Size sanity check
	if(oldSize > data.size())
		return;

	// Convert to 8bit data
	QByteArray newData(newSize, 0);
	const char *oldData = data.data();
	long i, j;
	for(i = 0;i < oldSize;i++)
	{
		short oldPixel = ((const short*)oldData)[i];
		newData[i] = (uchar)(oldPixel >> 8);
	}

	load8bit(columns, rows, newData);
}

void ApogeeImage::doLeveling(qreal threshold)
{
}
