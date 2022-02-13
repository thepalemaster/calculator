import QtQuick 2.15

Column {
    spacing: 2
    Repeater {
        model: 5
        ShapeButton{
            width: parent.width
            height: Style.buttonHeight
        }
    }
}
