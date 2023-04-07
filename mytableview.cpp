#include "mytableview.h"
#include<QApplication>
#include<QKeyEvent>
#include<QString>
#include<QModelIndex>
#include<QClipboard>
#include<QMimeData>
#include<QStandardItemModel>
#include<QString>
#include<QStyledItemDelegate>
#include <QPainter>
MyTableView::MyTableView(QWidget *parent) : QTableView(parent)
{
    QStandardItemModel *model = new QStandardItemModel();
    model->setRowCount(1000);
    model->setColumnCount(1);
    model->setHeaderData(0,Qt::Horizontal,"姓名");
    setModel(model);
    setStyleSheet("QTableView { background-color: white; }"
                      "QTableView::item:selected { color: white; background-color: blue; }"
                      "QTableView::horizontalHeader { background-color: lightgray; }"
                      "QTableView::verticalHeader { background-color: lightgray; }");
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    setAlternatingRowColors(true);
    setSortingEnabled(true);
    setWordWrap(false);
    setTabKeyNavigation(true);


}

void MyTableView::keyPressEvent(QKeyEvent *event)
{
    if (event->matches(QKeySequence::Paste)) {
        QClipboard *clipboard = QGuiApplication::clipboard();
        const QMimeData *mimeData = clipboard->mimeData();
        if (mimeData->hasText()) {
            QString text = mimeData->text();
            QStringList rows = text.split(QLatin1Char('\n'), QString::SkipEmptyParts);
            if (rows.count() > 0) {
                QModelIndexList selectedIndexes = selectionModel()->selectedIndexes();
                if (selectedIndexes.count() > 0) {
                    int row = selectedIndexes.at(0).row();
                    int column = selectedIndexes.at(0).column();
                    int maxRow = model()->rowCount();
                    int maxColumn = model()->columnCount();
                    for (int i = 0; i < rows.count(); i++) {
                        if (row + i >= maxRow) {
                            model()->insertRow(row + i);
                        }
                        QStringList values = rows.at(i).split(QLatin1Char('\t'), QString::SkipEmptyParts);
                        for (int j = 0; j < values.count(); j++) {
                            if (column + j >= maxColumn) {
                                continue;
                            }
                            QModelIndex index = model()->index(row + i, column + j);
                            model()->setData(index, values.at(j));
                        }
                    }
                }
            }
        }
    }
    else {
        QTableView::keyPressEvent(event);
    }
         // 更新视图
     viewport()->update();
     return;
}

#include<QDebug>
QVariant MyTableView::getData(int row, int column)
{
    QModelIndex index = model()->index(row, column); // 获取指定单元格的索引
    QVariant data = model()->data(index); // 获取指定单元格的 UserRole 角色数据
    return data;

}


