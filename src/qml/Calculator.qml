import QtQuick 2.0

Rectangle {
    color: Style.backgroundColor
    id: calc
    border {
        color: Style.mainColor
        width: 1
    }

    ChooseShape{
        id: chooser
        anchors.right: calc.right
        anchors.top: calc.top
        anchors.margins: 5
        width: calc.width / 4
        height: calc.height - Style.buttonHeight - anchors.margins - 5
    }

    CommandButtons {
        id: command
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: chooser.left
        anchors.top: view.bottom
        anchors.margins: 5
    }

    AreaViewer {
        id: view
        anchors.left: parent.left
        anchors.right: chooser.left
        anchors.top: input.bottom
        anchors.margins: 5
    }

    ShapeInput{
        id: input
        width: parent.width - chooser.width
        height: parent.height / 2
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: chooser.left
        anchors.margins: 5
    }
}
