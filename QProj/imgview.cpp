#include "imgview.h"

ImgView::ImgView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setText(tr("No image loaded."));
}

ImgView::~ImgView()
{
}

void ImgView::setText(const QString &label)
{
	ui.img->setText(label);
}

void ImgView::setImg(const QPixmap &pixmap)
{
	ui.img->setPixmap(pixmap);
}
