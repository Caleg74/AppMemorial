import QtQuick
import QtQuick.Controls
//import QtQuick.Controls.Styles 1.4

TextField {
    id: control
    property alias backColor: idBackColor.color

    placeholderText: qsTr("Enter description")
    color: "#0a3f60"
    placeholderTextColor: "#83d1f5"
    font.pointSize: 15

    background: Rectangle {
        id: idBackColor
        color: {
            if (readOnly)
                "transparent";
            else
                "white" ;
        }
        border.width: 2
        border.color: "#0a3f60"
        radius: 5
    }
}

//Component {

//    TextField {
//        color: "#0a3f60"
//        placeholderTextColor: "#83d1f5"

//        background: Rectangle {
//            color: "#fff"
//            border.width: 2
//            border.color: "#0a3f60"
//            radius: 5
//        }
//    }

//    TextFieldStyle {
//        textColor: "#0a3f60"
//        placeholderTextColor: "#83d1f5"

//        background: Rectangle {
//            color: "#fff"
//            border.width: 2
//            border.color: "#0a3f60"
//            radius: 5
//        }
//    }
//}
