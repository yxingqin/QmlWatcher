import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 1.4
import QtQuick.Controls 2.4 as Ctrl2
import QtQuick.Layouts 1.11
//import Qt.labs.platform 1.1

ApplicationWindow {
    id: _window
    visible: true
    flags: Qt.Window | Qt.WindowSystemMenuHint
           | Qt.WindowTitleHint | Qt.WindowMinimizeButtonHint
           | Qt.WindowMaximizeButtonHint | Qt.WindowCloseButtonHint
           | Qt.WindowStaysOnTopHint
    width: 600
    height: 800
    title: qsTr("Qml watcher")
    property bool isWindow: false

//    QtObject {
//        id:_theme
//        property color background: "#262728"
//        property color reserverColor: "#fff"
//        property color textColor:  "#FFF"
//    }

    //保存大小
    property point _geo: Qt.point(0, 0)
    property point _size: Qt.point(100, 100)

    function _printLoadingMessage(msg) {
        var str = `${(new Date()).toTimeString().split(' ')[0]}: ${msg}`;
        console.log(`<b style='color: blue;'>${str}</b>`);
    }
    function _start() {
        $Engine.watch(_mainQmlInput.text)
        _printLoadingMessage("load qmlfile :" + _mainQmlInput.text);
        _loader.source = "";
        $Engine.clearCache();
        _loader.setSource(`file:///${$Engine.absQmlPath}`);
    }
    function _reload() {
        _printLoadingMessage("Reloading ...");
        var	s = _loader.source;
        if(isWindow&&_loader.status == Loader.Ready)
        {
            _geo.x = _loader.item.x;
            _geo.y = _loader.item.y;
            _size.x = _loader.item.width;
            _size.y = _loader.item.height;
        }
        _loader.source = "";
        $Engine.clearCache();
        if(isWindow)
            _loader.setSource(s, {"flags": flags, "x": _geo.x, "y": _geo.y, "width": _size.x, "height": _size.y});
        else
            _loader.setSource(s);
    }
//    menuBar: MenuBar {
//        Menu {
//            title:qsTr("Setting")
//            MenuItem {
//                text: qsTr("QmlImportPath")
//                onTriggered: {
//                   // folderDialog.open();
//                }
//            }
//        }
//    }
   ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        RowLayout {
            Layout.fillWidth: true
            Ctrl2.TextField {
                id: _mainQmlInput
                Layout.fillWidth: true
                placeholderText: qsTr("Main qml file path")
                selectByMouse: true
            }
            Ctrl2.Button {
                text: qsTr("Load")
                onClicked:{
                    _start();
                }
            }
        }
        SplitView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            orientation: Qt.Vertical
            Rectangle {
                id:_loader_win
                objectName: "_loader_win"
                height: parent.height/4*3
                Text {
                    anchors.centerIn: parent
                    text:"Live QML Window"
                    color:"black"
                    font.pixelSize:24
                }
                Loader {
                    id: _loader
                    asynchronous: true
                    anchors.fill:parent
                    onLoaded: {

                        _loader_win.visible=_loader.item instanceof Item;
                        isWindow=! _loader_win.visible;
                        if(isWindow){
                            _loader.item.flags= _window.flags;
                        }
                    }
                }
            }
            Ctrl2.ScrollView {
                id: _scrollView
                Layout.fillWidth: true
                Layout.fillHeight: true
                Ctrl2.TextArea {
                    id: _console
                    objectName: "_console"
                    background: Rectangle {
                        radius: 2
                        border.color: focus ? "#41adff" : "#ababab"
                    }
                    textFormat: "RichText"
                    wrapMode: "Wrap"
                    selectByMouse: true
                    selectedTextColor: "white"
                    readOnly: true
                    onTextChanged: _scrollView.scrollToButtom()

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.RightButton
                        onClicked: _menu.popup()

                        Menu {
                            id: _menu
                            MenuItem {
                                text: qsTr("Clear All")
                                onTriggered: _console.text = ""
                            }
                        }
                    }
                }
                function scrollToButtom() {
                    Ctrl2.ScrollBar.vertical.position = 1 - Ctrl2.ScrollBar.vertical.size;
                }
            }
        }
    }
   DropArea {
       anchors.fill: parent
       onDropped: {
           if (drop.hasUrls) {
               _mainQmlInput.text = drop.urls[0].replace("file:///", "");
               _start()
           }
       }
   }

}
