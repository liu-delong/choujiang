#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <QLayout>
#include <QGridLayout>
#include <QDebug>
#include <QTableView>
class MyFrame : public QFrame
{


public:
    QWidget *ming_dan_box;
    QWidget *ming_dan;
    QWidget *control;
    MyFrame(QWidget *parent);

protected:
    void resizeEvent(QResizeEvent *event) override;

};

#endif // MYFRAME_H
