import QtQuick 2.0

Item {
    property bool checkBoxState: false
    property alias checkBoxName: name.text

    Rectangle {
        id: checkbox
        height: Style.buttonHeight / 2
        width: Style.buttonHeight / 2
        border {
            color: Style.mainColor
            width: 1
        }
        color: checkBoxState ? "red" : Style.backgroundColor
        MouseArea {
            anchors.fill: parent
            onClicked: checkBoxState = !checkBoxState
        }
    }
    Text {
        id: name
        anchors.left: checkbox.right
        anchors.margins: 10
        text: qsTr("text")
        color: Style.mainColor
    }
}
