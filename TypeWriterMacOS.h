#ifndef TYPEWRITERMACOS_H
#define TYPEWRITERMACOS_H

#include <QObject>

#ifdef Q_OS_MACOS

#include <QDebug>

#include "TypeWriter.h"

class TypeWriterMacOS: public TypeWriter
{
public:
    TypeWriterMacOS();
    ~TypeWriterMacOS();
    void type_key(QStringList keys);

private:
    void *source;
    quint16 str2unicode(bool *mod, QString in);
};

#endif

#endif // TYPEWRITERMACOS_H
