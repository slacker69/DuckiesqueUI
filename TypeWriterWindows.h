#ifndef TYPEWRITERWINDOWS_H
#define TYPEWRITERWINDOWS_H

#include <QObject>

#ifdef Q_OS_WINDOWS

#include <QDebug>

#include "TypeWriter.h"

class TypeWriterWindows: public TypeWriter
{
public:
    TypeWriterWindows();
    ~TypeWriterWindows();
    void type_key(QStringList keys);

private:
    void *display;
    unsigned char str2unicode(QString in);
};
#endif

#endif // TYPEWRITERWINDOWS_H
