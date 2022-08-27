#include "mytreewidget.h"

MyTreeWidget::MyTreeWidget(QWidget * parent) : QTreeWidget(parent)
{

}

MyTreeWidget::~MyTreeWidget()
{

}

void MyTreeWidget::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);
}
