import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import OBDApplication 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Power Meter")

    property alias gaugeValue: gauge.value
    property alias labelText: label.text
    property alias labelColor: label.color
    property alias animationDuration: animation.duration
    property alias logText: textArea.text

    StackView {

        id: stackView
        initialItem: mainView
        anchors.fill: parent

        Rectangle {
            id: logView

            Button {
                width: parent.width
                id: backButton
                text: "<"
                onClicked: stackView.pop()
            }

            TextArea {
                id: textArea
                anchors.bottom: parent.bottom
                anchors.top: backButton.bottom
                anchors.left: parent.left
                width: parent.width
                readOnly: true
                onTextChanged: function() {
                    __verticalScrollBar.value = __verticalScrollBar.maximumValue
                }
            }
        }

        Rectangle {
            id: mainView
            color: "black"

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: stackView.push(logView)
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

                style: CircularGaugeStyle {
                    id: style
                    minimumValueAngle: -90
                    maximumValueAngle: 180
                    tickmarkLabel: Text {
                        font.pixelSize: Math.max(6, outerRadius * 0.1)
                        text: styleData.value
                        antialiasing: true
                        color: styleData.value >= 130 ? "#e34c22" : "#e5e5e5"
                    }
                }

                Behavior on value {
                    NumberAnimation {
                        id: animation
                        duration: 500
                    }
                }
            }
        }
    }
}
