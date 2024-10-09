#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>

class AppCore : public QObject
{
    Q_OBJECT
public:
    explicit AppCore(QObject *parent = nullptr);
    //counter
    Q_PROPERTY(int counter READ getCounter NOTIFY onCounterChanged FINAL)
    int getCounter() const;
    Q_INVOKABLE void upCounter();
    Q_INVOKABLE void resetCounter();
    //....



signals:
    void onCounterChanged();

private:
    int m_counter = 0;
};

#endif // APPCORE_H
