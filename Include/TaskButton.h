#ifndef TASKBUTTON_H
#define TASKBUTTON_H

#include <QAction>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include "Task.h"
#include "TimeEditWidget.h"

class TaskButton : public QWidget
{
    Q_OBJECT
public:
    TaskButton(QWidget *parent = 0);
    void setTask(Task *task);

    bool isEditing() const;
    void startRenaming();
    void startSettingTime();

public slots:
    void tick();
    void cancelEditing();
    void setActive(bool active);


signals:
    void startedEditing();
    void finishedEditing();
    void cancelledEditing();
    void movedUp();
    void movedDown();
    void deleted();
    void activated(bool active);
    void buttonClicked();
    void taskDone();

private slots:
    void onButtonClick();
    void finishRenaming();
    void finishSettingTime();

    void doDoneAction();
    void doMoveUpAction();
    void doMoveDownAction();
    void doRenameAction();
    void doSetTimeAction();
    void doResetAction();
    void doDeleteAction();
    void updateButton();



private:

    enum State {
        NORMAL,
        EDITING
    };

    Task *task;
    State state;

    QBoxLayout *layout;
    QPushButton *button;
    QLineEdit *lineEdit;
    TimeEditWidget *timeEdit;

    QAction *doneAction;
    QAction *moveUpAction;
    QAction *moveDownAction;
    QAction *renameAction;
    QAction *resetAction;
    QAction *setTimeAction;
    QAction *deleteAction;

    void changeState(State newState);
    void createWidgets();
    void createActions();
    void updateLineEdit();
    void updateTimeEdit();

    bool eventFilter(QObject *obj, QEvent *event);

};

#endif // TASKBUTTON_H
