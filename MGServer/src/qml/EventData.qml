import QtQuick
import QtQuick.Controls

Item {
    width: parent.width
    height: parent.height


    Rectangle {
        height: parent.height
        width: parent.width
        id: root
        color: "#d0d0d0"
        anchors.fill: parent
//        opacity: 1 - backendHelper.opacity

        Grid
        {
            columns: 2
            anchors.verticalCenter: parent.verticalCenter
            spacing: 20

            // Row 1
            Text {
                id: eventYear
                width: 100
                text: qsTr("Anno")
                font.pointSize: 15
            }

            StyleMGTextInput {
                id: txtYear
                width: 200
                activeFocusOnPress: true
                placeholderText: "YYYY"
            }


            // Row 2
            Text {
                id: eventName
                width: 100
                text: qsTr("Nome")
                font.pointSize: 15
            }

            StyleMGTextInput {
                id: txtName
                width: 400
                activeFocusOnPress: true
                placeholderText: "Memorial.."
            }

            // Row 3
            Text {
                id: idCreatePdf
                width: 100
                text: qsTr("Classifiche")
                font.pointSize: 15
            }

            StyleMGPushButton {
                id:btnCreatePdf
                objectName: "btnCreatePdf"
                width: 100
                buttonText: "Crea PDF"
            }
        }
    }
}
