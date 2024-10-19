import QtQuick 2.15
import QtQuick.Controls 2.15
import CustomComponents 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Click counter"

    Rectangle {
            anchors.fill: parent
            color: "black"

    Counter {
        id: counter
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        Text {
            id: countLabel
            color: "violet"
            text: "Current value: " + counter.value
            font.pixelSize: 20
        }

        Button {
            text: "Click me :)"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: counter.addOne()
            background: Rectangle {
                                color: "violet"
                                radius: 2
            }
         }
      }
   }
}
