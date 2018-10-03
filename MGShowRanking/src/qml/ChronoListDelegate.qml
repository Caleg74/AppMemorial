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
            property int colWidthUnit: parent.width / 14
            anchors.margins: 5
            anchors.fill: parent
//            height: parent.height
//            width: parent.width
            property int fontSize:  Math.max(parent.width / 120, 6)


            GeneralTxtItem {
                id: mwId
                generalText: MenWomen   // roleName
                fontSize: parent.fontSize
                width: parent.colWidthUnit * 2 / 3
                anchors.left: parent.left
            }

            GymnastPosItem {
                id: nameId
                nameFull: NameFull   // roleName
                flagImage: FlagImage // roleName
                fontSize: parent.fontSize
                width: parent.colWidthUnit * 4
                anchors.left: mwId.right
            }

            GeneralTxtItem {
                id: countryId
                generalText: Country   // roleName
                fontSize: parent.fontSize
                width: parent.colWidthUnit
                anchors.left: nameId.right
            }

            GeneralTxtItem {
                id: apparatusId
                generalText: Apparatus   // roleName
                fontSize: parent.fontSize
                width: parent.colWidthUnit * 3
                anchors.left: countryId.right
            }

            GeneralTxtItem {
                id: startScoreId
                generalText: StartScore   // roleName
                fontSize: parent.fontSize
                width: parent.colWidthUnit
                anchors.left: apparatusId.right
            }


            GeneralTxtItem {
                id: exeScoreId
                generalText: ExecutionScore   // roleName
                fontSize: parent.fontSize
                width: parent.colWidthUnit
                anchors.left: startScoreId.right
            }

            GeneralTxtItem {
                id: finalScoreId
                generalText: FinalScore   // roleName
                fontSize: parent.fontSize
                width: parent.colWidthUnit
                anchors.left: exeScoreId.right
            }

            GeneralTxtItem {
                id: gymnastTotId
                generalText: GymnastTotalScore   // roleName
                fontSize: parent.fontSize
                width: parent.colWidthUnit
                anchors.left: finalScoreId.right
            }

            GeneralTxtItem {
                id: rankId
                generalText: Rank   // roleName
                fontSize: parent.fontSize
                width: parent.colWidthUnit
                anchors.left: gymnastTotId.right
                anchors.right: parent.right
            }
        }
    }
}
