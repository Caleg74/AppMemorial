import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

    Rectangle {
        id: button

        property color buttonColor: "lightblue"
        property color onHoverColor: "gold"
        property color borderColor: "white"
        property string label: "ciccio"

        signal buttonClick()

        Text {
            id: buttonLabel
            anchors.centerIn: parent
            text: label
        }

        onButtonClick: {
            console.log(buttonLabel.text + " clicked")
        }

        MouseArea{
            onClicked: buttonClick()
            hoverEnabled: true
            onEntered: parent.border.color = onHoverColor
            onExited:  parent.border.color = borderColor
        }

        // Determines the color of the button by using the conditional operator
        color: buttonMouseArea.pressed ? Qt.darker(buttonColor, 1.5) : buttonColor

    }
