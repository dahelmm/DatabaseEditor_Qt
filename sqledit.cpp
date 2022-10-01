#include "sqledit.h"


SQLEdit::SQLEdit(QTextEdit *editor)
{
    highlighter = new Highlighter(editor->document());
    // completer = new QWordCompleter(wordList, this); // ! оптимизировать !
}

/*
QString SQLEdit::getQuery()
{
    if (checkQuery(query))
        return query;

}

// Проверка запроса на валидность
bool SQLEdit::checkQuery(const QString &query)
{

}
*/
