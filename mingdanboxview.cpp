#include "mingdanboxview.h"
#include "ui_mingdanboxview.h"

MingDanBoxView::MingDanBoxView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MingDanBoxView)
{
    ui->setupUi(this);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(255,170,127,100));
    setAutoFillBackground(true);
    setPalette(pal);
    auto t=ui->scrollAreaWidgetContents;
    t->setPalette(pal);
}

MingDanBoxView::~MingDanBoxView()
{
    delete ui;
}
