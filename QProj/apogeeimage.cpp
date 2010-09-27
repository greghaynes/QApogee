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

void ApogeeImage::load8BitRaw(long columns, long rows, QByteArray &data)
{
	QString header = QString(PGM_MAGIC_NUM) % QString("\n") %
		             QString::number(columns) % " " % QString::number(rows) % QString("\n") %
					 QString("255\n");

	QByteArray pgmData = header.toAscii();

	scale8Bit(data);
	pgmData.append(data);

	if(!loadFromData(pgmData, "pgm"))
		qDebug() << "Could not load image from data.";
	else
		emit(changed());
}

void ApogeeImage::load16BitRaw(long columns, long rows, QByteArray &data)
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
		newData[i] = (unsigned char)(oldPixel >> 8);
	}

	load8BitRaw(columns, rows, newData);
}

// Find extreme values and rescale values in data to
// fit range 0-255
void ApogeeImage::scale8Bit(QByteArray &data)
{
	unsigned char min = 255, max = 0;

	long i = 0,
		 size = data.size();
	for(i = 0;i < size;i++)
	{
		unsigned char val = data[i];
		if(val < min)
			min = val;
		if(val > max)
			max = val;
	}

	double scaleF;
	unsigned char valRange = max - min;
	if(!valRange)
		scaleF = 1;
	else
		scaleF = 255 / valRange;
	for(i = 0;i < size;i++)
	{
		unsigned char newVal = (data[i] - min) * scaleF;
		data[i] = newVal;
	}
}
