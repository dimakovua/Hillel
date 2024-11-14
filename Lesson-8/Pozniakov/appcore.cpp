#include "appcore.h"

AppCore::AppCore(QObject *parent) : QObject(parent), m_counter(0)
{
}

int AppCore::getCounter() const
{
    return m_counter;
}

void AppCore::upCounter()
{
    ++m_counter;
    emit onCounterChanged();
}

void AppCore::resetCounter()
{
    m_counter = 0;
    emit onCounterChanged();
}
