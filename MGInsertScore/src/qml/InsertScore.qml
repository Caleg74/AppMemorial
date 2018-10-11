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


                StyleMGComboBox {
                    id: cbbGymnastSelection
                    objectName: "cbbGymnastSelection"
                    model: gymnastEventModel.comboList
                    width: parent.parent.width/2
//                    activeFocusOnPress: true
                    currentIndex: 0
                    signal selectedTextChanged(string currentTxt)
                    onCurrentTextChanged: {
                        selectedTextChanged(currentText)
                    }
                }

                StyleMGComboBox {
                    id: cbbAppartus
                    model: apparatusModel.comboList
                    width: parent.parent.width/10*4
//                    activeFocusOnPress: true
                    visible: cbbGymnastSelection.currentIndex > 0
                    currentIndex: 0
                }
            }

            Row
            {

                CheckBox {
                    id: chkFinalApparatus
                    text: "Attrezzo Finale"
                    style: CheckBoxStyle {

                    indicator: Rectangle {
                           implicitWidth: 24
                           implicitHeight: 24
                           radius: 3
                           border.color: control.activeFocus ? "grey" : "#0a3f60"
                           border.width: 2
                           Rectangle {
                               visible: control.checked
                               color: "#83d1f5"
                               border.color: "#0a3f60"
                               radius: 2
                               anchors.margins: 4
                               anchors.fill: parent
                           }
                   }

                   spacing: 10

                   label: Text {
                           renderType: Text.NativeRendering
                           font.pointSize: 15
                           color: "#0a3f60"
                           text: control.text
                         }
                    }
                }

                spacing: 20

                TextField {
                    id: txtStartScore
                    width: parent.parent.width/5
                    activeFocusOnPress: true
                    style:textEditMGStyle
                    placeholderText: "Start Score.."
                    font.pointSize: 15
                }

                TextField {
                    id: txtFinalScore
                    width: parent.parent.width/5
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
                                     string finalScore,
                                     bool finalApparatus)

                    enabled: (txtStartScore.text.length) && (txtFinalScore.text.length)
                             && (cbbGymnastSelection.currentIndex >= 0)
                             && (cbbAppartus.currentIndex >= 0)
                    onClicked: {
                        saveScore(cbbGymnastSelection.currentText,
                                  cbbAppartus.currentText,
                                  txtStartScore.text,
                                  txtFinalScore.text,
                                  chkFinalApparatus.checked)

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

