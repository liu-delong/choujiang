#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QTableView>
#include <QDebug>
#include <QLabel>
#include <QGridLayout>
#include <random>
#include <algorithm>
#include <ctime>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _mdv=(MingDanView*)ui->frame->ming_dan;
    _bxv=(MingDanBoxView*)ui->frame->ming_dan_box;
    _ctv=(ControlView*)ui->frame->control;
    _speed=_ctv->ui->horizontalSlider->value();
    on_mode_changed(_ctv->ui->comboBox->currentText());
    connect(_mdv->ui->pushButton,SIGNAL(clicked()),this,SLOT(on_dao_ru_ming_dan()));
    connect(_ctv->ui->begin_bt,SIGNAL(clicked()),this,SLOT(on_start_choujiang()));
    connect(_ctv->ui->end_bt,SIGNAL(clicked()),this,SLOT(on_stop_choujiang()));
    connect(_ctv->ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(on_speed_changed(int)));
    connect(_ctv->ui->comboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_mode_changed(QString)));


}
vector<QString> MainWindow::getNameList()
{
    _nameList.clear();
    auto table=_mdv->ui->widget;
    auto model=table->model();
    for(int i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)).toString()!="")
        {
            _nameList.push_back(model->data(model->index(i,0)).toString());
            qDebug()<<model->data(model->index(i,0)).toString();
        }
    }
    return _nameList;

}

void MainWindow::insertBox(vector<QString> nameList)
{
    auto layout=(QGridLayout*)(_bxv->ui->scrollAreaWidgetContents->layout());
    for(int i=0;i<layout->count();i++)
    {
        layout->removeItem(layout->itemAt(i));
    }
    for(int i=0;i<nameList.size();i++)
    {
        auto lb=new QLabel(nameList[i]);
        auto p=lb->palette();
        p.setColor(QPalette::Background,Qt::yellow);
        default_pal=p;
        lb->setAutoFillBackground(true);
        lb->setPalette(default_pal);
        layout->addWidget(lb,i/6,i%6);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dao_ru_ming_dan()
{
    insertBox(getNameList());
}

void MainWindow::on_start_choujiang()
{
    if(_nameList.size()>0)
    {
        _ctv->ui->end_bt->setDisabled(false);
        _ctv->ui->begin_bt->setDisabled(true);
        _mdv->ui->pushButton->setDisabled(true);
        _t=new Mythread(_runing,_mode,_speed,_nameList.size());
        _t->start();
        connect(_t,SIGNAL(selectitem(int,int)),this,SLOT(on_selectitem(int,int)));
        auto l=_bxv->ui->scrollAreaWidgetContents->layout();
        for(int i=0;i<l->count();i++)
        {
            auto lb=l->itemAt(i)->widget();
            lb->setPalette(default_pal);
        }
    }

}

void MainWindow::on_stop_choujiang()
{
    _runing=false;
    _mdv->ui->pushButton->setDisabled(false);
    _ctv->ui->begin_bt->setDisabled(false);
    _ctv->ui->end_bt->setDisabled(true);
    auto lb=(QLabel*)_bxv->ui->scrollAreaWidgetContents->layout()->itemAt(_choose)->widget();
    QString tq=_ctv->ui->textBrowser->toPlainText();
    tq+=lb->text()+"\n";
    _ctv->ui->textBrowser->setText(tq);
    _t->wait();
    delete _t;
}

void MainWindow::on_selectitem(int old_index,int new_index)
{
    auto layout=_bxv->ui->scrollAreaWidgetContents->layout();
    if(old_index>=0)
    {
        auto lbo=(QLabel*)layout->itemAt(old_index)->widget();
        lbo->setPalette(default_pal);
    }
    auto lb=(QLabel*)layout->itemAt(new_index)->widget();
    auto pal=lb->palette();
    pal.setColor(QPalette::Background,Qt::green);
    lb->setPalette(pal);

    _choose=new_index;
}

void MainWindow::on_speed_changed(int value)
{
    _speed=value;
}

void MainWindow::on_mode_changed(QString text)
{
    if(text=="顺序")
    {
        _mode=0;
    }
    else if(text=="随机")
    {
        _mode=1;
    }
    else
    {
        _mode=2;
    }
}



Mythread::Mythread(bool &runing, int &mode, int &speed, int size)
:_runing(runing),
 _mode(mode),
 _speed(speed),
 _size(size)
{

}

void Mythread::run()
{
    _runing=true;
    vector<int> a(_size);
    for(int i=0;i<_size;i++) a[i]=i;
    srand(time(0));
    random_shuffle(a.begin(),a.end());
    default_random_engine e;
    uniform_int_distribution<int> u(0,_size-1);
    int current=-1;
    int mode2_help=-1;
    while(_runing)
    {
        if(_mode==0)
        {
            int oc=current;
            current=(current+1)%_size;
            mode2_help=current;
            emit selectitem(oc,current);
        }
        else if(_mode==1)
        {
            int oc=current;
            current=u(e);
            mode2_help=current;
            emit selectitem(oc,current);
        }
        else
        {
            mode2_help=(mode2_help+1)%_size;
            int oc=current;
            current=a[mode2_help];
            emit selectitem(oc,current);
        }
        QThread::msleep(10+1000/_speed);
    };
}
