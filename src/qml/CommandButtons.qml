import QtQuick 2.0

Grid {
    id: commandGrid
    columns: 2
    spacing: 5
    property int actualWidth: width / columns - spacing / (columns - 1)

    StandartButton {
        buttonName: "Reset"
        width: actualWidth
    }

    StandartButton {
        buttonName: "Copy"
        width: actualWidth
    }

    StandartButton {
        buttonName: "View List"
        width: actualWidth
    }

    StandartButton {
        buttonName: "Set Measure Units"
        width: actualWidth
    }
}
