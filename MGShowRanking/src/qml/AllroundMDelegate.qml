import QtQuick 2.0

Item {
    id: allroundMDelegate
    width: parent.width
    height: 45

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
            property int fontSize:  Math.max(parent.width / 90, 6)


            GymnastPosItem {
                id: rankId
                rank: Rank           // roleName
                nameFull: NameFull   // roleName
                flagImage: FlagImage // roleName
                fontSize: parent.fontSize
                anchors.left: parent.left
                anchors.right: totId.left
            }

            ScoreItem {
                id: totId
                finalScore: FinalScore_Total  // roleName
                //startScore: StartScore_Total  // roleName
                isFinalApparatus: false
                latestScore: false
                fontSize: parent.fontSize
                fontBold: true
                width: parent.apparatusWidth
                anchors.right: floorId.left
            }

            ScoreItem {
                id: floorId
                startScore: StartScore_Floor  // roleName
                finalScore: FinalScore_Floor  // roleName
                isFinalApparatus: FinalApparatus_Floor // roleName
                latestScore: LatestScore_Floor         // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                anchors.right: phorseId.left
            }

            ScoreItem {
                id: phorseId
                startScore: StartScore_PHorse  // roleName
                finalScore: FinalScore_PHorse  // roleName
                isFinalApparatus: FinalApparatus_PHorse // roleName
                latestScore: LatestScore_PHorse         // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                anchors.right: ringsId.left
            }

            ScoreItem {
                id: ringsId
                startScore: StartScore_Rings  // roleName
                finalScore: FinalScore_Rings  // roleName
                isFinalApparatus: FinalApparatus_Rings // roleName
                latestScore: LatestScore_Rings         // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                anchors.right: vaultId.left
            }

            ScoreItem {
                id: vaultId
                startScore: StartScore_Vault  // roleName
                finalScore: FinalScore_Vault  // roleName
                isFinalApparatus: FinalApparatus_Vault // roleName
                latestScore: LatestScore_Vault         // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                anchors.right: pbarsId.left
            }

            ScoreItem {
                id: pbarsId
                startScore: StartScore_ParallelBars  // roleName
                finalScore: FinalScore_ParallelBars  // roleName
                isFinalApparatus: FinalApparatus_ParallelBars // roleName
                latestScore: LatestScore_ParallelBars         // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                anchors.right: hbarId.left
            }

            ScoreItem {
                id: hbarId
                startScore: StartScore_HBar  // roleName
                finalScore: FinalScore_HBar  // roleName
                isFinalApparatus: FinalApparatus_HBar // roleName
                latestScore: LatestScore_HBar         // roleName
                fontSize: parent.fontSize
                width: parent.apparatusWidth
                separatorVisible: false
                anchors.right: parent.right
            }
        }
    }
}
