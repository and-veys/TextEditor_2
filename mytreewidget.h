#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QTreeWidget>


class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    MyTreeWidget(QWidget * parent);
    ~MyTreeWidget();
    void setModel(QAbstractItemModel *model) override;
};

#endif // MYTREEWIDGET_H
