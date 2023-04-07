#include "myframe.h"
#include "QWidget"
#include "mingdanboxview.h"
#include "mingdanview.h"
#include "controlview.h"
MyFrame::MyFrame(QWidget *parent):
    QFrame(parent),
    ming_dan_box(new MingDanBoxView(this)),
    ming_dan(new MingDanView(this)),
    control(new ControlView(this))
{
    setMinimumSize(1, 1);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
void MyFrame::resizeEvent(QResizeEvent *event)
{
    qDebug()<<width()<<" "<<height();
    auto x=width()*0.255;
    auto y=height()*0.078;
    auto w=width()*0.775-x;
    auto h=height()*0.940-y;
    ming_dan_box->setGeometry(x,y,w,h);
    x=width()*0.083;
    y=height()*0.15;
    w=width()*0.248-x;
    h=height()*0.56-y;
    ming_dan->setGeometry(x,y,w,h);
    x=width()*0.78;
    y=height()*0.285;
    w=width()*0.945-x;
    h=height()*0.68-y;
    control->setGeometry(x,y,w,h);

    QFrame::resizeEvent(event);
}
