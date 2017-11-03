import QtQuick 2.0
import QtQuick.Controls 1.4


Rectangle {
    TableView {
        id: userslist
        width : 400

        TableViewColumn {
            role: "username"
            title: "Username"
            width: 200

            delegate : Rectangle {
                width : 100
                height : 40
                border.color : "cyan"
                border.width: 1
                Text {
                    text : modelData["username"]
                }
            }
        }

        TableViewColumn {
            role: "password"
            title: "Password"
            width: 200

            delegate : Rectangle {
                width : 100
                height : 40
                border.color : "cyan"
                border.width: 1
                Text {
                    text : modelData["password"]
                }
            }
        }

        Connections {
            target: us
            onUsersListReceived: {
                userslist.model = users;
            }
        }
    }
}
