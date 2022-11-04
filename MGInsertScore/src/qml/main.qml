import QtQuick
import QtQuick.Window
import "qrc:/qml"

Window {
    id: window
    width: 800
    height: 500
    visible: true
    title: qsTr("Memorial Gander - Insert Score")

//    StyleMGCheckbox { id: checkboxMGStyle }
    StyleMGComboBox { id: comboBoxMGStyle}
//    StyleMGTextInput { id: textEditMGStyle}
    StyleMGPushButton { id: buttonMGStyle}

    Rectangle {
        property string title: "Registra \nGinnasti"
        anchors.fill: parent
        color: "#d0d0d0"

        InsertScore
        {
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
        }
    }
}
