import QtQuick 2.0

Grid {
    columns: 2
    spacing: 5
    Rectangle {
        width: parent.width / 2 - 5
        height: Style.buttonHeight
        color: Style.backgroundColor
        border {
            color: Style.mainColor
            width: 1
        }
        Text {
            anchors.centerIn: parent
            text: qsTr("Copy")
            color: Style.mainColor
       }
    }
    Rectangle {
        width: parent.width / 2 - 5
        height: Style.buttonHeight
        color: Style.backgroundColor
        border {
            color: Style.mainColor
            width: 1
        }
        Text {
            anchors.centerIn: parent
            text: qsTr("Reset")
            color: Style.mainColor
       }
    }
    Rectangle {
        width: parent.width / 2 - 5
        height: Style.buttonHeight
        color: Style.backgroundColor
        border {
            color: Style.mainColor
            width: 1
        }
        Text {
            anchors.centerIn: parent
            text: qsTr("View List")
            color: Style.mainColor
       }
    }
    Rectangle {
        width: parent.width / 2 - 5
        height: Style.buttonHeight
        color: Style.backgroundColor
        border {
            color: Style.mainColor
            width: 1
        }
        Text {
            anchors.centerIn: parent
            text: qsTr("Set measure units")
            color: Style.mainColor
       }
    }
}
