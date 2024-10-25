#pragma once

#include <QAbstractListModel>
#include <QStringList>

class MyListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles
    {
        NameRole = Qt::UserRole + 1
    };

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        return roles;
    }

    QVariant data(const QModelIndex &index, int role) const override
    {
        if(!index.isValid() || index.row() >= m_items.size())
        {
            return QVariant();
        }

        if(role == NameRole)
        {
            return m_items.at(index.row());
        }

        return QVariant();
    }

    MyListModel(QObject* parent = nullptr) : QAbstractListModel(parent)
    {
        m_items = {"Item 1", "Item 2", "Item 3"};
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        Q_UNUSED(parent);
        return m_items.size();
    }




    Q_INVOKABLE void addItem(const QString& item)
    {
        beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
        m_items.append(item);
        endInsertRows();
    }

    Q_INVOKABLE void removeItem(int index)
    {
        if(index < 0 || index >= m_items.size())
            return;

        beginRemoveRows(QModelIndex(), index, index);
        m_items.removeAt(index);
        endRemoveRows();
    }

private:
    QStringList m_items;
};
