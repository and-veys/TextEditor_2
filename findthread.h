#ifndef FINDTHREAD_H
#define FINDTHREAD_H

#include <QDir>
#include <QObject>
#include <QTextEdit>
#include <QThread>



class FindThread : public QThread
{
    Q_OBJECT
public:
    void start(QString nm, QString ph);
    void stop();

signals:
    void print(const QString nm);
    void title(const QString nm);
    void end();

protected:
    void run() override;
private:
    int turn;
    QString path;
    QString name;
    int find(const QString & ph);
};

#endif // FINDTHREAD_H
