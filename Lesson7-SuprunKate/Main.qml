import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "To-Do List MVC"

    // Модель завдань
    ListModel {
        id: taskModel
    }

    function addTask(taskName) {
        if (taskName.trim() !== "") {
               var dateAdded = new Date().toLocaleString(); // Дата та час виконання
               taskModel.append({ name: taskName, completed: false, date: dateAdded });
               inputField.text = ""; // очищаємо поле введення після додавання
        }
    }

    function removeTask(index) {
        if (index >= 0 && index < taskModel.count) {
           taskModel.remove(index); // Видалення завдання з моделі
    }
}
    // Вивід
    ListView {
        id: taskListView
        width: parent.width
        height: parent.height - 150
        model: taskModel
        spacing: 10

        delegate: Rectangle {
            width: parent.width
            height: 50
            color: model.completed ? "lightgreen" : "lightgrey"
            border.color: "lightgrey"
            border.width: 1
            radius: 5

            RowLayout {
                anchors.fill: parent
                spacing: 10

                CheckBox {
                    checked: model.completed
                    onCheckedChanged: model.completed = checked

                }

                ColumnLayout {
                    Text {
                        text: model.name
                        font.pixelSize: 16
                        font.strikeout: model.completed // Перекреслений текст для виконаних завдань
                        Layout.alignment: Qt.AlignVCenter
                        color: model.completed ? "black" : "red"
                    }
                    Text {
                        text: model.date // Дата додавання
                        font.pixelSize: 12
                        color: "lightgrey"
                    }
                }

                // Кнопка видалення
                Button {
                    text: "Delete"
                    onClicked: removeTask(index)// По кліку на цю кнопку має видалитися елемент
                    Layout.alignment: Qt.AlignCenter
                }
            }
        }
    }

    // Панель для додавання нових завдань
    ColumnLayout {
        anchors.bottom: parent.bottom
        width: parent.width
        spacing: 10

        TextField {
            id: inputField
            placeholderText: "Enter new task"
            Layout.fillWidth: true
        }

        Button {
            text: "Add Task"
            onClicked: addTask(inputField.text) // Додаємо нове завдання
            Layout.fillWidth: true
        }
    }
}
