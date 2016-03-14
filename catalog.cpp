#include "catalog.h"

#include <QDebug>

Catalog::Catalog() : saved(false)
{

}

void Catalog::addItem(MediaItem const &item)
{
  m_catalog.append(item);
}

void Catalog::addItem(QString volume, QString filename, qint64 size)
{
  MediaItem temp;
  QString desc;
  temp.setSize(size);
  temp.setVolume(volume);
  temp.setFilename(filename);
  desc =filename.replace(QChar('_'), QChar(' ')); // Replace underscores
  // with spaces for better looking description.
  desc = getFileName(desc);
  temp.setDescription(desc);
  auto extension = getExtension(filename);
  auto type = getFileType(extension);
  temp.setType(type);
  addItem(temp);

}

void Catalog::addItem(QString volume, QString filename, qint64 size, QString type)
{
  MediaTypes x;
  if (type == QString("Video")) {
      x = MediaTypes::Video;
    } else if (type == QString("Music")) {
      x = MediaTypes::Music;
    } else {
      x = MediaTypes::Other;
    }
  saved = false;

}

void Catalog::addDirectory(const QString volume, const QString directory)
{
  QString filename;
  QFileInfo info;
  QDirIterator dirIterator(directory, QDirIterator::Subdirectories);

  while (dirIterator.hasNext()) {
      dirIterator.next();
      info = dirIterator.fileInfo();
      if (info.isFile() && info.size()) { // Only include files with a size greater than 0;
          filename = dirIterator.fileName();
          auto extension = getExtension(filename);
          auto type = getFileType(extension);
          if (type != MediaTypes::Other) {
              addItem(volume, filename, info.size());
            }
        }
    }

}

const int Catalog::size() const
{
  return m_catalog.size();
}

void Catalog::printCatalog()
{
  QString output;
  QTextStream stream(&output);
  for (auto &i : m_catalog) {

      stream << i << "\n";
    }
  qDebug() << output;
}

QVector<QVector<MediaItem>::iterator> Catalog::search(QString searchTerm)
{
  QVector<QVector<MediaItem>::iterator> results;

  find_all(m_catalog.begin(), m_catalog.end(), std::back_inserter(results),
           [searchTerm] (MediaItem s) { return s.description().contains(searchTerm, Qt::CaseInsensitive);});

  return results;
}

bool Catalog::save(QString const filename) const
{
  QFile file(filename);
  if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
      return false;
    }

  QTextStream out(&file);
  for (MediaItem x : m_catalog) {
      out << x << "\n";
    }
  file.close();
  saved = true;
  return true;
}

bool Catalog::load(QString const filename)
{
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      return false;
    }

  QTextStream in(&file);
  QString temp;
  while (!in.atEnd()) {
      temp = in.readLine();
      QStringList list = temp.split("\t");
      qint64 size = list.at(3).toLongLong();
      addItem(list.at(0), list.at(1), size);
    }
  saved = true;
  return true;
}

bool Catalog::getSaved() const
{
  return saved;
}



