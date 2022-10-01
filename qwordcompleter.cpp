#include "qwordcompleter.h"

#include <QEvent>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QTextEdit>
#include <QTextCursor>

QWordCompleter::QWordCompleter(const QStringList &completions, QObject *parent):
    QCompleter(completions, parent)
{
}

QWordCompleter::~QWordCompleter()
{
}

bool QWordCompleter::eventFilter(QObject *o, QEvent *e)
{
    // виджет которйы подключили унаследован от класса QTextEdit?
    if ( widget()->inherits("QTextEdit") && e->type() == QEvent::KeyPress) // событие e - это событие клавиатуры?
    {
        QKeyEvent* ke = static_cast<QKeyEvent*>(e);
        switch (ke->key())
        {
        case Qt::Key_Space: // Space + Ctrl
            if (ke->modifiers().testFlag(Qt::ControlModifier))
            {
                // определение курсора подстроки
                QTextEdit *textEdit = qobject_cast<QTextEdit*>(widget());
                QTextCursor textCursor = textEdit->textCursor();
                textCursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);

                // если размер текста больше min -> автозаполнение
                if (textCursor.selectedText().length() >= minCompletionPrefixLength)
                {
                    setCompletionPrefix(textCursor.selectedText()); // на основе какой подстроки мы будем фильтровать модель
                    QRect rect = QRect(textEdit->cursorRect().bottomLeft(), QSize(100, 5));// место где будет всплывать этот список
                    complete(rect);
                }
                return true;
            }
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Tab:
            // автозаполнение открыто?
            if (popup()->isVisible())
            {
                popup()->hide();
                if (popup()->currentIndex().isValid()) // выбрано слово?
                {
                    // сигнал
                    emit activated(popup()->currentIndex());
                    emit activated(popup()->currentIndex().data(completionRole()).toString());
                }
            return true;
            }
            break;
        default:
            break;
        }
    }
    return QCompleter::eventFilter(0, e);
}

int QWordCompleter::getMinCompletionPrefixLength() const
{
    return minCompletionPrefixLength;
}

void QWordCompleter::setMinCompletionPrefixLength(int value)
{
    minCompletionPrefixLength = value;
}
