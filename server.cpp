#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

int main() {

    while(true) {
        int network_socket = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(9002);
        server_address.sin_addr.s_addr = INADDR_ANY;

        int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

        if(connection_status == -1) {
            printf("No data was sent by the client!\n\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(7000));
            continue;
        }

        std::ofstream scoreboardDB;
        scoreboardDB.open("database/scoreboard.db", std::ios::app);

        char client_message[256];
        recv(network_socket, &client_message, sizeof(client_message), 0);
        printf("The client send the date, %s\n",client_message);

        scoreboardDB << client_message << std::endl;

        close(network_socket);
    }


    return 0;
}



