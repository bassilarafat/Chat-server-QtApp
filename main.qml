import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Server side App")

    //connect to backend object server
    Connections{
        target: server
        //define a fun to connect to signal newNewMessage
        function onNewMessage(ba){
            listOfMessages.append({
                                      message: ba +""
                                  })
        }
    }

    ColumnLayout{
        anchors.fill: parent
        ListView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true
            model: ListModel{         //to view our messages from the client
                id:listOfMessages
                ListElement{
                    message :"here is my server ..welcome"
                }
            }
            //delegate to show our item in model
            delegate: ItemDelegate{
                text: message
            }
            ScrollBar.vertical: ScrollBar{}
        }
        RowLayout{
            Layout.fillWidth: true
            TextField{
                Layout.fillWidth: true
                id:txtFieldMessage
                placeholderText: "type your message to the client"
                //when press enter
                onAccepted:btnsendMessage.clicked()
            }
            Button{
                id:btnsendMessage
                text:"Send"
                onClicked: {
                    server.sendMessage(txtFieldMessage)
                    txtFieldMessage.clear()
                }
            }
        }
    }
}
