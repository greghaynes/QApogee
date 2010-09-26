#include "qproj.h"

#include <QErrorMessage>

QProj::QProj(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	, cam_discovered(false)
{
	ui.setupUi(this);

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