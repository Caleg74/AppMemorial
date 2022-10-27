import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1

Item {
    width: parent.width
    height: parent.height

    property string finalScore;
    property bool gymnastDefined;

    function resetValues() {
        txtDifficultyScore.text = "0.000"
        txtExecutionScore.text = "0.000"
        txtFinalScore.text = "0.000"
        txtPenaltyScore.text = "0.000"
    }

    function floatToString(num, precision) {
        var str;
        str = num.toFixed(Math.min(precision-1, num.toString().substr(num.toString().indexOf(".")+1).length));
        str = str.slice(0, (str.indexOf(".")) + precision + 1);
        str = str.padEnd(str.indexOf(".") + precision, '0')
        return str;
    }

    function calcFinalScore() {
        var precision = 4;
        if (gymnastDefined)
        {
            var fFinalScore = ( parseFloat(txtDifficultyScore.text.replace(",", "."))
                              + parseFloat(txtExecutionScore.text.replace(",", "."))
                              - parseFloat(txtPenaltyScore.text.replace(",", ".")))

            finalScore = floatToString(fFinalScore, precision);

//            console.log(fFinalScore)
//            console.log(finalScore)

            if (finalScore === "NaN")
            {
                // format error
                finalScore = "Error"
            }
            txtFinalScore.text = finalScore
        }
    }

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
            }

            Row{
                spacing: 20

                StyleMGComboBox {
                    id: cbbAppartus
                    model: apparatusModel.comboList
                    width: parent.parent.width/10*4
//                    activeFocusOnPress: true
//                    visible: cbbGymnastSelection.currentIndex > 0
                    currentIndex: 0

                    onCurrentIndexChanged: {
                        if (currentIndex != 0)
                        {
                            gymnastDefined = true
                            console.log("gymnastDefined = true")
                        }
                        else
                        {
                            gymnastDefined = false
                            console.log("gymnastDefined = false")
                            resetValues()
                        }
                    }
                }

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
            }

            Row
            {
                spacing: 10

                Text {
                    width: 160
                    text: "Difficoltà"
                    renderType: Text.NativeRendering
                    font.pointSize: 15
                    color: "#0a3f60"
                  }

                TextField {
                    id: txtDifficultyScore
                    width: parent.parent.width/5
                    activeFocusOnPress: true
                    style:textEditMGStyle
//                    placeholderText: "0.000"
                    text: "0.000"
                    font.pointSize: 15
                    onTextChanged: calcFinalScore()
                }

                Text {
                    width: 160
                    text: "+  Esecuzione"
                    renderType: Text.NativeRendering
                    font.pointSize: 15
                    color: "#0a3f60"
                  }

                TextField {
                    id: txtExecutionScore
                    width: parent.parent.width/5
                    activeFocusOnPress: true
                    style:textEditMGStyle
//                    placeholderText: "0.000"
                    text: "0.000"
                    font.pointSize: 15
                    onTextChanged: calcFinalScore()
                }
            }

            Row {
                spacing: 10

                Text {
                    width: 160
                    text: "-  ev. Penalità"
                    renderType: Text.NativeRendering
                    font.pointSize: 15
                    color: "#0a3f60"
                  }

                TextField {
                    id: txtPenaltyScore
                    width: parent.parent.width/5
                    activeFocusOnPress: true
                    style:textEditMGStyle
//                    placeholderText: "0.000"
                    text: "0.000"
                    font.pointSize: 15
                    onTextChanged: calcFinalScore()
                }
            }

            Row {
                spacing: 20

                TextField {
                    id: txtFinalScore
                    width: parent.parent.width/5
                    height: 40
                    activeFocusOnPress: false
                    readOnly: true
                    style:textEditMGStyle
                    text: finalScore
                    font.pointSize: 15
                    font.bold: true
                }

                StyleMGPushButton {
                    id:btnSaveScore
                    objectName: "btnSaveScore"
                    width: 110
                    height: 40
                    buttonText: "Registra"
                    signal saveScore(string gymnastName,
                                     string apparatus,
                                     string startScore,
                                     string finalScore,
                                     bool finalApparatus)

                    enabled: (txtDifficultyScore.text.length) && (txtExecutionScore.text.length)
                             && (cbbGymnastSelection.currentIndex >= 0)
                             && (cbbAppartus.currentIndex >= 0)
                    onClicked: {
                        saveScore(cbbGymnastSelection.currentText,
                                  cbbAppartus.currentText,
                                  txtDifficultyScore.text,
                                  txtFinalScore.text,
                                  chkFinalApparatus.checked)

                        resetValues()
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

