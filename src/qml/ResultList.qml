import QtQuick 2.0

Column {
    spacing: 2
    Repeater {
        model: 7
        ShapeView {
            width: parent.width
            height: Style.buttonHeight
        }
    }
}
