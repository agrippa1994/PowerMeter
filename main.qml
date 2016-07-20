import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Extras 1.4

Window {
    color: "black"
    visible: true
    width: 640
    height: 480
    title: qsTr("Power Meter")

    property alias gaugeValue: gauge.value
    property alias labelText: label.text
    property alias labelColor: label.color

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        id: label
        color: "white"
        anchors.bottom: mouseArea.bottom
        anchors.bottomMargin: 10
        anchors.left: mouseArea.left
        anchors.leftMargin: 10
        font.pixelSize: mouseArea.height / 15
    }

    CircularGauge {
        id: gauge
        anchors.fill: parent
        anchors.bottomMargin: mouseArea.height / 15
        anchors.topMargin: 10
        maximumValue: 140
        minimumValue: 0
        antialiasing: true

        Behavior on value {
            NumberAnimation {
                duration: 500
            }
        }
    }
}
