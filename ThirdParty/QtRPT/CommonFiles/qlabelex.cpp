/*
Name: CommonFiles
Version: 1.3.4
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net012-2014
*/


#include "qlabelex.h"

QLabelEx::QLabelEx(QWidget *parent) : QLabel(parent) {
    m_bHover = false;
    setCursor(Qt::PointingHandCursor);
}

QLabelEx::QLabelEx(const QString &Text, QWidget *parent) : QLabel(Text, parent) {
    m_bHover = false;
    setCursor(Qt::PointingHandCursor);
}

QLabelEx::~QLabelEx() {
}

void QLabelEx::setHoverText(bool bHover) {
    m_bHover = bHover;
}

void QLabelEx::enterEvent(QEvent *) {
    if( m_bHover ) {
        QFont font = this->font();
        font.setUnderline(m_bHover);
        setFont(font);
    }
}

void QLabelEx::leaveEvent(QEvent *) {
    if( m_bHover ) {
        QFont font = this->font();
        font.setUnderline(false);
        setFont(font);
    }
}

void QLabelEx::mouseReleaseEvent(QMouseEvent *) {
    emit clicked();
}
