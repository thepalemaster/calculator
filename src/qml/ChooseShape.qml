import QtQuick 2.15
import ru.AreaCalc.ShapeModel 1.0

ListView {
    id: root
    signal setupShape (int id)
    spacing: 2
    model: ShapeModel{}
    delegate:
        StandartButton {
            //property int shapeID: shapeID
            width: root.width
            buttonName: shapeName
            onClicked: root.setupShape(shapeID);
        }
}
