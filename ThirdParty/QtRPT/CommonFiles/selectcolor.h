#ifndef SELECTCOLOR_H
#define SELECTCOLOR_H

#include <QWidget>
#include <QToolButton>
#include <QHBoxLayout>

class SelectColor : public QWidget
{
    Q_OBJECT
public:
    explicit SelectColor(QWidget *parent = 0, QString rgbColor = "rgba(255,255,255,255)");
    QToolButton *button;
    QString getBackGroundColor();
    void setBackGroundColor(QString rgbColor);
    void setMargins(QMargins margins);

private:
    QHBoxLayout *vLayout;

signals:

public slots:

};

#endif // SELECTCOLOR_H
