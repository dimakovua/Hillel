#! env qml

import QtQuick 2.0
import QtQuick.Controls 2.15
import QtMultimedia 5.15

Timer {
    interval: 1000  // 1 секунда
    running: true
    repeat: true
    onTriggered: {
        console.log("Timer ticked")
    }
}

