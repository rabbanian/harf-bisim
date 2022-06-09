import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Pane {
    id: page

    Column {
        spacing: 4
        anchors.centerIn: parent

        Button {
            text: "Push to talk"
            onPressed: root.captureStartSignal()
            onReleased: root.captureStopSignal()
        }
    }
}
