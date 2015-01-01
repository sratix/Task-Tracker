#include "selectcolor.h"

SelectColor::SelectColor(QWidget *parent, QString rgbColor) : QWidget(parent) {
    //QWidget *w = new QWidget(ui->tableWidget);
    QWidget *colorBox = new QWidget(this);
    colorBox->setObjectName("colorBox");
    QString stl = "QWidget#colorBox {;"
                  "border-width:1px;"
                  "border-style:solid;"
                  "border-color:rgba(0,0,0,255);"
                  "border-top-color:rgba(0,0,0,255);"
                  "border-left-color:rgba(0,0,0,255);"
                  "border-right-color:rgba(0,0,0,255);"
                  "border-bottom-color:rgba(0,0,0,255);"
                  "color:rgba(0,0,0,255);"
                  "background-color:"+rgbColor+";"
            "}";
    colorBox->setStyleSheet(stl);

    button = new QToolButton(this);
    vLayout = new QHBoxLayout(this);
    vLayout->addWidget(colorBox);
    vLayout->addWidget(button);
    vLayout->setContentsMargins(0,0,0,0);
    this->setLayout(vLayout);
}

QString SelectColor::getBackGroundColor() {
    QWidget *colorBox = this->findChild<QWidget *>("colorBox");
    QString str1 = colorBox->styleSheet();
    int start; int end;
    start = str1.indexOf(";background-color:",0,Qt::CaseInsensitive);
    end = str1.indexOf(";",start+1,Qt::CaseInsensitive);

    QString tmp = str1.mid(start+1,end-start-1);
    start = tmp.indexOf("rgba",0,Qt::CaseInsensitive);
    tmp = tmp.mid(start);
    if (start == -1) tmp = "";
    if (tmp == "#ffffff") tmp = "rgba(255,255,255,0)";
    return tmp;
}

void SelectColor::setBackGroundColor(QString rgbColor) {
    QString stl = "QWidget#colorBox {;"
                  "border-width:1px;"
                  "border-style:solid;"
                  "border-color:rgba(0,0,0,255);"
                  "border-top-color:rgba(0,0,0,255);"
                  "border-left-color:rgba(0,0,0,255);"
                  "border-right-color:rgba(0,0,0,255);"
                  "border-bottom-color:rgba(0,0,0,255);"
                  "color:rgba(0,0,0,255);"
                  "background-color:"+rgbColor+";"
            "}";
    QWidget *colorBox = this->findChild<QWidget *>("colorBox");
    colorBox->setStyleSheet(stl);
}

void SelectColor::setMargins(QMargins margins) {
    vLayout->setContentsMargins(margins);
}
