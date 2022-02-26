import QtQuick 2.0

Item {
    //width: 300
    //height: 120
    id: main
    Text {
        id: name
        width: main.width / 2
        text: "Shape Name 0"
        font {
            pointSize: 23
        }
        color: Style.mainColor
    }

    Column {
        anchors.top: name.bottom
        spacing: 10
        InputField {
            id: one
            width: main.width / 2
            height: Style.buttonHeight / 2
        }
        InputField {
            id: two
            width: main.width / 2
            height: Style.buttonHeight / 2
        }
    }
}
