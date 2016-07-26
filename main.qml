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
    title: qsTr("Power Meter")




    property alias gaugeValue: powerGauge.value
    property alias labelText: powerGauge.text
    property alias labelColor: powerGauge.color

    property alias throttleValue: throttleGauge.value
    property alias speedValue: speedGauge.value
    property bool menuVisible: false

    // Transition between views
    Behavior on menuVisible {
        ParallelAnimation {
            NumberAnimation {
                target: mainView
                property: "opacity"
                duration: 250
                easing.type: Easing.InExpo
                from: menuVisible? 0.0 : 1.0
                to: menuVisible? 1.0 : 0.0
            }

            NumberAnimation {
                target: menu
                property: "opacity"
                duration: 250
                easing.type: Easing.InExpo
                from: menuVisible? 1.0 : 0.0
                to: menuVisible? 0.0 : 1.0
            }
        }
    }

    MouseArea {
        id: mainView
        anchors.fill: parent
        onClicked: menuVisible = true

        Row {
            anchors.fill: parent
            spacing: 5

            Gauge {
                id: throttleGauge
                height: parent.height
                value: 100
                Behavior on value {
                    NumberAnimation {
                        duration: 200
                    }
                }
            }

            GaugeView {
                id: powerGauge
                height: parent.height
                width: parent.width / 2 - throttleGauge.width / 2 - parent.spacing
                onValueChanged: function() {
                    if(powerGauge.value > 130)
                        powerGauge.color = "red";
                    else if(powerGauge.value > 100)
                        powerGauge.color = "yellow"
                    else
                        powerGauge.color = "white";

                    powerGauge.text = value.toFixed(0).toString() + " PS"
                }
            }

            GaugeView {
                id: speedGauge
                height: parent.height
                width: parent.width / 2 - throttleGauge.width / 2 - parent.spacing
                maximum: 200
                onValueChanged: function() {
                    if(speedGauge.value > 130)
                        speedGauge.color = "red";
                    else if(speedGauge.value > 100)
                        speedGauge.color = "yellow"
                    else
                        speedGauge.color = "white";

                    speedGauge.text = value.toFixed(0).toString() + " km/h"
                }
            }
        }
    }

    MainMenu {
        id: menu
        anchors.fill: parent
        visible: menuVisible
    }
}
