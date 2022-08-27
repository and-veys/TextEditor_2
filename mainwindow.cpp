#include "mainwindow.h"
#include "mytextedit.h"

#include <QDockWidget>
#include <QMenu>
#include <QMessageBox>
#include <QMenuBar>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QStatusBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Текстовый редактор");

    QMenu * menu = new QMenu("&File");
    menu->addAction("&New", [this]{newDoc();});
    menu->addAction("&Open", [this]{open();});
    menu->addAction("&Save", [this]{save();});
    menu->addAction("&Save as...", [this]{saveAs();});
    menu->addAction("&Print", [this]{print();});
    menuBar()->addMenu(menu);

    menu = new QMenu("&Info");
    menu->addAction("&Help", [this]{help();});
    menuBar()->addMenu(menu);

    tree = new MyTreeWidget(this);
    QDockWidget * dock = new QDockWidget(this);
    dock->setWidget(tree);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    model_file_system.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
    model_file_system.setRootPath("C:/");
    tree->setModel(&model_file_system);
    for (int i = 1; i < model_file_system.columnCount(); ++i)
        tree->hideColumn(i);

    mdi = new QMdiArea(this);
    setCentralWidget(mdi);

    label = new QLabel(this);
    QStatusBar * bar = statusBar();
    bar->addWidget(label);

    connect(tree, &QTreeView::clicked, this, &MainWindow::onClickTree);
}

MainWindow::~MainWindow()
{

}


void MainWindow::onClickTree()
{
     QItemSelectionModel * sel_model = tree->selectionModel();
     if (sel_model->hasSelection()) {
         QModelIndex cur = sel_model->currentIndex();
         if(cur.isValid()) {
             QFileInfo f(model_file_system.filePath(cur));
             if(f.isFile() && f.suffix().toLower() == "txt")
                    open(f.filePath());
             if(f.isDir())
                label->setText(f.absoluteFilePath());
             else
                label->setText(f.absolutePath());
         }
     }
}

void MainWindow::newDoc()
{
    MyTextEdit * txt = new MyTextEdit(this);
    setTextEditTitle(txt, mdi->addSubWindow(txt));
    txt->show();
}
void MainWindow::open(QString nm)
{
    if(nm == "")
        nm = QFileDialog::getOpenFileName(this, "Открыть текстовый файл", QDir::currentPath(), "Text files (*.txt)");
    if(nm == "")
        return;
    MyTextEdit * txt = new MyTextEdit(this, nm);
    if(!txt->open())
        QMessageBox::critical(this, "Ошибка", "Ошибка чтения файла...");
    setTextEditTitle(txt, mdi->addSubWindow(txt));
    txt->show();
}

void MainWindow::setTextEditTitle(MyTextEdit * txt, QMdiSubWindow * sw)
{
    QMdiSubWindow * w = sw;
    if(w == nullptr)
        w = mdi->currentSubWindow();
    w->setWindowTitle(txt->getFileName());

}

void MainWindow::save(const QString & nm)
{
    MyTextEdit * txt = getActivTextEdit();
    if(txt == nullptr)
        return;
    if(nm == "" && txt->isNewDocument())
        saveAs();
    else {
        if(!txt->save(nm))
            QMessageBox::critical(this, "Ошибка", "Ошибка записи в файл...");
        setTextEditTitle(txt);
    }
}
void MainWindow::saveAs()
{
    MyTextEdit * txt = getActivTextEdit();
    if(txt == nullptr)
        return;
    QString nm = QFileDialog::getSaveFileName(this, "Сохранить в новый файл", QDir::currentPath(), "Text files (*.txt)");
    if(nm == "")
         return;
    save(nm);
}

void MainWindow::help()
{
    QMessageBox::information(this, "Справка", "Здесь должна быть справка");
}

void MainWindow::print()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle("Print");
    if (dlg.exec() != QDialog::Accepted)
        return;
    MyTextEdit * txt = getActivTextEdit();
    if(txt == nullptr)
        return;
    txt->print(&printer);
}

MyTextEdit *MainWindow::getActivTextEdit()
{
    QMdiSubWindow * w = mdi->currentSubWindow();
    if(w == nullptr)
        return nullptr;
    return (MyTextEdit *)(w->widget());
}

