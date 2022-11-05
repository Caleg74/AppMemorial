import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Particles 2.0

Item {
    id: root
    property string finalScore;
    property string difficultyScore;
    property bool separatorVisible: true;
    property int fontSize: 15;
    property bool fontBold: false;
    property bool isFinalApparatus: false;
    property bool latestScore

    width: parent.widthh
    height: parent.height

    onLatestScoreChanged: {
        if (latestScore) {
            scoreBackground.gradient = grad
        } else {
            scoreBackground.gradient = null
        }
   }

    Item {  // some sort of a Row
//        width: parent.width
//        height: parent.height
        anchors.fill: parent
        anchors.margins: 5

        Rectangle {
            id: scoreBackground
            width: parent.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
//            anchors.margins: 10
            anchors.left: parent.left
            anchors.right: separator.right
//            color: latestScore ? "#8083d1f5" : "white"
            radius: 5
            Gradient { // enabled or disabled depending on "latestScore"Changed" value
                  id: grad
                  GradientStop { position: 0.0; color: "#4083d1f5" }
                  GradientStop { position: 1.0; color: "#A083d1f5" }
            }

            Text {
                id: finalScore
                renderType: Text.NativeRendering
                text: root.finalScore
                font.pointSize: fontSize
                font.bold: fontBold
                font.italic: isFinalApparatus
                color:  "#0a3f60"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
//                width: parent.width - difficultyScore.width - separator.width
                height: parent.height
                anchors.left: parent.left
                anchors.right: difficultyScore.left
            }

            Text {
                id: difficultyScore
                renderType: Text.NativeRendering
                text: root.difficultyScore // root.difficultyScore !== "0" ? "("+ root.difficultyScore +")" : ""
                font.pointSize: fontSize * 3/4
                font.bold: false
                font.italic: isFinalApparatus
                color:  "#0a3f60"
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                width: parent.width * 2 /5
                height: parent.height
                anchors.right: parent.right
            }
        }
        Rectangle {
            id: separator
            width: 2    // just a line
            height: parent.height
            color: "#d0d0d0"
            visible: separatorVisible
            anchors.right: parent.right
        }
    }
}
