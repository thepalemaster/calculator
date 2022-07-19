import QtQuick 2.0
import ru.AreaCalc.InputView 1.0

Item{
    id: root
    //property int shapeID
    function setShape(shapeID) {
        viewer.setupShape(shapeID);
        input1.input = "";
        input2.input = "";
        input3.input = "";
        input4.input = "";
        check1.checkBoxState = false;
        check2.checkBoxState = false;
    }
    function calculate () {
        viewer.calculate(input1.input, input2.input, input3.input,
                         input4.input, check1.checkBoxState, check2.checkBoxState);
    }
    InputView {
        id: viewer
    }
    Column {
            spacing: 10
            Text {
                id: name
                width: root.width / 2
                text: viewer.shapeName
                font {
                    pointSize: 23
                }
                color: Style.mainColor
            }
            InputField {
                id: input1
                visible: !!viewer.field1
                fieldName: viewer.field1
                width: root.width / 2
                height: Style.buttonHeight / 2
            }
            InputField {
                id: input2
                visible: !!viewer.field2
                fieldName: viewer.field2
                width: root.width / 2
                height: Style.buttonHeight / 2
            }
            InputField {
                id: input3
                visible: !!viewer.field3
                fieldName: viewer.field3
                width: root.width / 2
                height: Style.buttonHeight / 2
            }
            InputField {
                id: input4
                visible: !!viewer.field4
                fieldName: viewer.field4
                width: root.width / 2
                height: Style.buttonHeight / 2
            }
            InputCheckBox {
                id: check1
                visible: !!viewer.option1
                checkBoxName: viewer.option1
                width: root.width / 2
                height: Style.buttonHeight / 2
            }
            InputCheckBox {
                id: check2
                visible: !!viewer.option2
                checkBoxName: viewer.option2
                width: root.width / 2
                height: Style.buttonHeight / 2
            }
    }
}
