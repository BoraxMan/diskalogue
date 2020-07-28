#ifndef CATALOG_H
#define CATALOG_H

#include <QVector>
#include <QString>
#include <QtGlobal>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <algorithm>
#include <QDirIterator>
#include <QDir>
#include "mediaitem.h"
#include "func.h"
#include "mediatypes.h"

class Catalog
{
public:
  Catalog();
  void addItem(MediaItem const &item);
  void addItem(QString volume, QString filename, qint64 size);
  void addItem(QString volume, QString filename, qint64 size, QString type);
  void addDirectory(QString const volume, QString const directory);
  const int size(void) const;
  void printCatalog(void); // debugging purposes only!
  QVector<QVector<MediaItem>::iterator> search(QString searchTerm);
  bool save(QString const filename) const ;
  bool load(QString const filename);
  bool getSaved() const;

private:
  QVector<MediaItem> m_catalog;
  mutable bool saved;
};

#endif // CATALOG_H
