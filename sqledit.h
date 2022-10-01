#ifndef SQLEDIT_H
#define SQLEDIT_H

#include <QTextEdit>
#include "highlighter.h"
#include "qwordcompleter.h"

class SQLEdit
{
public:
    SQLEdit(QTextEdit* editor);

    QString getQuery();

private:
    inline bool checkQuery(const QString &query);

    Highlighter *highlighter;
    QCompleter* completer;

    QString query;
    QStringList wordList;

};

#endif // SQLEDIT_H
