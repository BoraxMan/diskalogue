#ifndef FUNC_H
#define FUNC_H
#include <QMap>
#include <QString>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include "mediatypes.h"

QMap<QString, MediaTypes>& extensionMap();
QString getExtension(QString filename);
MediaTypes getFileType(QString extension);
QString getFileName(const QString &x);
QString getSinglePathSelection();

template <typename InputIterator, typename OutputIterator, typename Predicate>
OutputIterator find_all(InputIterator first, InputIterator last, OutputIterator dest, Predicate pred)
{
  while (first != last) {
      if (pred(*first)) {
          *dest = first;
          ++dest;
        }
      ++first;
     }
  return dest;
}

#endif // FUNC_H
