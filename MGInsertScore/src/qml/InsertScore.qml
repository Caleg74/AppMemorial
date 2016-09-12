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
        anchors.leftMargin: 20

        Column
        {
            width: parent.width
            spacing: 40
            anchors.centerIn: parent

            Row
            {
                spacing: 20
//                anchors.verticalCenter: parent.verticalCenter


                ComboBox {
                    id: cbbGymnastSelection
                    objectName: "cbbGymnastSelection"
                    model: gymnastRegisteredModel.comboList
                    width: parent.parent.width/2
//                    activeFocusOnPress: true
                    style:comboBoxMGStyle
                    currentIndex: 0
                    signal selectedTextChanged(string currentTxt)
                    onCurrentTextChanged: {
                        selectedTextChanged(currentText)
                    }
                }

                ComboBox {
                    id: cbbAppartus
                    model: apparatusModel.comboList
                    width: parent.parent.width/3
                    activeFocusOnPress: true
                    style:comboBoxMGStyle
                    visible: cbbGymnastSelection.currentIndex > 0
                    currentIndex: 0
                }

            }

            Row
            {
                spacing: 20

                TextField {
                    id: txtStartScore
                    width: parent.parent.width/3
                    activeFocusOnPress: true
                    style:textEditMGStyle
                    placeholderText: "Start Score.."
                    font.pointSize: 15
                }

                TextField {
                    id: txtFinalScore
                    width: parent.parent.width/3
                    activeFocusOnPress: true
                    style:textEditMGStyle
                    placeholderText: "Final Score.."
                    font.pointSize: 15
                }

                StyleMGPushButton {
                    id:btnSaveScore
                    objectName: "btnSaveScore"
                    width: 100
                    buttonText: "Registra"
                    signal saveScore(string gymnastName,
                                     string apparatus,
                                     string startScore,
                                     string finalScore)

                    enabled: (txtStartScore.text.length) && (txtFinalScore.text.length)
                             && (cbbGymnastSelection.currentIndex >= 0)
                             && (cbbAppartus.currentIndex >= 0)
                    onClicked: {
                        saveScore(cbbGymnastSelection.currentText,
                                  cbbAppartus.currentText,
                                  txtStartScore.text,
                                  txtFinalScore.text)

                        txtStartScore.text = ""
                        txtFinalScore.text = ""
                        cbbAppartus.currentIndex = 0


                    }
                }
            }
        }

        StyleMGMsgBox {
            visible: false
        }
    }
}

