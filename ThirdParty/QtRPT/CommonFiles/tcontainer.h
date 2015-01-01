/*
Name: CommonFiles
Version: 1.3.4
Programmer: Aleksey Osipov
e-mail: aliks-os@ukr.net012-2014
*/

#ifndef TCONTAINER_H
#define TCONTAINER_H

#include <QtDebug>
#include <QWidget>
#include <QMenu>
#include <QVBoxLayout>
#include <QMetaProperty>

enum modes{
    NONE = 0,
    MOVE = 1,
    RESIZETL = 2,
    RESIZET = 3,
    RESIZETR = 4,
    RESIZER = 5,
    RESIZEBR = 6,
    RESIZEB = 7,
    RESIZEBL = 8,
    RESIZEL = 9
};

class TContainer : public QWidget {
    Q_OBJECT
    Q_PROPERTY(bool Selected READ isSelected WRITE setSelected)
public:
    TContainer(QWidget *parent, QPoint p, QWidget *cWidget = 0);
    ~TContainer();
    QWidget *childWidget;
    QMenu *menu = 0;
    void setChildWidget(QWidget *cWidget);
    void setSelected(bool value);
    void setPasted(bool value);
    bool isSelected();
    qreal scale;
    void setScale(qreal scale);
    void allowResize(bool value);
    void allowDrawSelection(bool value);
    bool isAllowDrawSelection();
    virtual TContainer *clone();
    QRect getOldGeom();
    void setOldGeom(QRect rect);

    friend QDataStream &operator<<(QDataStream &stream, const TContainer &obj);
    friend QDataStream &operator>>(QDataStream &stream, TContainer &obj);

protected:
    int mode;
    QPoint position;
    QVBoxLayout* vLayout;
    void setCursorShape(const QPoint &e_pos);
    bool eventFilter( QObject *obj, QEvent *evt );
    void keyPressEvent(QKeyEvent *);
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *e);
    bool m_selected;
    bool m_pasting;
    bool m_showMenu;
    bool m_isEditing;
    void popupShow(const QPoint &pt);

private:    
    QRect m_oldRect;
    bool m_allowResize;
    bool m_allowDrawSelection;
    void m_geomChanged(QRect oldRect, QRect newRect);

signals:
    void inFocus(bool mode);
    void newGeometry(QRect oldRect, QRect newRect);
    void geomChanged(QRect oldRect, QRect newRect);
    void deleteByUser();

public slots:

};

#endif // TCONTAINER_H
