#ifndef MEDIAITEM_H
#define MEDIAITEM_H
#include <QString>
#include <QtGlobal>
#include <ostream>
#include <QTextStream>
#include "mediatypes.h"
class MediaItem
{
public:
  MediaItem();
  QString description() const;
  void setDescription(const QString description);

  QString filename() const;
  void setFilename(const QString filename);

  QString volume() const;
  void setVolume(const QString volume);

  qint64 size() const;
  void setSize(const qint64 size);

  MediaTypes getType() const;
  void setType(const MediaTypes &value);
  friend QTextStream &operator<<(QTextStream &outstream, MediaItem & p);

private:
  QString m_volume;
  QString m_filename;
  QString m_description;
  qint64 m_size;
  MediaTypes m_type;


};

#endif // MEDIAITEM_H
