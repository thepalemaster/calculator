import QtQuick 2.0


Rectangle {
    color: Style.backgroundColor
    id: shapelist
    signal closeList
    border {
        color: Style.mainColor
        width: 1
    }
    StandartButton {
        buttonName: "Back"
        onClicked:{
            shapelist.closeList()
        }
        
    }
    ListView {
        model: 5
        delegate: ShapeView
        anchors.fill: parent
        
    }

}
