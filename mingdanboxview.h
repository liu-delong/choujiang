#ifndef MINGDANBOXVIEW_H
#define MINGDANBOXVIEW_H

#include <QWidget>
#include "ui_mingdanboxview.h"
namespace Ui {
class MingDanBoxView;
}

class MingDanBoxView : public QWidget
{
    Q_OBJECT

public:
    explicit MingDanBoxView(QWidget *parent = nullptr);
    ~MingDanBoxView();
    Ui::MingDanBoxView *ui;
private:

};

#endif // MINGDANBOXVIEW_H
