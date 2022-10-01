#ifndef DATABASEEDITOR_H
#define DATABASEEDITOR_H

#include <QMainWindow>

#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DatabaseEditor; }
QT_END_NAMESPACE

class DatabaseEditor : public QMainWindow
{
  Q_OBJECT

public:
  DatabaseEditor(QWidget *parent = nullptr);
  ~DatabaseEditor();

private slots:
  void on_bttnOpenDatabase_clicked();

  void on_bttnCreateDatabase_clicked();

private:
  Ui::DatabaseEditor *ui;
  Database *database;
};
#endif // DATABASEEDITOR_H
