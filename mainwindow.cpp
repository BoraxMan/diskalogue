#include "mainwindow.h"
#include "ui_mainwindow.h"


void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}



MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_watcher(nullptr),
  m_catalog(nullptr)
{
  ui->setupUi(this);
  m_watcher = new DeviceWatcher(this);

  connect(ui->action_New, SIGNAL(triggered(bool)), this, SLOT(newCatalog()));
  connect(ui->action_Close, SIGNAL(triggered(bool)),this, SLOT(close()));
  connect(ui->actionSave_as, SIGNAL(triggered(bool)), this, SLOT(saveAs()));
  connect(ui->action_Save, SIGNAL(triggered(bool)), this, SLOT(save()));
  connect(ui->action_Add_Directory, SIGNAL(triggered(bool)), this, SLOT(addDirectory()));
  connect(ui->action_Open, SIGNAL(triggered(bool)), this, SLOT(open()));

  QTreeWidgetItem *headerItem = new QTreeWidgetItem();
  headerItem->setText(0, "Volume/Description");
  headerItem->setText(1,"Size of file.");
  ui->treeWidget->setHeaderItem(headerItem);
  ui->treeWidget->setColumnWidth(0,384);
}

MainWindow::~MainWindow()
{
  delete m_watcher;
  delete ui;
}

void MainWindow::newCatalog()
{
  m_catalog = new Catalog;
  setEnableGui(true);
}

int MainWindow::close()
{
  if (m_catalog == nullptr) return 0;

  if (m_catalog->getSaved() == false) {
      QMessageBox msgBox;
      msgBox.setWindowTitle("Unsaved changes");
      msgBox.setText("The file has been modified.");
      msgBox.setInformativeText("Do you want to continue and lose changes?");
      msgBox.setStandardButtons(QMessageBox::Close | QMessageBox::Save | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int result = msgBox.exec();
      switch (result) {
        case QMessageBox::Save:
          saveAs();
          break;
        case QMessageBox::Cancel:
          return 1;
          break;
        case QMessageBox::Close:
          break;
        default:
          return 1;
        }
    }
  delete m_catalog;
  m_catalog = nullptr;
  setEnableGui(false);

    while (ui->treeWidget->topLevelItemCount() > 0) {
      ui->treeWidget->takeTopLevelItem(0);
  }
}





void MainWindow::saveAs()
{
  if (m_catalog == nullptr) return;

  QFileDialog fileDialog(this, "Save File As");
  fileDialog.setNameFilter("Catalog File (*.csv)");
  fileDialog.setDefaultSuffix("csv");

  if (fileDialog.exec()) {

      QString fname = fileDialog.selectedFiles().first();
      QString filename = QDir::toNativeSeparators(fname);
      if (!filename.isNull()) {
          m_catalogFileName = filename;
          m_catalog->save(m_catalogFileName);
        } else {
          return;
        }
    }

  return;
}

void MainWindow::addDirectory()
{
  if (m_catalog == nullptr) {
      newCatalog();
     }

  QString path = getSinglePathSelection();
  if (path.isNull()) {
      return;
    }

  m_catalog->addDirectory(path, path);
  m_catalog->printCatalog();
}

void MainWindow::addVolume()
{

}

int MainWindow::open()
{
  QString fname  = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Diskalogue File (*.csv)"));
  QString filename = QDir::toNativeSeparators(fname);

  if (!filename.isNull()) {
      if (m_catalog) {
          close();
        }
    } else {
      return 0;
    }
  newCatalog();
  m_catalog->load(filename);



}

void MainWindow::slotDeviceAdded(const QString &dev)
{
  if (m_catalog == nullptr) {
      newCatalog();
    }

    QStorageInfo x(dev);
    QString path = QDir::toNativeSeparators(dev);
    qDebug() << x.name();
    path.resize(3); // For Windows Only.
    qDebug() << path;
    for (int timer = 10; timer >0; --timer) {
                qDebug() << "time";
        delay();
        if (x.isReady()){
        m_catalog->addDirectory(x.name(), path);
        m_catalog->printCatalog();

        qDebug() << "Added";
        return;
        }
    }

}

void MainWindow::startSearch()
{
  while (ui->treeWidget->topLevelItemCount() > 0) {
    ui->treeWidget->takeTopLevelItem(0);
}

  auto results = m_catalog->search(ui->searchLineEdit->text());
  QSet<QString> volumes;
  for (const auto &i : results) {
      volumes.insert(i->volume());
    }

  for (const auto &i : volumes) {
      QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
      item->setText(0, i);
      item->setExpanded(true);
    }

  for (const auto &i : results) {
      auto parentItems = ui->treeWidget->findItems(i->volume(), Qt::MatchExactly);
      QTreeWidgetItem *item2 = new QTreeWidgetItem(parentItems.first());
      item2->setText(0, i->description());
      item2->setText(1, QString::number(i->size()));
    }
}

void MainWindow::setEnableGui(bool enabled)
{
  ui->treeWidget->setEnabled(enabled);
  ui->searchLineEdit->setEnabled(enabled);
  ui->searchButton->setEnabled(enabled);
}


void MainWindow::aboutQT()
{
  QApplication::aboutQt();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
  if (m_catalog->getSaved() == false) {
      if (close() == -1) {
          event->ignore();
        }
    }
  event->accept();
  delete m_watcher;
  delete ui;
}
