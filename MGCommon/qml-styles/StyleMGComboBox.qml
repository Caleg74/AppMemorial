import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Private 1.0

Component {
    ComboBoxStyle {
        id: comboBox
        background: Rectangle {
            id: rectCategory
            radius: 5
            border.width: 2
            border.color: "#0a3f60"
            color: "#fff"
        }

        label: Text {
            renderType: Text.NativeRendering
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 15
            color: "#0a3f60"
            text: control.currentText
        }

        // drop-down customization here
        property Component __dropDownStyle: MenuStyle {
            __maxPopupHeight: 600
            __menuItemType: "comboboxitem"


            frame: Rectangle {              // background
                color: "#fff"
                border.width: 2
                border.color: "#83d1f5"
                radius: 5
            }

            itemDelegate.label:             // an item text
                Text {
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 15
                color: styleData.selected ? "white" : "#0a3f60"
                text: styleData.text
            }

            itemDelegate.background: Rectangle {  // selection of an item
                radius: 2
                color: styleData.selected ? "#83d1f5" : "transparent"
            }

            __scrollerStyle: ScrollViewStyle { }
        }

        property Component __popupStyle: Style {
            property int __maxPopupHeight: 400
            property int submenuOverlap: 0

            property Component frame: Rectangle {
                width: (parent ? parent.contentWidth : 0)
                height: (parent ? parent.contentHeight : 0) + 2
                border.color: "#0a3f60"
                property real maxHeight: 500
                property int margin: 1
            }

            property Component menuItemPanel: Text {
                renderType: Text.NativeRendering
                text: "NOT IMPLEMENTED"
                color: "red"
                font {
                    pixelSize: 14
                    bold: true
                }
            }

            property Component __scrollerStyle: null
        }
    }
}
