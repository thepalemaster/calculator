import QtQuick 2.0

Rectangle {
    height: Style.buttonHeight
    color: Style.backgroundColor
    Text {
        color: Style.mainColor
        text: "Area: 3,14159"
        font {
            pointSize: 23
        }
        anchors.centerIn: parent
    }
}
