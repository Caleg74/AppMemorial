import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1

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

            TextField {
                id: txtYear
                width: 200
                activeFocusOnPress: true
                style:textEditMGStyle
                placeholderText: "YYYY"
                font.pointSize: 15
            }


            // Row 2
            Text {
                id: eventName
                width: 100
                text: qsTr("Nome")
                font.pointSize: 15
            }

            TextField {
                id: txtName
                width: 400
                activeFocusOnPress: true
                style:textEditMGStyle
                placeholderText: "Memorial.."
                font.pointSize: 15
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
