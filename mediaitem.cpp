#include "mediaitem.h"

MediaItem::MediaItem()
{

}

QTextStream &operator<<(QTextStream &outstream, MediaItem &p)
{
  outstream << p.m_volume.toStdString().c_str() << "\t";
  outstream << p.m_filename.toStdString().c_str() << "\t";
  outstream << p.m_description.toStdString().c_str() << "\t";
  outstream << p.m_size << "\t";
  if (p.m_type == MediaTypes::Video) {
      outstream << "Video";
    } else if (p.m_type == MediaTypes::Music ){
      outstream << "Music";
    } else {
      outstream << "Other";
    }

  return outstream;
}

QString MediaItem::description() const
{
  return m_description;
}

void MediaItem::setDescription(const QString description)
{
  m_description = description;
}

QString MediaItem::filename() const
{
  return m_filename;
}

void MediaItem::setFilename(const QString filename)
{
  m_filename = filename;
}

QString MediaItem::volume() const
{
  return m_volume;
}

void MediaItem::setVolume(const QString volume)
{
  m_volume = volume;
}

qint64 MediaItem::size() const
{
  return m_size;
}

void MediaItem::setSize(const qint64 size)
{
  m_size = size;
}

MediaTypes MediaItem::getType() const
{
  return m_type;
}

void MediaItem::setType(const MediaTypes &value)
{
  m_type = value;
}

