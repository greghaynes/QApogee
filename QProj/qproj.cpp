#include "qproj.h"
#include "apogeeimage.h"
#include "imageviewer.h"

#include <QErrorMessage>
#include <QFileDialog>
#include <QFile>
#include <QDebug>

QProj::QProj(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	, cam_discovered(false)
{
	ui.setupUi(this);

	// Connect actions
	connect(ui.actionOpenImage, SIGNAL(triggered(bool)),
		    this, SLOT(viewImage()));

	// Instantiate Camera
	// TODO: This should be a recoverable error
	HRESULT hr = ApogeeCamera.CreateInstance(__uuidof( Camera2 ));
	if(!SUCCEEDED(hr))
	{
		setEnabled(false);
		showError(tr("Could not create camera instance."));
	}
}

QProj::~QProj()
{
	ApogeeCamera = NULL;
}

void QProj::discoverCamera()
{
	HRESULT hr;
	ICamDiscoverPtr Discover;

	// Create Discover dialog
	hr = Discover.CreateInstance(__uuidof( CamDiscover ));
	if(!SUCCEEDED(hr))
	{
		showError(tr("Could not create camera discover dialog."));
		return;
	}

	// Set dialog checkboxes
	Discover->DlgCheckEthernet = false;
	Discover->DlgCheckUsb = true;

	Discover->ShowDialog(true);
	
	// Check if a selection was made
	if(!Discover->ValidSelection)
		return;

	// Initialize camera to one selected in dialog
	hr = ApogeeCamera->Init(Discover->SelectedInterface,
	                        Discover->SelectedCamIdOne,
                            Discover->SelectedCamIdTwo,
							0x0);

	// TODO: Allow camera to be re-initialized
	ui.actionSelectCamera->setEnabled(false);

	if(!SUCCEEDED(hr))
		showError(tr("Could not connect to selected camera"));
}

void QProj::showError(const QString &err_msg)
{
	QErrorMessage e;
	e.showMessage(err_msg);
	e.exec();
}

void QProj::showCameraInfo()
{
}

void QProj::viewImage()
{
	QFileDialog *fd = new QFileDialog(this);;
	connect(fd, SIGNAL(fileSelected(const QString&)),
	        this, SLOT(viewImage(const QString&)));
	fd->show();
}

void QProj::viewImage(const QString &filename)
{
	qDebug() << "Opening image " << filename;

	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	QByteArray byte_arr = file.readAll();
	file.close();

	ApogeeImage img;
	img.load16BitRaw(256, 256, byte_arr);

	ImageViewer *view = new ImageViewer();
	view->setImage(img);
	view->show();
}