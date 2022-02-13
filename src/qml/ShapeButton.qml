import QtQuick 2.0

Rectangle {
    color: Style.backgroundColor
    border {
        color: Style.mainColor
        width: 1
    }
    MouseArea {
        anchors.fill: parent
    }
    Text {
        id: name
        anchors.centerIn: parent
        text: qsTr("SHAPE " + index)
        color: Style.mainColor
    }
}
