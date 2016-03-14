#include "testunit.h"
#include "catalog.h"
#include "mediaitem.h"
#include "mediatypes.h"
#include <QString>
#include <QDebug>
#include <QList>


void testunit()
{
  Catalog catalog;
  catalog.addItem(QString("FAMILY_MOVIES"), QString("mary_poppins.avi"), 54404443);
  catalog.addItem(QString("HORROR"), QString("wizards manse.mkv"), 439011439191);
  catalog.addItem(QString("FAMILY_MOVIES"), QString("The_Wizard_Of_Oz.mkv"), 4390119191);
  catalog.printCatalog();

  auto x = catalog.search(QString("wiz"));
  qDebug() << x.size();
  for (auto i : x) {
      qDebug() << i->description();
    }
  catalog.save(QString("test.csv"));
  Catalog dx;
  dx.load(QString("test.csv"));
  dx.addDirectory("VOLUME2", "/home/dennisk/program");
  dx.printCatalog();
  dx.save(QString("test2.csv"));
}
