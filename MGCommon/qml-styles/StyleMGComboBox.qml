import QtQuick 2.6
import QtQuick.Controls 2.1

ComboBox {
    id: control
    font.pointSize: 15

    delegate: ItemDelegate {
        width: control.width
        contentItem: Text {
            text: modelData
            color: "#0a3f60"
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        highlighted: control.highlightedIndex === index
    }

    indicator: Canvas {
        id: canvas
        x: control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2
        width: 12
        height: 8
        contextType: "2d"

//        Connections {
//            target: control
//            onPressedChanged: canvas.requestPaint()
//        }

        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            context.fillStyle = control.pressed ? "white" : "#0a3f60"
            context.fill();
        }
    }

    contentItem: Text {
        leftPadding: 4
        rightPadding: control.indicator.width + control.spacing

        text: control.displayText
        font: control.font
        color: control.pressed ? "white" : "#0a3f60"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: 40
        border.color: control.pressed ? "#83d1f5" : "#0a3f60"
        border.width: control.visualFocus ? 4 : 2
        radius: 5
    }

    popup: Popup {
        y: control.height - 1
        width: control.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            border.color: "#0a3f60"
            radius: 5
        }
    }
}

