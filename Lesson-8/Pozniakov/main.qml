import QtQuick
import QtQuick.Controls
import QtQuick.Shapes

ApplicationWindow {
    visible: true
    width: 700
    height: 400
    title: qsTr("Lesson-8")


    Row {
        anchors.centerIn: parent
        spacing: 25

        Rectangle {
            width: 100
            height: 50
            border.width: 1
            border.color: "#778899"
            color: "#F8F8FF"

            Label {
                anchors.centerIn: parent
                font.pixelSize: 25
                text: appCore.counter
            }
        }

        Button {
            width: 100
            height: 50
            text: "Up Counter!"
            font.pixelSize: 15
            background: Rectangle {
                border.width: 1
                border.color: "#778899"
                color: "#F8F8FF"
                radius: 2
            }
            onClicked: appCore.upCounter()
        }
    }

    Shape {
        id:treangle1
        width:100
        height: 100

        x: 100
        y: 100
        ShapePath {
            strokeWidth: 2
            fillColor:   "#DCDCDC"
            PathMove { x: 0;      y: 0 }
            PathLine { x: 0;    y: 100 }
            PathLine { x: 90;     y: 50 }
            PathLine { x: 0;      y: 0 }
        }
    }
    Rectangle {
        width: 100
        height: 50
        anchors.right: parent.right
        anchors.top: parent.top
        Rectangle {
            width: parent.width
            height: parent.height / 2
            anchors.top: parent.top
            color: "blue"
        }
        Rectangle {
            width: parent.width
            height: parent.height / 2
            anchors.bottom: parent.bottom
            color: "yellow"
        }
    }
}



