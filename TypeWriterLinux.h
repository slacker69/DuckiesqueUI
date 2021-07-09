#ifndef TYPEWRITERLINUX_H
#define TYPEWRITERLINUX_H

#include <QObject>

#ifdef Q_OS_LINUX

#include "TypeWriter.h"

class TypeWriterLinux: public TypeWriter
{
public:
    TypeWriterLinux();
    ~TypeWriterLinux();
    void type_key(QStringList keys);

private:
    void *display;
    quint16 str2unicode(QString in);
};
#endif

#endif // TYPEWRITERLINUX_H
