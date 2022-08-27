#include "mytextedit.h"

#include <QFile>


MyTextEdit::MyTextEdit(QWidget * parent, const QString & nm) : QTextEdit(parent), file_name(nm)
{

}

MyTextEdit::~MyTextEdit()
{

}

QString MyTextEdit::getFileName()
{
    if(file_name== "")
        return "Новый документ";
    return file_name.split("/").last();
}

bool MyTextEdit::isNewDocument()
{
    return (file_name == "");
}

bool MyTextEdit::open()
{
    if(file_name == "")
        return true;
    QString txt;
    if(!read(txt)) {
        file_name = "";
        return false;
    }
    setText(txt);
    return true;
}

bool MyTextEdit::save(QString nm)
{
    if(nm == "")
        nm = file_name;
    if(!write(nm))
        return false;
    file_name = nm;
    return true;
}

bool MyTextEdit::read(QString & res)
{
    QFile file(file_name);
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray arr = file.readAll();
        file.close();
        res = arr;
        return true;
    }
    return false;
}

bool MyTextEdit::write(const QString &nm)
{
    QFile file(nm);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(toPlainText().toUtf8());
        file.close();
        return true;
    }
    return false;
}

