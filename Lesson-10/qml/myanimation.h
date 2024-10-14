#ifndef MYANIMATION_H
#define MYANIMATION_H

#include <QObject>

class MyAnimation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int posX READ posX WRITE setPosX NOTIFY posXChanged)

public:
    explicit MyAnimation(QObject *parent = nullptr);

    int posX() const { return m_posX; }
    void setPosX(int newPosX) {
        if (m_posX != newPosX) {
            m_posX = newPosX;
            emit posXChanged();
        }
    }

    Q_INVOKABLE void moveRight() {
        setPosX(m_posX + 20);  // При кожному виклику зміщуємо об'єкт на 20 пікселів праворуч
    }

signals:
    void posXChanged();

private:
    int m_posX = 0;  // Початкова координата по X
};

#endif // MYANIMATION_H
