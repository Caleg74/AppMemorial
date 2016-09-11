import QtQuick 2.0

Item {
    id: allroundMDelegate
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
            property int apparatusWidth: parent.width / 10
            anchors.margins: 5
            anchors.fill: parent
//            height: parent.height
//            width: parent.width
            property int fontSize:  Math.max(parent.width / 100, 6)


            GymnastPosItem {
                id: rankId
                rank: Rank          // roleName
                nameFull: NameFull  // roleName
                fontSize: parent.fontSize
                anchors.left: parent.left
                anchors.right: totId.left
            }

            TotalScoreItem {
                id: totId
                finalScore: FinalScore_Total  // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                anchors.right: floorId.left
            }

            ApparatusScoreItem {
                id: floorId
                startScore: StartScore_Floor  // roleName
                finalScore: FinalScore_Floor  // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                anchors.right: phorseId.left
            }

            ApparatusScoreItem {
                id: phorseId
                startScore: StartScore_PHorse  // roleName
                finalScore: FinalScore_PHorse  // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                anchors.right: ringsId.left
            }

            ApparatusScoreItem {
                id: ringsId
                startScore: StartScore_Rings  // roleName
                finalScore: FinalScore_Rings  // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                anchors.right: vaultId.left
            }

            ApparatusScoreItem {
                id: vaultId
                startScore: StartScore_Vault  // roleName
                finalScore: FinalScore_Vault  // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                anchors.right: pbarsId.left
            }

            ApparatusScoreItem {
                id: pbarsId
                startScore: StartScore_ParallelBars  // roleName
                finalScore: FinalScore_ParallelBars  // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                anchors.right: hbarId.left
            }

            ApparatusScoreItem {
                id: hbarId
                startScore: StartScore_HBar  // roleName
                finalScore: FinalScore_HBar  // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                separatorVisible: false
                anchors.right: parent.right
            }
        }
    }
}
