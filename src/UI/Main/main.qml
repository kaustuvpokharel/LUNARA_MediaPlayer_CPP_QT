import QtQuick
import QtQuick.Controls
import "../Pages"
import LUNARA 1.0

Window {
    width: 1920
    height: 1080
    visible: true
    title: qsTr("LUNARA")

    Component.onCompleted:
    {
        App.tryAutoLogin();
    }

    StackView
    {
        id: pageLoader
        anchors.fill: parent
        initialItem: login
    }


    Component
    {
        id: login
        Login
        {
            onLoginSuccess:{
                pageLoader.replace(upload)
            }

        }
    }

    Component
    {
        id: upload
        Upload
        {

        }
    }
}
