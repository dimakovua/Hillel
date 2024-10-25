import QtQuick
import QtQuick.Controls
import MyModule

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "MVC Example with C++ Model"

    MyListModel
    {
        id: myModel
    }

    ListView
    {
        anchors.fill: parent
        model: myModel
        delegate: Item {
            width: parent.width
            height: 50

            Text{
                text: model.name
                font.pointSize: 20
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked: {
                    myModel.removeItem(index)
                }
            }
        }
    }

    TextField {
        id: inputField
        anchors.horizontalCenter: parent.horizontalCenter
        width: 200
        placeholderText: "Enter new item"
    }

    Button
    {
        text: "Add Item"
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            myModel.addItem(inputField.text)
            inputField.text = ""
        }
    }

}
