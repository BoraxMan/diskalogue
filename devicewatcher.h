#ifndef DEVICEWATCHER_H
#define DEVICEWATCHER_H
#include <QtCore/QObject>
#include <QtCore/QThread>
#include "qdevicewatcher.h"

class DeviceWatcher : public QThread
{
  Q_OBJECT
private:
QDeviceWatcher *watcher;

public:
  ~DeviceWatcher() { watcher->stop(); delete watcher;}
  DeviceWatcher(QObject *parent =0): QThread(parent) {
    start();
    moveToThread(this);
    watcher = new QDeviceWatcher;
    watcher->moveToThread(this);
    watcher->appendEventReceiver(this);
    connect(watcher, SIGNAL(deviceAdded(QString)), parent, SLOT(slotDeviceAdded(QString)), Qt::DirectConnection);
   // connect(watcher, SIGNAL(deviceChanged(QString)), this, SLOT(slotDeviceChanged(QString)), Qt::DirectConnection);
   // connect(watcher, SIGNAL(deviceRemoved(QString)), this, SLOT(slotDeviceRemoved(QString)), Qt::DirectConnection);
    watcher->start();

  }
public slots:
    void slotDeviceAdded(const QString& dev) { qDebug("tid=%#x %s: add %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));}
    //void slotDeviceRemoved(const QString& dev) { qDebug("tid=%#x %s: remove %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));}
    //void slotDeviceChanged(const QString& dev) { qDebug("tid=%#x %s: change %s", (quintptr)QThread::currentThreadId(), __PRETTY_FUNCTION__, qPrintable(dev));}
protected:
	virtual bool event(QEvent *e) {
		if (e->type() == QDeviceChangeEvent::registeredType()) {
			QDeviceChangeEvent *event = (QDeviceChangeEvent*)e;
			QString action("Change");
			if (event->action() == QDeviceChangeEvent::Add)
				action = "Add";
			else if (event->action() == QDeviceChangeEvent::Remove)
				action = "Remove";

	    qDebug("tid=%#x event=%d %s: %s %s", (quintptr)QThread::currentThreadId(), e->type(), __PRETTY_FUNCTION__, qPrintable(action), qPrintable(event->device()));
			event->accept();
			return true;
		}
		return QObject::event(e);
	}
};

#endif // DEVICEWATCHER_H
