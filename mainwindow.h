#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QString>
#include "controlview.h"
#include "mingdanboxview.h"
#include "mingdanview.h"
#include <QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using namespace std;
class Mythread:public QThread
{
     Q_OBJECT
public:
    Mythread(bool& runing,int& mode,int& speed,int size);
    bool& _runing;
    int& _mode;
    int& _speed;
    int _size;
    void run() override;
signals:
    void selectitem(int old_index,int new_index);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ControlView* _ctv;
    MingDanView* _mdv;
    MingDanBoxView* _bxv;
    int _mode=0;
    int _speed=50;
    int _choose;
    bool _runing;
    QPalette default_pal;
    vector<QString> _nameList;
    Mythread *_t;
    MainWindow(QWidget *parent = nullptr);
    vector<QString> getNameList();
    void insertBox(vector<QString> nameList);
    ~MainWindow();
public slots:
    void on_dao_ru_ming_dan();
    void on_start_choujiang();
    void on_stop_choujiang();
    void on_selectitem(int old_index,int new_index);
    void on_speed_changed(int value);
    void on_mode_changed(QString text);




private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
