#include "func.h"

QMap<QString, MediaTypes>& extensionMap()
{
  static QMap<QString, MediaTypes> qmap;
  return qmap;
}


QString getExtension(QString filename)
{
  QFileInfo f(filename);
  return f.suffix();
}

MediaTypes getFileType(QString extension)
{
  return extensionMap().value(extension, MediaTypes::Other);
}

QString getFileName(const QString &x)
{
  QFileInfo f(x);
  return f.completeBaseName();
}

QString getSinglePathSelection()
{
  QFileDialog fileDialog;
  fileDialog.setFileMode(QFileDialog::Directory);
  fileDialog.setViewMode(QFileDialog::Detail);
  fileDialog.setOption(QFileDialog::ShowDirsOnly, true);
  fileDialog.setOption(QFileDialog::DontUseNativeDialog, true);

  QStringList files;
  if (fileDialog.exec()) {
      files = fileDialog.selectedFiles();
    }
  if (files.empty()) {
      QMessageBox(QMessageBox::Warning, QString("No selection"), QString("No output folder selected."),QMessageBox::Close).exec();
      return QString();
    }

  QString path = QDir::toNativeSeparators(files.at(0));
  return path;
}
