import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Particles 2.0

Item {
    property string rank;
    property string nameFull;
    property int fontSize: 15;

    width: parent.width
    height: parent.height

    Item {  // some sort of a Row
//        width: parent.width
//        height: parent.height
        anchors.fill: parent
        anchors.margins: 10

        Text {
            id: rankId
            text: parent.parent.rank
            font.bold: true
            font.pointSize: fontSize
            color: "#0a3f60"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            width: 30
            height: parent.height
            anchors.left: parent.left
        }

        Text {
            id: fullnameId
            text: parent.parent.nameFull
            font.pointSize: fontSize
            color: "#0a3f60"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            height: parent.height
            anchors.left: rankId.right
            anchors.right: separator.left
        }

        Rectangle {
            id: separator
            width: 2    // just a line
            height: parent.height
            color: "#d0d0d0"
            anchors.right: parent.right
        }
    }
}
