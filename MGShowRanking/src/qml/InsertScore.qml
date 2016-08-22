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

        Row
        {
            spacing: 10
            anchors.centerIn: parent
            anchors.verticalCenter: parent.verticalCenter


            ComboBox {
                id: cbbGymnast
                model: gymnastModel.comboList
                width: parent.parent.width/4
                activeFocusOnPress: true
                style:comboBoxMGStyle
                currentIndex: 0
            }

            TextField {
                id: txtStartScore
                width: parent.parent.width/4
                activeFocusOnPress: true
                style:textEditMGStyle
                placeholderText: "Start Score.."
                font.pointSize: 15
            }

            TextField {
                id: txtFinalScore
                width: parent.parent.width/4
                activeFocusOnPress: true
                style:textEditMGStyle
                placeholderText: "Start Score.."
                font.pointSize: 15
            }
        }
    }
}

