import QtQuick
import QtQuick.Controls

Item {
    width: parent.width
    height: parent.height

    property string finalScore : "0.000";
    property bool gymnastDefined;
    property int nbrOfReferees : 4;

    function resetValues() {
        txtDifficultyScore.text = "0.000"
        txtExecutionScore.text = "0.000"
        txtFinalScore.text = "0.000"
        txtPenaltyScore.text = "0.000"
        txtAvgPenalty.text = "0.000"
        txtPenalty1.text = "0.000"
        txtPenalty2.text = "0.000"
        txtPenalty3.text = "0.000"
        txtPenalty4.text = "0.000"
        txtPenalty1.backColor = "white"
        txtPenalty2.backColor = "white"
        txtPenalty3.backColor = "white"
        txtPenalty4.backColor = "white"
    }

    function setExclBackground(score)
    {
        var penaltylist2 = [txtPenalty1, txtPenalty2, txtPenalty3, txtPenalty4]

        var i
        for (i=penaltylist2.length-1; i>=0; i--)
        {
            if (parseFloat(penaltylist2[i].text.replace(",", ".")) === parseFloat(score))
            {
                if (Qt.colorEqual(penaltylist2[i].backColor, "#ffffff"))
                {
                    penaltylist2[i].backColor = "#20ff0000"
                    break // exit for loop
                }
            }
        }
    }

    function sortPenaltyScores() {
        var precision = 4;
        // var penaltylist = [parseFloat(txtPenalty1.text.replace(",", ".")),
        //                    parseFloat(txtPenalty2.text.replace(",", ".")),
        //                    parseFloat(txtPenalty3.text.replace(",", ".")),
        //                    parseFloat(txtPenalty4.text.replace(",", "."))]

        var penaltylist1 = [parseFloat(txtPenalty1.text.replace(",", ".")),
                           parseFloat(txtPenalty2.text.replace(",", ".")),
                           parseFloat(txtPenalty3.text.replace(",", ".")),
                           parseFloat(txtPenalty4.text.replace(",", "."))]



        penaltylist1.sort()
        console.log(penaltylist1)

        txtPenalty1.backColor = "white"
        txtPenalty2.backColor = "white"
        txtPenalty3.backColor = "white"
        txtPenalty4.backColor = "white"
        setExclBackground(penaltylist1[0])
        setExclBackground(penaltylist1[3])

        txtAvgPenalty.text = floatToString((penaltylist1[1]+penaltylist1[2])/2, precision)

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
            if (nbrOfReferees == 2)
            {
                txtAvgPenalty.text = floatToString((parseFloat(txtPenalty1.text.replace(",", "."))
                                + parseFloat(txtPenalty2.text.replace(",", "."))) / 2, precision)
            }
            else if (nbrOfReferees == 4)
            {
                sortPenaltyScores()
            }

            txtExecutionScore.text = floatToString(10.000 - parseFloat(txtAvgPenalty.text), precision)

            var fFinalScore = ( parseFloat(txtDifficultyScore.text.replace(",", "."))
                              + parseFloat(txtExecutionScore.text.replace(",", "."))
                              - parseFloat(txtPenaltyScore.text.replace(",", ".")))

            finalScore = floatToString(fFinalScore, precision);

            //console.log(fFinalScore)

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
                        if (currentIndex !== 0)
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


                StyleMGCheckbox {
                    id: chkFinalApparatus
                    visible: false
                    text: "Attrezzo Finale"
                }
            }

            Row {
                Column {    // colonna 1
                    spacing: 10
                    Row {
                        spacing: 10
                        Text {
                            width: 120
                            text: "Difficoltà"
                            renderType: Text.NativeRendering
                            font.pointSize: 15
                            color: "#0a3f60"
                          }

                        StyleMGTextInput {
                            id: txtDifficultyScore
                            width: 100
                            activeFocusOnPress: true
        //                    style:textEditMGStyle
        //                    placeholderText: "0.000"
                            text: "0.000"
                            font.pointSize: 15
                            onTextChanged: calcFinalScore()
                            onFocusChanged:{
                                if(focus)
                                   selectAll()
                            }
                        }

                        Text {
                            width: 20
                            text: "  "  // just to create a space
                            renderType: Text.NativeRendering
                        }
                    }

                    Row {
                        spacing: 10
                        Text {
                            width: 120
                            text: "+  Esecuzione"
                            renderType: Text.NativeRendering
                            font.pointSize: 15
                            color: "#0a3f60"
                          }

                        StyleMGTextInput {
                            id: txtExecutionScore
                            width: 100
                            activeFocusOnPress: false
        //                    style:textEditMGStyle
        //                    placeholderText: "0.000"
                            text: "0.000"
                            readOnly: true
                            font.pointSize: 15
                        }
                    }

                    Row {
                        spacing: 10

                        Text {
                            width: 120
                            text: "-  ev. Penalità"
                            renderType: Text.NativeRendering
                            font.pointSize: 15
                            color: "#0a3f60"
                          }

                        StyleMGTextInput {
                            id: txtPenaltyScore
                            width: 100
                            activeFocusOnPress: true
        //                    style:textEditMGStyle
        //                    placeholderText: "0.000"
                            text: "0.000"
                            font.pointSize: 15
                            onTextChanged: calcFinalScore()
                            onFocusChanged:{
                                if(focus)
                                   selectAll()
                            }
                        }
                    }
                }

                Column {    // colonna 2
                    spacing: 10
                    Row {
                        spacing: 10

                        Text {
                            width: 80
                            text: "Media ded."
                            renderType: Text.NativeRendering
                            font.pointSize: 12
                            color: "#0a3f60"
                          }

                        StyleMGTextInput {
                            id: txtAvgPenalty
                            width: parent.parent.width/3
                            activeFocusOnPress: false
        //                    style:textEditMGStyle
        //                    placeholderText: "0.000"
                            text: "0.000"
                            readOnly: true
                            font.pointSize: 12
                            focus: false
                        }

                        Text {
                            width: 20
                            text: "  "  // just to create a space
                            renderType: Text.NativeRendering
                        }
                    }
                }

                Column {    // colonna 3
                    spacing: 10
                    Row {
                        spacing: 10

                        Text {
                            width: 120
                            text: "Deduzione 1"
                            renderType: Text.NativeRendering
                            font.pointSize: 15
                            color: "#0a3f60"
                          }

                        StyleMGTextInput {
                            id: txtPenalty1
                            width: 100
                            activeFocusOnPress: true
        //                    style:textEditMGStyle
        //                    placeholderText: "0.000"
                            text: "0.000"
                            font.pointSize: 15
                            onTextChanged: calcFinalScore()
                            onFocusChanged:{
                                if(focus)
                                   selectAll()
                            }
                        }
                    }

                    Row {
                        spacing: 10

                        Text {
                            width: 120
                            text: "Deduzione 2"
                            renderType: Text.NativeRendering
                            font.pointSize: 15
                            color: "#0a3f60"
                          }

                        StyleMGTextInput {
                            id: txtPenalty2
                            width: 100
                            activeFocusOnPress: true
        //                    style:textEditMGStyle
        //                    placeholderText: "0.000"
                            text: "0.000"
                            font.pointSize: 15
                            onTextChanged: calcFinalScore()
                            onFocusChanged:{
                                if(focus)
                                   selectAll()
                            }
                        }
                    }

                    Row {
                        id: rowReferee3
                        spacing: 10

                        Text {
                            width: 120
                            text: "Deduzione 3"
                            renderType: Text.NativeRendering
                            font.pointSize: 15
                            color: "#0a3f60"
                          }

                        StyleMGTextInput {
                            id: txtPenalty3
                            width: 100
                            activeFocusOnPress: true
        //                    style:textEditMGStyle
        //                    placeholderText: "0.000"
                            text: "0.000"
                            font.pointSize: 15
                            onTextChanged: calcFinalScore()
                            onFocusChanged:{
                                if(focus)
                                   selectAll()
                            }
                        }
                    }

                    Row {
                        id: rowReferee4
                        spacing: 10

                        Text {
                            width: 120
                            text: "Deduzione 4"
                            renderType: Text.NativeRendering
                            font.pointSize: 15
                            color: "#0a3f60"
                          }

                        StyleMGTextInput {
                            id: txtPenalty4
                            width: 100
                            activeFocusOnPress: true
        //                    style:textEditMGStyle
        //                    placeholderText: "0.000"
                            text: "0.000"
                            font.pointSize: 15
                            onTextChanged: calcFinalScore()
                            onFocusChanged:{
                                if(focus)
                                   selectAll()
                            }
                        }
                    }
                }
            }

            Row {
                spacing: 20

                StyleMGTextInput {
                    id: txtFinalScore
                    width: parent.parent.width/5
                    activeFocusOnPress: false
                    readOnly: true
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
                                     string difficultyScore,
                                     string executionScore,
                                     string penaltyScore,
                                     string finalScore,
                                     bool finalApparatus)

                    enabled: (txtDifficultyScore.text.length) && (txtExecutionScore.text.length)
                             && (cbbGymnastSelection.currentIndex >= 0)
                             && (cbbAppartus.currentIndex >= 0)
                    onClicked: {
                        saveScore(cbbGymnastSelection.currentText,
                                  cbbAppartus.currentText,
                                  txtDifficultyScore.text,
                                  txtExecutionScore.text,
                                  txtPenaltyScore.text,
                                  txtFinalScore.text,
                                  chkFinalApparatus.checked)

                        resetValues()
                        cbbAppartus.currentIndex = 0


                    }
                }

            }
        }

        //************************************************************************************

        Popup {
            id: popup
            x: root.width-btnSettings.width-width-5
            y: btnSettings.height
            width: 250
            height: 160
            modal: true
            focus: true
            spacing: 10
            background: Rectangle {
                    color: "#e0e0e0"
                    border.color: "darkgrey"
                }
            enter: Transition {
                   NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: 300 }
               }
            exit: Transition {
                NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 300 }
            }
            Column {
                spacing: 10
                Row {
                    Text {
                        text: "Impostazioni:"
                        renderType: Text.NativeRendering
                        font.pointSize: 12
                        font.bold: true
                        color: "#0a3f60"
                      }
                }

                Row {
                    Text {
                        width: 150
                        text: "Numero giurati"
                        renderType: Text.NativeRendering
                        font.pointSize: 12
                        color: "#0a3f60"
                      }

                    StyleMGComboBox {
                        id: cbbRefereeNbr
                        objectName: "cbbGymnastSelection"
                        //model: gymnastEventModel.comboList
                        width: 40
                        font.pointSize: 12
                        model: ["2", "4"]
        //                    activeFocusOnPress: true
                        currentIndex: 0
                        signal selectedTextChanged(string currentTxt)
                        onCurrentTextChanged: {
                            selectedTextChanged(currentText)
                        }
                    }
                }

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    StyleMGPushButton {
                        id:btnSaveSettings
                        width: 70
                        height: 40
                        buttonText: "Chiudi"
                        onClicked: {
                            popup.close()
                        }
                    }
                }
            }
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
            onClosed: {
                if (cbbRefereeNbr.currentIndex === 0) // = 2 referrees
                {
                    nbrOfReferees = 2;
                    rowReferee3.visible = false;
                    rowReferee4.visible = false;
                }
                else if (cbbRefereeNbr.currentIndex === 1) // = 4 referres
                {
                    nbrOfReferees = 4;
                    rowReferee3.visible = true;
                    rowReferee4.visible = true;
                }

                resetValues()
            }
        }

        StyleMGMsgBox {
            visible: false
        }
        Button {
            id: btnSettings
            anchors.right: parent.right
            anchors.top: parent.top
            text: qsTr("...")
            font.bold: true
            font.pointSize: 18

            background: Rectangle {
                    color: parent.down ? "#bbbbbb" :
                            (parent.hovered ? "#d6d6d6" : "transparent")
            }
            onClicked: popup.open()
        }
    }
}

