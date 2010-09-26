#ifndef CAMDISCOVER_H
#define CAMDISCOVER_H

#include <QThread>

class CamDiscover
{
	Q_OBJECT

public:
	CamDiscover(QObject *parent);
	~CamDiscover();

Q_SIGNALS:
	void success();
	void failure();

public Q_SLOTS:
	bool dialogDiscover();

private:
	
};

#endif // CAMDISCOVER_H
