#include "helpfield.h"
#include <QPainter>

HelpField::HelpField()
{
    setFixedSize(300, 50);
    m_text = "Score: 0\nPause == space";
}

// Реализация метода paintEvent для рисования текста
void HelpField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    // Создаем объект QPainter, который рисует на нашем виджете
    QPainter painter(this);

    // Устанавливаем цвет текста
    painter.setPen(QColor(250, 250, 250));  // Белый цвет для текста
    painter.setFont(QFont("Arial", 12, QFont::Bold));  // Настроим шрифт

    // Отрисовываем текст по центру виджета
    painter.drawText(rect(), Qt::AlignCenter, m_text);
}

// Слот для изменения текста
void HelpField::ChangeTextSlot(QString text)
{
    m_text = text;  // Обновляем текст
    repaint();  // Перерисовываем виджет, чтобы текст обновился
}


