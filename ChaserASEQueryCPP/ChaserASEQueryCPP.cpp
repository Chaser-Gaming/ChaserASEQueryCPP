#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <cstring>
#include <string.h>
#include <regex>
#include "Network.h"
#include <iterator>

using namespace std;

void sendUDP(string ip, int port);
void reggy(string message);
void splitnprint(string message);

int main(void){
    system("Color 0A");
    cout << R"(
##################################################################################################
# _____ _                           _____                            _____                       #
#/  __ \ |                         /  ___|                          |  _  |                      #
#| /  \/ |__   __ _ ___  ___ _ __  \ `--.  ___ _ ____   _____ _ __  | | | |_   _  ___ _ __ _   _ #
#| |   | '_ \ / _` / __|/ _ \ '__|  `--. \/ _ \ '__\ \ / / _ \ '__| | | | | | | |/ _ \ '__| | | |#
#| \__/\ | | | (_| \__ \  __/ |    /\__/ /  __/ |   \ V /  __/ |    \ \/' / |_| |  __/ |  | |_| |#
# \____/_| |_|\__,_|___/\___|_|    \____/ \___|_|    \_/ \___|_|     \_/\_\\__,_|\___|_|   \__, |#
#                                                                                           __/ |#
#                                                                                          |___/ #      
)";

    while (1) {
        cout << "##################################### START NEW SERVER QUERY " <<  "#####################################\n";
        string ip;
        string quit;
        int port;

        cout << "#" << string(96, ' ') + "#\n";
        cout << "# Enter server IP: ", cin >> ip;
        cout << "# Enter server Port: ", cin >> port;
        cout << "#" << string(96, ' ') + "#\n";

        sendUDP(ip, port + 123);

        cout << "# Push 'q' to exit, or any key to continue. " << string(53, ' ') + "#\n";;
        cin >> quit;

        if (quit == "q")
        return 0;
    }
    return 0;
}

void sendUDP(string ip, int port) {
    WSASession Session;
    UDPSocket Socket;
    char recvbuffer[250];
    string message = "s";

    try
    {
        Socket.SendTo(ip, port, message.c_str(), message.size());

        sockaddr_in add = Socket.RecvFrom(recvbuffer, sizeof(recvbuffer));
        string input(recvbuffer);
        cout << "############################## QUERY RESULTS FOR " << ip << ":" << port - 123 << " ##############################\n";
        cout << "#" << string(96, ' ') + "#\n";
        reggy(input);
        cout << "################################ END QUERY FOR " << ip << ":" << port - 123 << " ################################\n";
    }
    catch (std::system_error& e)
    {
        cout << e.what();
    }
}

void reggy(string message) {
    regex e("[^\\w\\.@*&^%$#!()= -]");

    string reggy = regex_replace(message, e, "\\");

    splitnprint(reggy);
}

void splitnprint(string message) {
    string delimiter = "\\";
    string fullmessage = message;
    int i = 0;
    string keys[50];
    size_t pos = 0;

        while ((pos = message.find(delimiter)) != string::npos) {
            keys[i] = message.substr(0, pos);
            message.erase(0, pos + delimiter.length());
            ++i;
        }
    
    cout << "# Server Name: " << keys[3] << string(98 - (keys[3].length() + 16), ' ') + "#\n";
    cout << "# Players Online: " << keys[8] + "/" + keys[9] << string(98 - (keys[8].length() + keys[9].length() + 20), ' ') + "#\n";
    cout << "# Map: " << keys[5] << string(98 - (keys[5].length() + 8), ' ') + "#\n";
    cout << "# Gametype: " << keys[4] << string(98 - (keys[4].length() + 13), ' ') + "#\n";
    cout << "# Version: " << keys[6] << string(98 - (keys[6].length() + 12), ' ') + "#\n";
    cout << "#" << string(96, ' ') + "#\n";
    int p = 0;
    int player = 1;

        for (int i = 0; i < stoi(keys[8]); i++)
        {
            cout << "################## PLAYER " << player << " ##################                                                   #\n";
            cout << "#" << string(96, ' ') + "#\n";
            cout << "# Name: " << keys[12 + p] << string(98 - (keys[12 + p].length() + 9), ' ') + "#\n";
            cout << "# Score: " << keys[15 + p] << string(98 - (keys[15 + p].length() + 10), ' ') + "#\n";
            cout << "# Team: " << keys[13 + p] << string(98 - (keys[13 + p].length() + 9), ' ') + "#\n";
            cout << "# Skin: " << keys[14 + p] << string(98 - (keys[14 + p].length() + 9), ' ') + "#\n";
            cout << "# Ping: " << keys[16 + p] << string(98 - (keys[16 + p].length() + 9), ' ') + "#\n";
            cout << "#" << string(96, ' ') + "#\n";
            p = p + 6;
            player++;
        }
}
