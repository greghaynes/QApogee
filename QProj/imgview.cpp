#include "imgview.h"

ImgView::ImgView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("Image Viewer"));
	setText(tr("No image loaded."));
}

ImgView::~ImgView()
{
}

void ImgView::setText(const QString &label)
{
	ui.img->setText(label);
}

void ImgView::setImg(const ApogeeImage &img)
{
	QPixmap pixmap = QPixmap::fromImage(img);
	if(!pixmap.isNull())
		ui.img->setPixmap(pixmap);
	else
		ui.img->setText(tr("Invalid image."));
}
