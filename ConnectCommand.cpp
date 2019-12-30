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

int ConnectCommand::execute(vector<string> arr, int index) {
    // 1st parameter = IP address, 2nd parameter = socket port
    mAddr = inet_addr(arr[index].c_str());

// REMOVE AFTER!!
mAddr = inet_addr("192.168.25.1");

    mPort = stoi(arr[index + 1]);
    cout << "ConnectCommand: addr = " << hex << mAddr << ", port = " << dec << mPort << endl;

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
    char buffer[1024];

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
    msqid = msgget(IPC_PRIVATE, IPC_CREAT | 0600);

    if (msqid == -1) {
        cerr << "Failed to create message" << endl;
        close(client_socket);
        return -3;
    }

    // receive message from queue
    struct message message;

    while (msgrcv(msqid, &message, 1024, 0, 0) > 0) {
//        cout << "got buffer = " << message.mtext << endl;
        write(client_socket, message.mtext, strlen(message.mtext));
    }

    // Destroy message queue
    msgctl(msqid, IPC_RMID, NULL);

    close(client_socket);
}

void ConnectCommand::sendData(string buffer) {
    struct message message;

    strcpy(message.mtext, buffer.c_str());

    msgsnd(msqid, &message, sizeof(long) + (strlen(message.mtext) * sizeof(char)) + 1, 0);
}