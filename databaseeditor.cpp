#include "databaseeditor.h"
#include "ui_databaseeditor.h"

#include <QFileDialog>

DatabaseEditor::DatabaseEditor(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::DatabaseEditor)
  , database(nullptr)
{
    ui->setupUi(this);
    database = new Database(this);
}

DatabaseEditor::~DatabaseEditor()
{
  delete ui;
}


void DatabaseEditor::on_bttnOpenDatabase_clicked()
{
    const QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите файл БД"), QString(), tr("*.db"));
    if(filePath.isEmpty())
        return;
    database->openDatabase(filePath);
}

void DatabaseEditor::on_bttnCreateDatabase_clicked()
{
    const QString filePath = QFileDialog::getSaveFileName(this, tr("Место сохранения БД"), QString(), tr("Database Files (*.db)"),0);
    if(filePath.isEmpty())
        return;
    database->createDatabase(filePath);
}
