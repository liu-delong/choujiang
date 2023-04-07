#include "mingdanview.h"
#include "ui_mingdanview.h"

MingDanView::MingDanView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MingDanView)
{
    ui->setupUi(this);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(255,255,127,100));
    setAutoFillBackground(true);
    setPalette(pal);
}

MingDanView::~MingDanView()
{
    delete ui;
}


