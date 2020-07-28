#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QSet>
#include <QTime>
#include <QEvent>
#include <QFormLayout>
#include <QCloseEvent>
#include <QStorageInfo>

#include "devicewatcher.h"
#include "catalog.h"

namespace Ui {
  class MainWindow;
}

class AddingDirDialog: public QDialog
{
  Q_OBJECT
public:
  explicit AddingDirDialog(QWidget *parent = 0);
private:
  QDialog *addingDir;
  QFormLayout *layout;
  QLabel *label;
public:
  void setText(QString text);

};

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  DeviceWatcher *m_watcher;
  Catalog *m_catalog;
  void setEnableGui(bool enabled);
  QString m_catalogFileName;

  void aboutQT();
private slots:
  void newCatalog(void);
  int close(void);
  void saveAs(void);
  void addDirectory();
  void addVolume();
  int open();

public slots:
  void slotDeviceAdded(const QString &dev);
  void startSearch(void);

protected:
  void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
