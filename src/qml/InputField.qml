import QtQuick 2.0

Item {
    Text {
        id: name
        anchors.left: parent.left
        color: Style.mainColor
        anchors.top: parent.top
        text: "Custom Shape Name"
    }
    Rectangle {
        height: parent.height
        width: parent.width / 2
        anchors.left: name.right
        anchors.margins: 10
        //anchors.top: parent.top
        //anchors.bottom: parent.bottom
        color: "gray"
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
