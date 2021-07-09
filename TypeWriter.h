#ifndef TYPEWRITER_H
#define TYPEWRITER_H

#include <QObject>

class TypeWriter
{
public:
    virtual void type_key(QStringList keys) = 0;
};

#endif // TYPEWRITER_H
