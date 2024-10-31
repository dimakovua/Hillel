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
            /*
                Реалізуйте додавання елементу до taskModel. 
                Використайте метод моделі append
                (Для поля date можете використати new Date().toLocaleString())
            */
            inputField.text = ""; // очищаємо поле введення після додавання
        }
    }

    function removeTask(index) {
        // Реалізуйте видалення завдання з моделі
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
            color: /* Нехай колір буде залежити від 
                    model.completed (світло зелений якщо виконано). 
                    Використайте тут тернарний оператор 
                    */
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
                        font.strikeout: model.completed
                    }
                    Text {
                        /*
                        Це текстове поле має виводити date з моделі
                        Хай це буде маленький текст сірого кольору
                        */
                    }
                }

                // Кнопка видалення
                Button {
                    /*
                    По кліку на цю кнопку має видалитися елемент
                    (Index це вже готова локальна змінна ListView)
                    */
                    Layout.alignment: Qt.AlignRight
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
            /*
            Текст на кнопці має бути Add Task
            По кліку кнопка бере поле текст з InputField
            та передає це у відповідну функцію додавання завдання
            */
            // text: "Add Task"
            // onClicked: addTask(inputField.text)
            Layout.fillWidth: true
        }
    }
}
