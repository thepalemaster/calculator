import QtQuick 2.0

Item {
    Rectangle {
        color: Style.backgroundColor
        border.color: Style.mainColor
        border.width: 1
        anchors.fill: parent
    }

    TextInput{
        color: Style.mainColor
        anchors.fill: parent
    }
}
