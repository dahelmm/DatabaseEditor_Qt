#ifndef DATABASEEDITOR_H
#define DATABASEEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DatabaseEditor; }
QT_END_NAMESPACE

class DatabaseEditor : public QMainWindow
{
  Q_OBJECT

public:
  DatabaseEditor(QWidget *parent = nullptr);
  ~DatabaseEditor();

private:
  Ui::DatabaseEditor *ui;
};
#endif // DATABASEEDITOR_H
