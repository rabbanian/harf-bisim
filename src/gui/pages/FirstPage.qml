import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Pane {
    id: page

    Column {
        spacing: 4
        anchors.centerIn: parent

        Label {
            text: "Enter a valid Playpod test host"
        }

        TextField {
            id: hostIP
            placeholderText: "Host"
        }

        TextField {
            id: hostPort
            placeholderText: "Port"
        }

        Button {
            text: "Connect"
            property alias load: inidicator

            onClicked: {
                this.text = "";
                this.enabled = false;
                this.load.visible = true;
                root.connectClickSignal(hostIP.text, hostPort.text);
            }

            BusyIndicator {
                id: inidicator
                visible: false
                anchors.fill: parent
                anchors.centerIn: parent
            }
        }
    }
}
