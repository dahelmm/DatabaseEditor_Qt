#include "databaseeditor.h"
#include "ui_databaseeditor.h"

DatabaseEditor::DatabaseEditor(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::DatabaseEditor)
{
  ui->setupUi(this);
}

DatabaseEditor::~DatabaseEditor()
{
  delete ui;
}

