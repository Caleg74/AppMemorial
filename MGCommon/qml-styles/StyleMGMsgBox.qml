import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

Item {
    id: root

    Dialog {
        id: messageDialog
        title: "Warning"
        modality: Qt.WindowModal
        objectName: "messageDialog"
        width: 400
        height: 120
        property string text: "my text"

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
}
