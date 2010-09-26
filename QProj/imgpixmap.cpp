#include "imgpixmap.h"

#include <QStringBuilder>
#include <QByteArray>

#define PGM_MAGIC_NUM "P5"

ImgPixmap::ImgPixmap()
	: QPixmap()
{
}

ImgPixmap::~ImgPixmap()
{
}

void ImgPixmap::load16bit(long columns, long rows, const QByteArray &data)
{
	QString header = QString(PGM_MAGIC_NUM) % QString("\n") %
		             QString::number(columns) % " " % QString::number(rows) % QString("\n") %
					 QString("65536") % QString("\n");

	QByteArray pgmData = header.toAscii().append(data);

	loadFromData(pgmData, "PGM");
}
