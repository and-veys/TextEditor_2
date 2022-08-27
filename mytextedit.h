#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>



class MyTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    MyTextEdit(QWidget * parent, const QString & nm="");
    ~MyTextEdit();
    QString getFileName();
    bool isNewDocument();
    bool open();
    bool save(QString nm);

private:
    QString file_name;
private:
    bool read(QString & res);
    bool write(const QString & nm);
};

#endif // MYTEXTEDIT_H
