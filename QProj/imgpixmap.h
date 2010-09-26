#ifndef IMGPIXMAP_H
#define IMGPIXMAP_H

#include <QPixmap>
#include <QByteArray>

class ImgPixmap : public QPixmap
{
public:
	ImgPixmap();
	~ImgPixmap();

	void load16bit(long columns, long rows, const QByteArray &data);

private:
	
};

#endif // IMGPIXMAP_H
