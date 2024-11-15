import QtQuick
import QtQuick.Controls.Basic

CheckBox {
    id: control
    text: qsTr("CheckBox")
    checked: false

    indicator: Rectangle {
        implicitWidth: 30
        implicitHeight: 30
        x: control.leftPadding
        y: (parent.height / 2) - (height / 2)
        radius: 3
        border.color: control.down ? "grey" : "#0a3f60"

        Rectangle {
            width: 20
            height: 20
            x: 5
            y: 5
            radius: 2
            color: control.down ? "grey" : "#0a3f60"
            visible: control.checked
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: "#0a3f60"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
