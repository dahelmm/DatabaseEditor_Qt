#ifndef QWORDCOMPLETER_H
#define QWORDCOMPLETER_H

#include <QCompleter>
#include <QWidget>

class QWordCompleter : public QCompleter
{
    Q_OBJECT
public:
    QWordCompleter(const QStringList& completions, QObject *parent = 0);
    ~QWordCompleter();


    // QObject interface
public:
    bool eventFilter(QObject *o, QEvent *e); // перехват клавиш в textEditor
    int getMinCompletionPrefixLength() const;
    void setMinCompletionPrefixLength(int value);

private:
    int minCompletionPrefixLength = 1;
};

#endif // QWORDCOMPLETER_H
