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

    ChooseShape{
        id: chooser
        width: parent.width / 4
        anchors.right: parent.right
    }

    ResultList{
        id: list
        anchors.bottom: parent.bottom
        anchors.right: chooser.left
        anchors.left: parent.left
    }

    AreaViewer {
        id: view
        anchors.left: parent.left
        anchors.bottom: list.top
        anchors.right: chooser.left
    }

    ShapeInput{
        width: 50
        height: 100
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: chooser.left
        anchors.bottom: view.top
    }
}
