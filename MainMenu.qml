import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

GridView {
    id: menu
    visible: menuVisible
    anchors.centerIn: parent

    GridLayout {
        anchors.centerIn: parent
        columns: 2

        Button {
            text: "Neu verbinden"
            onClicked: function() {
                menuVisible = false
                application.reconnect()
            }
        }

        Button {
            text: "Zurück"
            onClicked: menuVisible = false
        }
    }
}
