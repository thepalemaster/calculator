import QtQuick 2.0

Item {
    //width: 300
    //height: 120
    Text {
        id: name
        text: "Shape Name 0"
        font {
            pointSize: 23
        }
        color: Style.mainColor
    }

    Column {
        anchors.top: name.bottom
        spacing: 2
        InputField {
            id: one
            //width: 300
            //height: Style.buttonHeight / 2
        }
        InputField {
            id: two
            //width: 300
            //height: Style.buttonHeight / 2
        }
    }
}
