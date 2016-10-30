import QtQuick 2.0
import QtQuick.Controls 2.0
//import QtQuick.Particles 2.0

Item {
    property string rank;
    property string nameFull;
    property string flagImage;
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
            renderType: Text.NativeRendering
            text: parent.parent.rank
            font.bold: true
            font.pointSize: fontSize
            color: "#0a3f60"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            width: 40
            height: parent.height
            anchors.left: parent.left
        }

        Text {
            id: fullnameId
            renderType: Text.NativeRendering
            text: parent.parent.nameFull
            font.pointSize: fontSize
            color: "#0a3f60"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            height: parent.height
            anchors.left: rankId.right
        }

        Image {
            id: countryFlag
//            source: "qrc:/flags/ch.svg"
            source: parent.parent.flagImage
            width: parent.parent.height / 2
            sourceSize.width: width
            sourceSize.height: width
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: fullnameId.right
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
