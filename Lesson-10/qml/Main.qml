import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 300
    height: 200
    title: "Лічильник на QML"

    Column {
        anchors.centerIn: parent
        spacing: 10

        Text {
            text: "Лічильник: " + counter.count
            font.pixelSize: 20
        }

        Button {
            text: "Збільшити"
            onClicked: counter.increment()
        }
    }
}
