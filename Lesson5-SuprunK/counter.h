#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject {
    Q_OBJECT
    Q_PROPERTY(int value READ value NOTIFY valueChanged)

public:
    explicit Counter(QObject *parent = nullptr) : QObject(parent), m_value(0) {}

    int value() const { return m_value; }

public slots:
    void addOne() {
        m_value++;
        emit valueChanged();
    }

signals:
    void valueChanged();

private:
    int m_value;
};

#endif
