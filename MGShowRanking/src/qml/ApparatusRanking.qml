import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1

Item {
//    width: parent.width
//    height: parent.height
    id: idSingleRanking
    objectName: "idSingleRanking"

    Rectangle {

        id: rootM
        color: "#d0d0d0"
        height: parent.height
        width: parent.width / 2
        anchors.left: parent.left

//        opacity: 1 - backendHelper.opacity

        ApparatusRankingM {  // some sort of a Column
            width: (parent.width * 3 / 4)
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Rectangle {

        id: rootW
        color: "#d0d0d0"
        height: parent.height
        width: parent.width / 2
        anchors.right: parent.right

        ApparatusRankingW {  // some sort of a Column

            width: (parent.width * 3 / 4)
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}

