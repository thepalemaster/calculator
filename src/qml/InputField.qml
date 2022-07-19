import QtQuick 2.0

Item {
    property alias fieldName: name.text
    property alias input: field.text
    Text {
        id: name
        anchors.left: parent.left
        color: Style.mainColor
        anchors.top: parent.top
        text: ""
    }
    Rectangle {
        height: parent.height
        width: parent.width / 2
        anchors.left: name.right
        anchors.margins: 10
        color: "steelblue"
        border {
            color: Style.mainColor
            width: 1
        }
        TextInput {
            id: field
            color: Style.mainColor
            maximumLength: 18
            horizontalAlignment: TextInput.AlignHCenter
            verticalAlignment: TextInput.AlignVCenter
            anchors.fill: parent
        }
    }
}
