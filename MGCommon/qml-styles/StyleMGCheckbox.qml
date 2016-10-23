import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Component {
    CheckBox {
        id:chkbox
        text: "control.text"

        style: CheckBoxStyle {

          indicator: Rectangle {
                  implicitWidth: 24
                  implicitHeight: 24
                  radius: 3
                  border.color: control.activeFocus ? "grey" : "#0a3f60"
                  border.width: 2
                  Rectangle {
                      visible: control.checked
                      color: "#83d1f5"
                      border.color: "#0a3f60"
                      radius: 2
                      anchors.margins: 4
                      anchors.fill: parent
                  }
          }

          spacing: 10

          label: Text {
                  font.pointSize: 15
                  text: control.text
                }
        }
    }
}
