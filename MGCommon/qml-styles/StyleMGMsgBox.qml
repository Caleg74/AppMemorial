import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal
//import QtQuick.Dialogs 1.0

Dialog {
    id: messageDialog
    objectName: "messageDialog"

    property string text: "my text"

    modal: true
    standardButtons: Dialog.Ok
    title: "Warning"
    anchors.centerIn: parent

    width: 400
    height: 200

    Row {
        spacing: 30
        anchors.horizontalCenter: parent.horizontalCenter
        Image {
            source: "qrc:/images/warning_32x32.png"
        }

        Text {
            text: messageDialog.text
            font.pointSize: 12
            color: "#0a3f60"
        }
    }
}
/*
Dialog {
    id: messageDialog
    title: "Warning"

    width: 400
    height: 120
    property string text: "my text"
    modal: true

    contentItem: Rectangle {
        color: "#d0d0d0"
        anchors.centerIn: parent

        Column
        {
            anchors.centerIn: parent
            spacing: 30
            Row {
                spacing: 30
                anchors.horizontalCenter: parent.horizontalCenter
                Image {
                    source: "qrc:/images/warning_32x32.png"
                }

                Text {
                    text: messageDialog.text
                    font.pointSize: 12
                    color: "#0a3f60"
                }
            }

            StyleMGPushButton {
                id:btnSaveScore
                width: 100
                buttonText: "Close"
                enabled: true
                anchors.horizontalCenter: parent.horizontalCenter

                onClicked: { messageDialog.visible = false }
            }
        }
    }
}

*/
