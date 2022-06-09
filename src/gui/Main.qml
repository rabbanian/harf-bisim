import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "pages"

Window {
    id: root
    width: 500
    height: 400
    visible: true
    property alias stack: stackView

    signal captureStartSignal()
    signal captureStopSignal()
    signal connectClickSignal(String host, String port)



    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: FirstPage {}
    }
}
