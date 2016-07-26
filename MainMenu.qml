import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

FastBlur {
    id: menu
    radius: 64
    cached: true

    property alias gaussSource: menu.source
    property alias maxPower: maxPower.value
    property alias maxSpeed: maxSpeed.value
    property real headerHeight: 50
    property real itemHeight: 40
    signal close()

    ColumnLayout {
        anchors.fill: parent

        // Header
        RowLayout {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.preferredHeight: headerHeight

            // Left margin
            Rectangle { Layout.preferredWidth: 10 }

            Text {
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignVCenter
                text: "Menü"
                color: "white"
                font.pixelSize: headerHeight / 2
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: headerHeight - 10
                Layout.preferredWidth: headerHeight - 10
                iconSource: "qrc:/img/delete.png"
                style: ButtonStyle {
                    background: Rectangle {
                        color: "transparent"
                        border.color: "#e74c3c"
                        border.width: 1
                        radius: 5
                    }
                }
                onClicked: menu.close()
            }

            // Right margin
            Rectangle { Layout.preferredWidth: 10 }
        }

        // Body
        GridLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            columns: 1

            Button {
                Layout.alignment: Qt.AlignCenter
                text: "Neu verbinden"
                style: ButtonStyle {
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 25
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#888"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                            GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                        }
                    }
                }
                onClicked: function() {
                    application.reconnect()
                    menu.close()
                }
            }

            RowLayout {
                Layout.preferredHeight: itemHeight
                Layout.alignment: Qt.AlignCenter

                // Left margin
                Rectangle { width: 10 }

                Text {
                    Layout.alignment: Qt.AlignVCenter
                    text: "Max. PS(" + maxPower.value + "): "
                    color: "white"
                }

                Slider {
                    Layout.fillWidth: true
                    id: maxPower
                    minimumValue: 100
                    maximumValue: 600
                    stepSize: 10
                    value: 140
                }

                // Right margin
                Rectangle { width: 10 }
            }

            RowLayout {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: itemHeight

                // Left margin
                Rectangle { width: 10 }

                Text {
                    text: "Max. Geschwindigkeit(" + maxSpeed.value +"): "
                    color: "white"
                }
                Slider {
                    Layout.fillWidth: true
                    id: maxSpeed
                    minimumValue: 100
                    maximumValue: 300
                    stepSize: 10
                    value: 200
                }

                // Right margin
                Rectangle { width: 10 }
            }
        }
    }
}
