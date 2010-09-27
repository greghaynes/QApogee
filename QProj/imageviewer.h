#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "apogeeimage.h"

#include <QWidget>
#include <QString>

#include "ui_imageviewer.h"

class ImageViewer : public QWidget
{
	Q_OBJECT

public:
	ImageViewer(QWidget *parent = 0);
	~ImageViewer();

	void setText(const QString &text);
	void setImage(const ApogeeImage &img);

private Q_SLOTS:
	void imageChanged();

private:
	void drawImage();

	Ui::ImageViewer ui;
	const ApogeeImage *m_image;
};

#endif // IMGVIEW_H
