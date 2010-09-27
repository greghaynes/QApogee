#ifndef QPROJ_H
#define QPROJ_H

#include <QtGui/QMainWindow>
#include "ui_qproj.h"

#import "Apogee.DLL" no_namespace

class QProj : public QMainWindow
{
	Q_OBJECT

public:
	QProj(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QProj();

public Q_SLOTS:
	void discoverCamera();

private Q_SLOTS:
	void showCameraInfo();
	void viewImage();
	void viewImage(const QString &filename);

private:
	void showError(const QString &err_msg);
	void setCamDiscovered(bool val);

	bool cam_discovered;
	Ui::QProjClass ui;
	ICamera2Ptr ApogeeCamera; // Camera interface
};

#endif // QPROJ_H
