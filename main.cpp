#include "databaseeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  DatabaseEditor w;
  w.show();
  return a.exec();
}
