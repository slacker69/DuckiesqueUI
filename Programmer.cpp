#include "Programmer.h"

Programmer::Programmer(QWidget *parent) : QDialog(parent)
{
#if defined(Q_OS_LINUX)
    p = which(&pkexec_path, "pkexec");
    if(p)
        p = which(&programmer_path, "dfu-programmer");
#elif defined(Q_OS_MACOS)
    p = false;
#elif defined(Q_OS_WINDOWS)
    p = false;
#else
#error Invalid OS
#endif

}

bool Programmer::hasProgrammer() const{
    return p;
}

QString Programmer::getProgrammer() const{
    return programmer_path;
}

QString Programmer::getPkexec() const{
    return pkexec_path;
}

bool Programmer::which(QString *file, QString name){
    (*file) = QString();
    QList<QByteArray> paths = qgetenv("PATH").split(QDir::listSeparator().cell());
    foreach(QString path, paths){
        QFileInfo f(path);
        if(!f.exists() || !f.isDir())
            continue;
        QString c = path+QDir::separator()+name;
        if(QFileInfo(c).exists()){
            (*file) = c;
            return true;
        }
    }
    return false;
}
