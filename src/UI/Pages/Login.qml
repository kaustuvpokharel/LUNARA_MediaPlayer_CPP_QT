import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import LUNARA 1.0

Item
{
    id: root

    property string email: ""
    property string password: ""

    signal loginSuccess()

    Connections
    {
        target: App
        function onLoginSuccessful()
        {
            return root.loginSuccess()
        }
    }

    Rectangle
    {
        id: background
        anchors.fill: parent
        color: "#121727"
    }

    ColumnLayout
    {
        anchors.centerIn: parent
        spacing: 35
        Rectangle
        {
            id: logo
            width: 80
            height: 80
            radius: 10
            color: "#262B38"
            border.color: "#404349"
            border.width: 1
            Layout.alignment: Qt.AlignHCenter

            Rectangle
            {
                width: 30
                height: 30
                radius: 5
                color: "#f2f2f2"
                anchors.centerIn: parent
            }
        }

        Text {
            id: lunara
            text: qsTr("LUNARA")
            color: "#f2f2f2"
            font.pixelSize: 60
            Layout.alignment: Qt.AlignHCenter
            // Layout.topMargin: -25
        }

        Text {
            id: title2
            text: qsTr("Professional Video Player")
            color: "#f2f2f2"
            opacity: 0.5
            font.pixelSize: 20
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: -30
        }

        Rectangle
        {
            id: loginArea
            width: 350
            height: 370
            color: "#262B38"
            radius: 10
            border.color: "#404349"
            border.width: 1
            Layout.alignment: Qt.AlignHCenter

            ColumnLayout
            {
                anchors.centerIn: parent
                spacing: 20
                Text {
                    id: welcome
                    text: qsTr("Welcome Back")
                    font.pixelSize:25
                    color: "#f2f2f2"
                    Layout.alignment: Qt.AlignHCenter
                }

                Text {
                    id: signIndescription
                    text: qsTr("Sign in to access your video library")
                    font.pixelSize: 15
                    color: "#f2f2f2"
                    opacity: 0.5
                    Layout.alignment: Qt.AlignHCenter
                    Layout.topMargin: -20
                }

                Rectangle
                {
                    id: emailArea
                    width: 300
                    height: 40
                    radius: 10
                    color: "#40444E"
                    border.color: "#404349"
                    border.width: 1
                    Layout.alignment: Qt.AlignHCenter

                    TextField {
                        id: emailText
                        placeholderText: "Email"
                        font.pixelSize: 15
                        color: "#f2f2f2"
                        anchors.fill: parent
                        anchors.margins: 8
                        background: null
                        onTextChanged: email = text
                    }
                }

                Rectangle
                {
                    id: passwordArea
                    width: 300
                    height: 40
                    radius: 10
                    color: "#40444E"
                    border.color: "#404349"
                    border.width: 1
                    Layout.alignment: Qt.AlignHCenter

                    TextField
                    {
                        id: passwordText
                        placeholderText: "Password"
                        font.pixelSize: 15
                        color: "#f2f2f2"
                        anchors.fill: parent
                        anchors.margins: 8
                        background: null
                        echoMode: TextInput.Password
                        onTextChanged: password = text
                    }
                }

                RowLayout
                {
                    CheckBox
                    {
                        id: rememberMe
                        text: "Remember me"
                        checked: false
                        onCheckedChanged: App.setRemember(checked)
                    }

                    Item {
                        Layout.fillWidth: parent
                    }

                    Text {
                        id: forgetPassword
                        text: qsTr("Forget password?")
                        font.pixelSize: 12
                        color: "#f2f2f2"
                    }
                }

                Rectangle
                {
                    id: signInBtn
                    width: 300
                    height: 40
                    radius: 10
                    color: "red"
                    Layout.alignment: Qt.AlignHCenter

                    Text {
                        text: qsTr("Sign In")
                        font.pixelSize: 17
                        color: "#f2f2f2"
                        anchors.centerIn: parent
                    }

                    MouseArea
                    {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor

                        onClicked:
                        {
                            console.log("Sigin button clicekd!")
                            App.login(email, password);
                            // pageLoader.replace(upload)
                        }
                    }
                }
            }
        }
    }

}
