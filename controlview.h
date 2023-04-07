#ifndef CONTROLVIEW_H
#define CONTROLVIEW_H

#include <QWidget>
#include "ui_controlview.h"
namespace Ui {
class ControlView;
}

class ControlView : public QWidget
{
    Q_OBJECT

public:
    explicit ControlView(QWidget *parent = nullptr);
    ~ControlView();
    Ui::ControlView *ui;
private slots:
    void on_horizontalSlider_valueChanged(int value);

private:

};

#endif // CONTROLVIEW_H
