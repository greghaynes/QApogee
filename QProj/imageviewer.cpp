#include "imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("Image Viewer"));
	setText(tr("No image loaded."));
}

ImageViewer::~ImageViewer()
{
}

void ImageViewer::setText(const QString &label)
{
	ui.img->setText(label);
}

void ImageViewer::setImage(const ApogeeImage &img)
{
	connect(&img, SIGNAL(changed()),
		    this, SLOT(imageChanged()));
	m_image = &img;

	drawImage();
}

void ImageViewer::imageChanged()
{
	drawImage();
}

void ImageViewer::drawImage()
{
	QPixmap pixmap = QPixmap::fromImage(*m_image);
	if(!pixmap.isNull())
		ui.img->setPixmap(pixmap);
	else
		ui.img->setText(tr("Invalid image."));
}
