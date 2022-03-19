import QtQuick 2.0

Rectangle {
    id: button
    property string buttonName: "No Name"
    color: Style.backgroundColor
    height: Style.buttonHeight

    border {
        color: Style.mainColor
        width: 1
    }
    Text {
        anchors.fill: button
        text: button.buttonName
        color: Style.mainColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
    }
    MouseArea {
        anchors.fill: button
    }
}
