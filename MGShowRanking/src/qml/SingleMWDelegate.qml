import QtQuick 2.0

Item {
    id: singleMDelegate
    width: parent.width
    height: 50

    Rectangle {
        y: 20
        height:  parent.height
        width: parent.width
        radius: 5
        border.width: 2
        border.color: "#0a3f60"
        color: "#fff"


        Item // some sort of a Row
        {
            property int apparatusWidth: parent.width / 2.5
            anchors.margins: 5
            anchors.fill: parent
//            height: parent.height
//            width: parent.width
            property int fontSize:  Math.max(parent.width / 33, 6)


            GymnastPosItem {
                id: rankId
                rank: Rank           // roleName
                nameFull: NameFull   // roleName
                flagImage: FlagImage // roleName
                fontSize: parent.fontSize
                anchors.left: parent.left
                anchors.right: singleScoreMId.left
            }


            ApparatusScoreItem {
                id: singleScoreMId
                startScore: StartScore_SingleMW  // roleName
                finalScore: FinalScore_SingleMW  // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                separatorVisible: false
                anchors.right: parent.right
            }
        }
    }
}
