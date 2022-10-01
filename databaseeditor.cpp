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
    m_model = new QSqlTableModel(this);
    ui->tableViewDisplayTable->setModel(m_model);

    // Sql query
    query = new SQLEdit(ui->editorSQL);
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
    QStringList tables = database->readTablesDatabase();
    if(!tables.isEmpty())
    {
        foreach(auto item, tables)
        {
            ui->cmbBoxTablesDatabaseOnDisplay->addItem(item);
            ui->cmbBoxTablesDatabase->addItem(item);
        }
    }
}

void DatabaseEditor::on_bttnCreateDatabase_clicked()
{
    const QString filePath = QFileDialog::getSaveFileName(this, tr("Место сохранения БД"), QString(), tr("Database Files (*.db)"),0);
    if(filePath.isEmpty())
        return;
    database->createDatabase(filePath);

}

void DatabaseEditor::on_tabWgtDisplayDataDatabase_currentChanged(int index)
{
    if(index == 1)
    {
        m_model->setTable(ui->cmbBoxTablesDatabase->currentText());
        m_model->select();
    }
}

void DatabaseEditor::on_cmbBoxTablesDatabaseOnDisplay_currentIndexChanged(const QString &table)
{
    ui->cmbBoxTablesDatabase->setCurrentText(table);
    m_model->setTable(table);
    m_model->select();
}

void DatabaseEditor::on_bttnAddRow_clicked()
{
    m_model->insertRow(m_model->rowCount());
}

void DatabaseEditor::on_bttnRemoveRow_clicked()
{
    int rowNumber = ui->tableViewDisplayTable->currentIndex().row();
    if(rowNumber)
    {
        m_model->removeRow(rowNumber);
        m_model->select();
    }
    else
        m_model->removeRow(m_model->rowCount()-1);



}
