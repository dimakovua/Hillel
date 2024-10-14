#pragma once

#include <QObject>

class Counter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

public:
     explicit Counter(QObject *parent = nullptr) : QObject(parent), m_count(0) {}

     int count() const { return m_count; }

     void setCount(int count)
     {
         if(m_count != count)
         {
             m_count = count;
             emit countChanged();
         }
     }

    Q_INVOKABLE void increment()
     {
         setCount(m_count + 1);
     }
 private:
     int m_count;

 signals:
     void countChanged();
};
