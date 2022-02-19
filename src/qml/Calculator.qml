import QtQuick 2.0

Rectangle {
    color: Style.backgroundColor

    border {
        color: Style.mainColor
        width: 1
    }

    ChooseShape{
        id: chooser
        width: parent.width / 4
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 5
    }

    /*
    ResultList{
        id: list
        anchors.bottom: parent.bottom
        anchors.right: chooser.left
        anchors.left: parent.left
        anchors.margins: 5
    }
    */

    AreaViewer {
        id: view
        anchors.left: parent.left
        //anchors.bottom: list.top
        anchors.right: chooser.left
        anchors.bottom: parent.bottom
        //anchors.margins: 5
    }

    ShapeInput{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: chooser.left
        //anchors.bottom: view.top
    }
}
