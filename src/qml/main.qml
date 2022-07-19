import QtQuick 2.15
import QtQuick.Window 2.1
import QtQuick.Controls 2.1



Window {
    id: root
    width: 640
    height: 640
    visible: true
    color: Style.backgroundColor
    title: qsTr("Hello World")
    
    StackView {
        id: stack
        width: root.width
        height: root.height - counter.height
        anchors.top: root.top
        anchors.margins: 10
        initialItem: Item {
            anchors.fill: stack
            Calculator {
                id: calc
                anchors.fill: parent
                anchors.margins: 10
            }
        }
    }
    
    ShapeCounter {
        id: counter
        height: Style.buttonHeight / 2
        anchors.top: stack.bottom
        anchors.left: root.left
        //anchors.bottom: root.bottom
    }
}
