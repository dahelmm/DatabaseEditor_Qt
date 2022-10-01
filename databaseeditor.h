#ifndef DATABASEEDITOR_H
#define DATABASEEDITOR_H

#include <QMainWindow>
#include <QSqlTableModel>

#include "database.h"
#include "sqledit.h"

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

  void on_tabWgtDisplayDataDatabase_currentChanged(int index);

  void on_cmbBoxTablesDatabaseOnDisplay_currentIndexChanged(const QString &arg1);

  void on_bttnAddRow_clicked();

  void on_bttnRemoveRow_clicked();

private:
  Ui::DatabaseEditor *ui;
  Database *database;
  QSqlTableModel *m_model;
  SQLEdit *query;
};
#endif // DATABASEEDITOR_H
