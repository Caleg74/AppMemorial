import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Particles 2.0

Item {
    property string rank;
    property string nameFull;
    property int fontSize: 15;

    width: parent.width
    height: parent.height

    Row {

        width: parent.width
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter


        Text {
            id: rankId
            text: parent.parent.rank
            font.bold: true
            font.pointSize: fontSize
            color: "#0a3f60"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            width: parent.width * 1 / 10
            height: parent.height
        }

        Text {
            id: fullnameId
            text: parent.parent.nameFull
            font.pointSize: fontSize
            color: "#0a3f60"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            width: parent.width * 2 / 10
            height: parent.height
        }

        Rectangle {
            id: separator
            width: 2    // just a line
            height: parent.height - 5
            color: "#d0d0d0"
        }
    }
}
