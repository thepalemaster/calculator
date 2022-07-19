import QtQuick 2.0

Item {
    id: root
    signal calculateCurrentInput
    StandartButton {
        id: calc
        buttonName: "Calculate"
        anchors.top: root.top
        width: root.width        
        onClicked: {
            root.calculateCurrentInput()
        }
    }
     
    Grid {
        id: commandGrid
        anchors {
            top: calc.bottom
            left: root.left
            right: root.right
            bottom: root.bottom
            margins: 5
        }
        width: root.width
        height: 300
        columns: 2
        spacing: 2
        property int actualWidth: width / 2//columns - spacing / (columns - 1)
        
        StandartButton {
            buttonName: "Reset"
            width: commandGrid.actualWidth
        }
        
        StandartButton {
            buttonName: "Copy"
            width: commandGrid.actualWidth
        }
        
        StandartButton {
            buttonName: "View List"
            width: commandGrid.actualWidth
        }
        
        StandartButton {
            buttonName: "Set Measure Units"
            width: commandGrid.actualWidth
        }
    }
}
