import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1

Item {
    width: parent.width
    height: parent.height


    Rectangle {
        height: parent.height
        width: parent.width
        id: root
        color: "#d0d0d0"
        anchors.fill: parent
//        opacity: 1 - backendHelper.opacity


        Rectangle {
            id: menTitleSpace
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
                TableTitleItem {
                    text: "Ginnasta"
                    fontSize: parent.fontSize
                    width: (parent.width / 18) * 5   // 5/18th th of the space
                    imageSource: "/images/Empty.svg" // no image, but reserve space
                }

                TableTitleItem {
                    text: "Totale"
                    fontSize: parent.fontSize
                    width: (parent.width / 18) * 13/7  // use 1/7th of the 13/18th available
                    imageSource: "/images/Sum.svg"
                }
                TableTitleItem {
                    text: "Suolo"
                    fontSize: parent.fontSize
                    width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
                    imageSource: "/images/Floor.svg"
                }
                TableTitleItem {
                    text: "Cavallo a\nmaniglie"
                    fontSize: parent.fontSize
                    width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
                    imageSource: "/images/PommelHorse.svg"
                }
                TableTitleItem {
                    text: "Anelli"
                    fontSize: parent.fontSize
                    width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
                    imageSource: "/images/Rings.svg"
                }
                TableTitleItem {
                    text: "Volteggio"
                    fontSize: parent.fontSize
                    width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
                    imageSource: "/images/Vault.svg"
                }
                TableTitleItem {
                    text: "Parallela"
                    fontSize: parent.fontSize
                    width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
                    imageSource: "/images/ParallelBars.svg"
                }
                TableTitleItem {
                    text: "Sbarra"
                    fontSize: parent.fontSize
                    width: (parent.width / 18) * 13/7 // use 1/7th of the 13/18th available
                    separatorVisible: false
                    imageSource: "/images/HorizontalBar.svg"
                }
//                TextField {
//                    id: txtLastName
//                    width: parent.parent.width/4 - 50
//                    activeFocusOnPress: true
//                    style:textEditMGStyle
//                    placeholderText: "Cognome.."
//                    font.pointSize: 15
//                }

//                ComboBox {
//                    id: cbbCountry
//                    model: countryListModel.comboList
//                    width: parent.parent.width/4 - 50
//                    activeFocusOnPress: true
//                    style:comboBoxMGStyle
//                    currentIndex: 0

////                    model: ListModel {
////                        id: cbbCountryItem
////                        ListElement { text: "Nazione.."}
////                        ListElement { text: "Svizzera" }
////                        ListElement { text: "Francia" }
////                        ListElement { text: "Italia" }
////                    }
//                }

//                ComboBox {
//                    id: cbbSex
//                    width: parent.parent.width/4 - 50
//                    activeFocusOnPress: true
//                    style:comboBoxMGStyle
//                    currentIndex: 0

//                    model: ListModel {
//                        id: cbbSexItem
//                        ListElement { text: "Sesso.."}
//                        ListElement { text: "M" }
//                        ListElement { text: "F" }
//                    }

//                    StyleMGPushButton {
//                        id:btnSort
//                        objectName: "btnSort"
//                        width: 100
//                        buttonText: "Sort"
//                    }
//                }

//                Item {
//                    id: btnAddGymnast
//                    objectName: "btnAddGymnast"

//                    width: 40 ; height: 40
//                    enabled: (txtFirstName.text.length) && (txtLastName.text.length)
//                            && (cbbCountry.currentIndex > 0) && (cbbSex.currentIndex > 0)
//                    Image {
//                        source: addMouseArea.pressed ? "qrc:images/add_icon_pressed.png" : "qrc:images/add_icon.png"
//                        anchors.centerIn: parent
//                        opacity: enabled ? 1 : 0.5
//                    }
//                    MouseArea {
//                        id: addMouseArea
//                        anchors.fill: parent
//                        onClicked: {
//                            GymnastDataModel.addItem(txtFirstName.text, txtLastName.text,
//                                                        cbbCountry.currentText, cbbSex.currentText)
//                            // remove fields for next input
//                            txtFirstName.text = ""
//                            txtLastName.text = ""
//                            cbbCountry.currentIndex = 0
//                            cbbSex.currentIndex = 0
//                        }
//                    }
                }
            }
        }

//        ScrollView {
//            width: parent.width
//            height: parent.height
//            anchors.top: addGymnastSpace.bottom
//            anchors.bottom: root.bottom

//            flickableItem.interactive: true

//            ListView {
//    //            width: 200; height: 250
//                id: listviewinput
//                model: GymnastDataModel
//                delegate: GymnastInfoDelegate { }
//                anchors.fill: parent
//                width: parent.width
//                clip: true

//                // Animations
//                add: Transition { NumberAnimation { properties: "y"; from:-50 ; duration: 500 } }
//                removeDisplaced: Transition { NumberAnimation { properties: "y"; duration: 150 } }
//                remove: Transition { NumberAnimation { property: "opacity"; to: 0; duration: 200 } }
//            }

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
//                        anchors.rightMargin: 4
//                        anchors.bottomMargin: 6
//                    }
//                }
//                scrollBarBackground: Item {
//                    implicitWidth: 14
//                    implicitHeight: 26
//                }
//            }
//        }
//    }


}

