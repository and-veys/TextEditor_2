#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mytextedit.h"
#include "mytreewidget.h"

#include <QFileSystemModel>
#include <QLabel>
#include <QMainWindow>
#include <QMdiArea>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
     QFileSystemModel model_file_system;
     MyTreeWidget * tree;
     QMdiArea * mdi;
     QLabel * label;
private slots:
     void onClickTree();
private:
     void newDoc();
     void open(QString nm="");
     void save(const QString & nm="");
     void saveAs();
     void help();
     void print();
     MyTextEdit * getActivTextEdit();
     void setTextEditTitle(MyTextEdit * txt, QMdiSubWindow * w=nullptr);

};
#endif // MAINWINDOW_H
