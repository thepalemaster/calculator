import QtQuick 2.15
import ru.AreaCalc.ShapeModel 1.0

ListView {
    spacing: 2
    model: ShapeModel{}
    delegate:
        StandartButton {
            width: parent.width
            buttonName: display
        }
}
