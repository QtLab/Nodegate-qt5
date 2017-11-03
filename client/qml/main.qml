import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 740
    title: qsTr("Maquette reseau")

    Item {
        id: rootView
        anchors.fill: parent

        MyTableView {
            x: 150
            y: 50
        }

        Column {
            Button {
                text: "refresh"
                onClicked: us.list();
            }

            TextArea {
                id: username
                width: 85
                height: 30
            }

            TextArea {
                id: password
                width: 85
                height: 30
            }

            Button {
                text: "create user"
                onClicked: us.create(username.text, password.text);
            }

            TextArea {
                id: idUser
                width: 85
                height: 30
            }

            Button {
                text: "read user"
                onClicked: us.read(idUser.text);
            }

            Text {
                id: userInfo
                width: 85
                height: 30
            }

            Connections {
                target: us
                onUserReadReceived: {
                    userInfo.text = user.username;
                }
            }
        }
    }
}
