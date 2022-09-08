#include "findthread.h"

void FindThread::start(QString nm, QString ph)
{
    turn = 0;
    name = std::move(nm);
    path = std::move(ph);
    QThread::start();

}

void FindThread::run() {
    if(find(path) == 0)
         emit print("--- Nothing found ---");
    disconnect();
}

int FindThread::find(const QString & ph) {
    ++turn;
    emit title("Progress: " + QString::number(turn));
    if(name=="")
        return 0;
    QDir dir(ph);
    int count = 0;
    if(dir.dirName() == name) {
        ++count;
        emit print("DIR : " + dir.absolutePath());
    }
    QFileInfoList list = dir.entryInfoList(QDir::Files);
    for(int i=0; i<list.size(); ++i) {
        if(list[i].fileName() == name) {
            ++count;
            emit print("FILE: " + list[i].absoluteFilePath());
        }
    }
    list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
    for(int i=0; i<list.size(); ++i)
        count += find(list[i].absoluteFilePath());
    return count;
}

void FindThread::stop()
{
    emit print("--- Stopped ---");
    name = "";
}
