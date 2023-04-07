#include "controlview.h"
#include "ui_controlview.h"

ControlView::ControlView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlView)
{
    ui->setupUi(this);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(255,255,127,100));
    setAutoFillBackground(true);
    setPalette(pal);
    ui->label_3->setText(QString::number(ui->horizontalSlider->value()));
}

ControlView::~ControlView()
{
    delete ui;
}

void ControlView::on_horizontalSlider_valueChanged(int value)
{
    ui->label_3->setText(QString::number(value));
}

