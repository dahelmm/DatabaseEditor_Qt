#include "databaseeditor.h"
#include "ui_databaseeditor.h"

#include <QFileDialog>

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseEditor::DatabaseEditor(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::DatabaseEditor)
  , database(nullptr)
{
    ui->setupUi(this);
    database = new Database(this);
    m_model = new QSqlTableModel(this);
    ui->tableViewDisplayTable->setModel(m_model);


    highlighter = new Highlighter(ui->textEditSQL->document());
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
        ui->textEditSQL->setFocus();
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

/// Yoonoma
void DatabaseEditor::on_bttnRunSQL_clicked()
{
    // Модель для отображения данных SQL запроса
    QSqlQueryModel *model = new QSqlQueryModel(ui->tableViewQuery);
    QSqlQuery query;

    query.exec(ui->textEditSQL->toPlainText());
    model->setQuery(query);
    ui->tableViewQuery->setModel(model);


    ui->textBrowserOutputSQL->setTextColor(QColor(0, 255, 0));

    // Проверка запроса на валидность
    if (model->lastError().type() != QSqlError::NoError) // eсли возникла ошибка
    {
        ui->textBrowserOutputSQL->setTextColor(QColor(255, 0, 0));
        ui->textBrowserOutputSQL->setText(model->lastError().text());

    }
    else if (model->query().isSelect()) // eсли запрос "SELECT%"
        ui->textBrowserOutputSQL->setText(tr("Запрос выполнен."));
    else
        ui->textBrowserOutputSQL->setText(tr("Запрос выполнен. "
                                             "Количество затронутых строк: %1\nНовая таблица:").arg(
                                              model->query().numRowsAffected()));

    ui->textEditSQL->setFocus(); // Указатель на курсор в edit

///Все строки, которые увидит пользователь должны быть обработаны функциями QObject::tr()
///или QcoreApplication::translate().
}
