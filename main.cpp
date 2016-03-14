#include "mainwindow.h"
#include <QApplication>
#include <QMap>

#include "mediatypes.h"
#include "func.h"
#include "devicewatcher.h"
#include "testunit.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  extensionMap().insert("avi", MediaTypes::Video);
  extensionMap().insert("mpg", MediaTypes::Video);
  extensionMap().insert("ogv", MediaTypes::Video);
  extensionMap().insert("mkv", MediaTypes::Video);
  extensionMap().insert("flv", MediaTypes::Video);
  extensionMap().insert("webm", MediaTypes::Video);
  extensionMap().insert("wmv", MediaTypes::Video);
  extensionMap().insert("mp3", MediaTypes::Music);
  extensionMap().insert("ogg", MediaTypes::Music);
  extensionMap().insert("wma", MediaTypes::Video);
  extensionMap().insert("wav", MediaTypes::Music);
  extensionMap().insert("mod", MediaTypes::Music);
  extensionMap().insert("mid", MediaTypes::Music);
  extensionMap().insert("mp4", MediaTypes::Video);

  MainWindow w;
  w.show();
  testunit();
  //return 0;
  return a.exec();
}
