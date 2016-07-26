import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import OBDApplication 1.0

Item {
    property alias text: label.text
    property alias value: gauge.value
    property alias color: label.color
    property alias maximum: gauge.maximumValue

    Text {
        id: label
        color: "white"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        font.pixelSize: parent.height / 15
        horizontalAlignment: Text.AlignHCenter
    }

    CircularGauge {
        id: gauge
        anchors.fill: parent
        anchors.bottomMargin: parent.height / 15
        anchors.topMargin: 10
        maximumValue: 140
        minimumValue: 0
        antialiasing: true
        Behavior on value {
            NumberAnimation {
                id: animation
                duration: 500
            }
        }
    }
}
