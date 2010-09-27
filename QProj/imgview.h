#ifndef IMGVIEW_H
#define IMGVIEW_H

#include "apogeeimage.h"

#include <QWidget>
#include <QString>

#include "ui_imgview.h"

class ImgView : public QWidget
{
	Q_OBJECT

public:
	ImgView(QWidget *parent = 0);
	~ImgView();

	void setText(const QString &text);
	void setImg(const ApogeeImage &img);

private:
	Ui::ImgViewClass ui;
};

#endif // IMGVIEW_H
