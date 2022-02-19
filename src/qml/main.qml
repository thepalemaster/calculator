import QtQuick 2.15
import QtQuick.Window 2.1
import "."

Window {
    id: root
    width: 640
    height: 480
    visible: true
    color: Style.backgroundColor
    title: qsTr("Hello World")

    Calculator {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: counter.top
        anchors.margins: 10
    }
    ShapeCounter {
        id: counter
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }
}
