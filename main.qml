import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3
import OBDApplication 1.0
import "./"

Window {
    visible: true
    width: 640
    height: 480
    title: "Power Meter"

    property alias gaugeValue: powerGauge.value
    property alias labelText: powerGauge.text
    property alias labelColor: powerGauge.color
    property alias speedValue: speedGauge.value
    property bool menuVisible: false

    // Transition between views
    Behavior on menuVisible {
        NumberAnimation {
            target: menu
            property: "opacity"
            duration: 250
            from: menuVisible ? 1.0 : 0.0
            to: menuVisible ? 0.0 : 1.0
        }
    }

    MouseArea {
        id: mainView
        anchors.fill: parent
        onClicked: menuVisible = true

        // Background image
        Image {
            anchors.fill: parent
            fillMode: Image.Tile
            source: "qrc:/img/background.png"
        }

        RowLayout {
            anchors.fill: parent
            spacing: 5

            // Left margin
            Rectangle { width: 5 }

            GaugeView {
                id: powerGauge
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
                maximum: menu.maxPower
                onValueChanged: text = value.toFixed(0).toString() + " PS"
            }

            GaugeView {
                id: speedGauge
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
                maximum: menu.maxSpeed
                onValueChanged: text = value.toFixed(0).toString() + " km/h"
            }

            // Right margin
            Rectangle { width: 5 }
        }
    }

    MainMenu {
        id: menu
        anchors.fill: parent
        gaussSource: mainView
        visible: opacity > 0 // Show whenever opacity is set
        opacity: 0.0
        onClose: menuVisible = false
    }
}
