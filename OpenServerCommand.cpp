//
// Created by eden on 19/12/2019.
//

#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <sstream>

#include "VarMapClass.h"
#include "OpenServerCommand.h"

OpenServerCommand cmdOpenServer;

// C function, start point of the thread
static int openServerFuncC(OpenServerCommand *obj) {
    return obj->openServerFunc();
}

OpenServerCommand::OpenServerCommand() {
    // Fill mNodes
    mNodes = {"/instrumentation/airspeed-indicator/indicated-speed-kt",
              "/sim/time/warp",
              "/controls/switches/magnetos",
              "/instrumentation/heading-indicator/offset-deg",
              "/instrumentation/altimeter/indicated-altitude-ft",
              "/instrumentation/altimeter/pressure-alt-ft",
              "/instrumentation/attitude-indicator/indicated-pitch-deg",
              "/instrumentation/attitude-indicator/indicated-roll-deg",
              "/instrumentation/attitude-indicator/internal-pitch-deg",
              "/instrumentation/attitude-indicator/internal-roll-deg",
              "/instrumentation/encoder/indicated-altitude-ft",
              "/instrumentation/encoder/pressure-alt-ft",
              "/instrumentation/gps/indicated-altitude-ft",
              "/instrumentation/gps/indicated-ground-speed-kt",
              "/instrumentation/gps/indicated-vertical-speed",
              "/instrumentation/heading-indicator/indicated-heading-deg",
              "/instrumentation/magnetic-compass/indicated-heading-deg",
              "/instrumentation/slip-skid-ball/indicated-slip-skid",
              "/instrumentation/turn-indicator/indicated-turn-rate",
              "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
              "/controls/flight/aileron",
              "/controls/flight/elevator",
              "/controls/flight/rudder",
              "/controls/flight/flaps",
              "/controls/engines/engine/throttle",
              "/controls/engines/current-engine/throttle",
              "/controls/switches/master-avionics",
              "/controls/switches/starter",
              "/engines/active-engine/auto-start",
              "/controls/flight/speedbrake",
              "/sim/model/c172p/brake-parking",
              "/controls/engines/engine/primer",
              "/controls/engines/current-engine/mixture",
              "/controls/switches/master-bat",
              "/controls/switches/master-alt",
              "/engines/engine/rpm"};
}

int OpenServerCommand::execute(vector<string> arr, int index) {

    // 1st parameter = socket port
    mPort = stoi(arr[index]);
    cout << "OpenServerCommand: port = " << mPort << endl;

    // Launch the server thread that gets data from the simulator
    thread threadObj(openServerFuncC, this);

    // wait until the simulator is connected
    sem_init(&mSync, 0, 0);
    sem_wait(&mSync);

    // Return to the main thread
    threadObj.detach();
    sem_destroy(&mSync);

    // One parameter handled, so return 1
    return 1;
}

int OpenServerCommand::openServerFunc() {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        cerr << "Could not create a socket" << endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(mPort);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Could not bind the socket to an IP" << endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 2) == -1) { //can also set to SOMAXCON (max connections)
        cerr<<"Error during listening command" << endl;
        return -3;
    } else {
        cout << "Server is now listening ..." << endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);
    if (client_socket == -1) {
        cerr << "Error accepting client" << endl;
        return -4;
    }

    close(socketfd); //closing the listening socket

    // The simulator is connected, so signal the main thread to continue
cout << "Flight simulator is now connected to server" << endl;
    sem_post(&mSync);

    // Declare a buffer to get the data
    string buffer(1024, 0);

    // Reading from client in loop
    while (read(client_socket, &buffer[0], buffer.size() - 1) != -1) {
        // split buffer by comma and put all data in vector
        stringstream   ss(buffer);
        vector<float > data;

        for (float i; ss >> i;) {
            data.push_back(i);
            if (ss.peek() == ',')
                ss.ignore();
        }

        // Update all INPUT variables
        for (int i = 0; i < mNodes.size(); i++) {
            Variable *v;
            if (varList.findByNode(mNodes[i], v) && v->getDirection() == DIR_IN) {
                v->setVal(data[i]);
//                cout << v->getName() << " = " << mNodes[i] << " = " << v->getVal() <<endl;
            }
        }

//        for (auto& it: varList.mapVarName) {
//            Variable *v = it.second;
//            cout << it.first << ", ";
//            cout << ((v->getDirection() == DIR_IN) ? "INPUT" : "OUTPUT") << ", ";
//            cout << v->getVal() << endl;
//            n++;
//        }
//        cout << "We updated " << n << " variables" << endl << endl;
    }

    cout << "OpenServer thread has ended" << endl;
    close(client_socket);

    return 0;
}