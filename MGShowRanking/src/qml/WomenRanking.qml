import QtQuick
import QtQuick.Controls


Item {
//    width: parent.width
//    height: parent.height
    id: idWomenRanking
    objectName: "idWomenRanking"
    Rectangle {
//        height: parent.height
//        width: parent.width
        id: root
        color: "#d0d0d0"
        anchors.fill: parent
//        opacity: 1 - backendHelper.opacity


        Rectangle {
            id: womenTitleSpace
            y: 20
            height:  parent.height / 12
            width: parent.width - 14 // scroll bar size
            radius: 5
            border.width: 2
            border.color: "#0a3f60"
            color: "#fff"


            Item // some sort of a Row
            {
                property int apparatusWidth: parent.width / 7
                anchors.margins: 5
                anchors.fill: parent
//                height: parent.height
//                width: parent.width
                property int fontSize:  Math.max(parent.width / 100, 6)


                TableTitleItem {
                    id: gymnId
                    text: "Ginnasta"
                    fontSize: parent.fontSize
                    height: parent.height
                    imageSource: "/images/Empty.svg" // no image, but reserve space
                    anchors.left: parent.left
                    anchors.right: totId.left
                }

                TableTitleItem {
                    id: totId
                    text: "Totale"
                    fontSize: parent.fontSize
                    height: parent.height
                    width: parent.apparatusWidth
                    imageSource: "/images/Sum.svg"
                    anchors.right: vaultId.left
                }
                TableTitleItem {
                    id: vaultId
                    text: "Volteggio"
                    fontSize: parent.fontSize
                    height: parent.height
                    width: parent.apparatusWidth
                    imageSource: "/images/Vault.svg"
                    anchors.right: unBarsId.left
                }
                TableTitleItem {
                    id: unBarsId
                    text: "Parallele\nasimmetriche"
                    fontSize: parent.fontSize
                    height: parent.height
                    width: parent.apparatusWidth
                    imageSource: "/images/UnevenBars.svg"
                    anchors.right: balBeamId.left
                }
                TableTitleItem {
                    id: balBeamId
                    text: "Trave"
                    fontSize: parent.fontSize
                    height: parent.height
                    width: parent.apparatusWidth
                    imageSource: "/images/BalanceBeam.svg"
                    anchors.right: floorId.left
                }
                TableTitleItem {
                    id: floorId
                    text: "Suolo"
                    fontSize: parent.fontSize
                    height: parent.height
                    width: parent.apparatusWidth
                    imageSource: "/images/Floor.svg"
                    anchors.right: parent.right
                    separatorVisible: false
                }
            }
        }

        ScrollView {

            width: parent.width -14 // scroll bar size
            height: parent.height
            anchors.top: womenTitleSpace.bottom
            anchors.bottom: root.bottom

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff

            ListView {
    //            width: 200; height: 250
                id: rankingview
                model: AllroundWomenDataModel
                delegate: AllroundWDelegate { }
//                anchors.fill: parent
                width: parent.width
                spacing: 2

                // Animations
//                add: Transition { NumberAnimation { properties: "y"; from:-50 ; duration: 500 } }
//                removeDisplaced: Transition { NumberAnimation { properties: "y"; duration: 150 } }
//                remove: Transition { NumberAnimation { property: "opacity"; to: 0; duration: 200 } }
            }

//            style: ScrollViewStyle {
//                transientScrollBars: true
//                handle: Item {
//                    implicitWidth: 14
//                    implicitHeight: 26
//                    Rectangle {
//                        color: "grey"
//                        anchors.fill: parent
//                        anchors.topMargin: 6
//                        anchors.leftMargin: 4
//                        anchors.rightMargin: -4
//                        anchors.bottomMargin: 6
//                    }
//                }
//                scrollBarBackground: Item {
//                    implicitWidth: 14
//                    implicitHeight: 26
//                }
//            }

        }
    }
 }

