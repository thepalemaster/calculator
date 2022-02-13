import QtQuick 2.0

Rectangle {
        color: Style.backgroundColor
        border {
            color: Style.mainColor
            width: 1
        }
        Text {
            id: name
            text: qsTr("Shape with parems 01234!" + index)
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            color: Style.mainColor
        }
}
