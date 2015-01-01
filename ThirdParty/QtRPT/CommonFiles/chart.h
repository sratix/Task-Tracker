/*
Name: QtRpt
Version: 1.4.4
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net
2012-2014
*/

#ifndef CHART_H
#define CHART_H

#include <QPainter>
#include <QWidget>
#include <QPaintEvent>
#include <QStyleOption>
#include <QDomElement>
#include <QDebug>
#include <CommonClasses.h>

enum ChartParam {
    DrawGrid = 0,
    ShowCaption = 1,
    ShowLegend = 2,
    ShowGraphCaption = 3,
    ShowPercent = 4,
    Caption = 5,
    AutoFillData = 6
};

struct GraphParam {
    QColor color;
    float valuePercent;
    float valueReal;
    QString valueString;
    QString caption;
};

typedef QList<GraphParam> GraphParamList;
Q_DECLARE_METATYPE(GraphParam)
Q_DECLARE_METATYPE(GraphParamList)
Q_DECLARE_METATYPE(QDomElement)

class Chart : public QWidget {
    Q_OBJECT    
public:
    explicit Chart(QWidget *parent = 0);
    void setParams(bool drawGrid, bool drawHistory, bool drawCaption, bool drawGraphCaption, bool showPercent, QString caption, bool autoFillData);
    void setData(GraphParam param, float value100Percent=0);
    QVariant getParam(ChartParam param);
    GraphParamList getGraphParamList();
    void paintChart(QPainter *painter);
    void setKoef(float koefRes_w, float koefRes_h, float left, float top);
    void clearData();
    void loadXML(QDomElement e);
    void setProperties();
    friend QDataStream &operator<<(QDataStream &stream, const Chart &obj);
    friend QDataStream &operator>>(QDataStream &stream, Chart &obj);

protected:
    void paintEvent(QPaintEvent * event);
    void setParamFromProperties();

private:
    QList<GraphParam> listOfGraph;
    QString m_caption;
    bool m_drawGrid;
    bool m_drawHistory;
    bool m_drawCaption;
    bool m_drawGraphCaption;
    bool m_showPercent;
    bool m_autoFillData;
    int m_rightSpaceWidth;
    int m_bottomSpaceHeight;
    int m_captionHeight;
    float m_correctValue;
    float m_koefRes_h;
    float m_koefRes_w;
    float m_left;
    float m_top;

signals:

public slots:

};


#endif // CHART_H
