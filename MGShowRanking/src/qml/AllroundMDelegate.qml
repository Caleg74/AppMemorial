import QtQuick 2.0

Item {
    id: allroundMDelegate
    width: parent.width
    height: 50

    Rectangle {
        width: parent.width
        y: 50
        height:  parent.height / 12
        radius: 5
        border.width: 2
        border.color: "#0a3f60"
        color: "#fff"


        Row
        {
            anchors.margins: 10
            anchors.fill: parent
            property int fontSize: Math.max(parent.width / 100, 8)

            GymnastPosItem {
                rank: Rank          // roleName
                nameFull: NameFull  // role name
                fontSize: parent.fontSize
                width: (parent.width / 18) * 5   // 5/18th th of the space
            }

            TotalScoreItem {
                finalScore: FinalScore_Total
                fontSize: parent.fontSize
                width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
            }

            ApparatusScoreItem {
                startScore: StartScore_Floor  // roleName
                finalScore: FinalScore_Floor  // roleName
                fontSize: parent.fontSize
                width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
            }

            ApparatusScoreItem {
                startScore: StartScore_PHorse  // roleName
                finalScore: FinalScore_PHorse  // roleName
                fontSize: parent.fontSize
                width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
            }

            ApparatusScoreItem {
                startScore: StartScore_Rings  // roleName
                finalScore: FinalScore_Rings  // roleName
                fontSize: parent.fontSize
                width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
            }

            ApparatusScoreItem {
                startScore: StartScore_Vault  // roleName
                finalScore: FinalScore_Vault  // roleName
                fontSize: parent.fontSize
                width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
            }

            ApparatusScoreItem {
                startScore: StartScore_ParallelBars  // roleName
                finalScore: FinalScore_ParallelBars  // roleName
                fontSize: parent.fontSize
                width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
            }

            ApparatusScoreItem {
                startScore: StartScore_HBar  // roleName
                finalScore: FinalScore_HBar  // roleName
                fontSize: parent.fontSize
                width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
                separatorVisible: false
            }
        }
    }
}
