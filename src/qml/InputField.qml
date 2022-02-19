import QtQuick 2.0

Rectangle {
   color: Style.backgroundColor
   border {
      color: Style.secondaryColor
      width: 1
   }
   Text {
       id: name
       color: Style.mainColor
       anchors.top: parent.top
       anchors.left: parent.left
       anchors.right: field.left
       text: "Custom Shape Name"
   }
   TextInput {
       id: field
       color: Style.mainColor
       width: parent.width / 3
       height: Style.buttonHeight
       anchors.top: parent.top
       anchors.bottom: parent.bottom
       anchors.right: parent.right
   }

}
