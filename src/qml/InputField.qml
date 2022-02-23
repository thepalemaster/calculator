import QtQuick 2.0

Row {
    spacing: 10
    Text {
        id: name
        color: Style.mainColor
        //width: parent.width / 2
        //anchors.top: parent.top
        //anchors.left: parent.left
        //anchors.horizontalCenter: parent.horizontalCenter
        text: "Custom Shape Name"
    }
    Rectangle {
        color: "gray"
        border {
            color: Style.mainColor
            width: 1
            
        }
        width: parent.width
        height: parent.height / 2
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
