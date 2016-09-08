import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Particles 2.0

Item {
    property string text;
    property bool separatorVisible: true;
    property string imageSource;
    property int fontSize: 15;

    width: parent.width
    height: parent.height

    Row {
        anchors.margins: 10
        anchors.centerIn: parent

        Text {
            id: name
            text: parent.parent.text
            font.pointSize: fontSize
            color: "#0a3f60"
            width: parent.parent.width - 40
            anchors.verticalCenter: parent.verticalCenter
        }

        Image {
            source: imageSource
            sourceSize.width: fontSize * 3
            sourceSize.height: fontSize * 3
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            width: 2    // just a line
            height: parent.height - 5
            anchors.verticalCenter: parent.verticalCenter
            color: "#d0d0d0"
            visible: separatorVisible
        }
    }
}
