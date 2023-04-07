#ifndef MINGDANVIEW_H
#define MINGDANVIEW_H

#include <QWidget>
#include "ui_mingdanview.h"
namespace Ui {
class MingDanView;
}

class MingDanView : public QWidget
{
    Q_OBJECT

public:
    explicit MingDanView(QWidget *parent = nullptr);
    ~MingDanView();
    Ui::MingDanView *ui;

private:

};

#endif // MINGDANVIEW_H
