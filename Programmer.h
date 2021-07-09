#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <QObject>
#include <QDialog>
#include <QFileInfo>
#include <QDir>
#include <QProcess>

#include <QDebug>

class Programmer : public QDialog
{
public:
    Programmer(QWidget *parent = nullptr);
    bool hasProgrammer() const;
    QString getProgrammer() const;
    QString getPkexec() const;

private:
    bool which(QString *file, QString name);
    bool p;
    QString programmer_path;
    QString pkexec_path;
};

#endif // PROGRAMMER_H
