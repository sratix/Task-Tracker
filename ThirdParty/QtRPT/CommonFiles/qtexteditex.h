/*
Name: CommonFiles
Version: 1.4.4
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2010-2014
*/

#ifndef QTEXTEDITEX_H
#define QTEXTEDITEX_H

#include <QWidget>
#include <QTextEdit>
#include <QTextList>

namespace Ui {
    class QTextEditEx;
}

class QTextEditEx : public QWidget {
    Q_OBJECT
public:
    QTextEditEx(QWidget *parent = 0);
    ~QTextEditEx();
    QTextEdit *textEdit;

protected:

private:
    Ui::QTextEditEx *m_ui;
    void setupTextActions();
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void alignmentChanged(Qt::Alignment a);
    void fontChanged(const QFont &f);

private slots:
    void textSize(const QString &p);
    void textFamily(const QString &f);
    void textStyle(int styleIndex);
    void textBold();
    void textItalic();
    void textUnderline();
    void textAlign();
    void textColor();
    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();
};

#endif // QTEXTEDITEX_H
