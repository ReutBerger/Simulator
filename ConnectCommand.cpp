//
// Created by eden on 19/12/2019.
//

#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <sys/msg.h>
#include <cstring>

#include "ConnectCommand.h"
#include "Interpreter.h"

ConnectCommand cmdConnect;

/* message structure */
struct message {
    long mtype;
    char mtext[1024];
};

// C function, start point of the thread
static int connectClientFuncC(ConnectCommand *obj) {
    return obj->connectClientFunc();
}

ConnectCommand::ConnectCommand() {
    msqid = -1;
}

ConnectCommand::~ConnectCommand() {
}

int ConnectCommand::execute(vector<string> arr, int index) {
    // 1st parameter = IP address, 2nd parameter = socket port
    if (arr[index][0] == '"') {
        arr[index].erase(0, 1);
        arr[index].erase(arr[index].size() - 1);
    }
    mAddr = inet_addr(arr[index].c_str());
    mPort = Calculate(arr[index + 1]);

    // Launch the server thread that gets data from the simulator
    thread threadObj(connectClientFuncC, this);

    // wait until the simulator is connected
    sem_init(&mSync, 0, 0);
    sem_wait(&mSync);

    // Return to the main thread
    threadObj.detach();
    sem_destroy(&mSync);

    // Two parameters handled, so return 2
    return 2;
}

int ConnectCommand::connectClientFunc() {
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        cerr << "Could not create a socket" << endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = mAddr;  //the localhost address
    address.sin_port = htons(mPort);

    // Requesting a connection with the server on local host with given port
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        cerr << "Could not connect to host server" << endl;
        return -2;
    }

    // We are connected to the simulator, so signal the main thread to continue
    cout << "Client is now connected to server" << endl;
    sem_post(&mSync);

    // Create a message to get data to send to the simulator
    if ((msqid = msgget(IPC_PRIVATE, IPC_CREAT | 0666)) < 0) {
        cerr << "Failed to create message" << endl;
        close(client_socket);
        return -3;
    }

    // receive message from queue
    struct message message;
    while (msgrcv(msqid, &message, sizeof(message), 0, MSG_NOERROR) > 0) {
        write(client_socket, message.mtext, strlen(message.mtext));
    }

    // Destroy message queue and socket
    msgctl(msqid, IPC_RMID, NULL);
    close(client_socket);

    cout << "ConnectCommand thread has ended" << endl;
    return 0;
}

void ConnectCommand::sendData(string buffer) {
    struct message message;

    strncpy(message.mtext, buffer.c_str(), sizeof(message.mtext) - 1);
    message.mtext[sizeof(message.mtext) - 1] = 0;
    message.mtype = 1;

    if (msgsnd(msqid, &message, sizeof(message), 0) < 0) {
        cout << "msgsnd failure: " << strerror(errno) << endl;
    }
}