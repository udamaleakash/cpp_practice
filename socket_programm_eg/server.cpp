#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024




int main()
{
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    /* 1. Create Socket -
    Parameter	 Meaning
    AF_INET	     IPv4 addressing
    SOCK_STREAM	 TCP protocol
        0	     default protocol

Creates a communication endpoint.*/
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("socket failed");
        return 1;
    }

    int opt = 1;
    /* 2. Set Socket Option- Allows reuse of port immediately & Prevents "Address already in use" error. */
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    /* 3. Bind Socket to IP and Port
    e.g.- 192.168.2.12 : 8080
    */
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind failed");
        return 1;
    }
    /* 4. Listen for Connections
    5 means maximum pending connection queue. */
    if (listen(server_fd, 5) < 0)
    {
        perror("listen failed");
        return 1;
    }

    cout << "Server started on port " << PORT << endl;
    cout << "Waiting for connection..." << endl;
    /* 5. Accept Client Connection
    When client connects:
    New socket created
    Server communicates with client using this new socket

    Important concept:
    server_fd -> listening socket
    client_socket -> communication socket */
    client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (client_socket < 0)
    {
        perror("accept failed");
        return 1;
    }

    cout << "Client connected: " << inet_ntoa(client_addr.sin_addr) << endl;

    /* 6. Receive Data - Reads data sent from client. */
    memset(buffer, 0, BUFFER_SIZE);
    int bytes = read(client_socket, buffer, BUFFER_SIZE - 1);

    if (bytes > 0)
        cout << "Client says: " << buffer << endl;
    /* 7. Send Data- Server replies to client. */
    const char *reply = "Hello from server...";
    send(client_socket, reply, strlen(reply), 0);

    /* 8. Close Connection */
    close(client_socket);
    close(server_fd);

    return 0;
}
/* Overall Flow
Server Flow
socket()
bind()
listen()
accept()
read()
send()
close()
Client Flow
socket()
connect()
send()
read()
close()
*/

/* Interview Questions (VERY COMMON) */

/* 
Socket programming:-(client-server communication)

Is a method for enabling communication between two nodes (processes) on a network, creating a, "networked application", or linking processes on the same device. */


/* Q1 What is a socket?
Answer:
A socket is an endpoint for communication between two machines over a network. 
that sends/receives data using protocols like TCP or UDP.


Q2 Difference between TCP and UDP?
-> 
TCP
-Connection oriented	
-Reliable	
-Slower	

UDP
-Connectionless
-Unreliable
-Faster

Components of a Socket Connection:
A socket pair (client IP:port and server IP:port) uniquely identifies the communication channel.

Q3 What is a port?
->
In socket programming, a port number is a logical identifier that specifies which application or service on a device should send or receive network data.
Example:

HTTP -> 80
HTTPS -> 443
SSH -> 22

Q4 What is bind()?
Answer:
bind() attaches a socket to a specific IP address and port number.

Q5 Difference between listen() and accept()?
->
listen()
Prepare socket for connections

accept()
Accept incoming connection

Q6 What is TCP 3-way handshake?
Client -> SYN
Server -> SYN ACK
Client -> ACK

Purpose:
establish reliable connection

Q7 Why htons() is used?
Answer:
It converts host byte order to network byte order.
Network uses big-endian format.

⭐ How to Impress Interviewer ⭐
Explain like this:
->
"In my TCP client-server implementation, the server first creates a socket using socket(), binds it to a specific port using bind(), then listens for incoming connections using listen(). When a client connects, the server accepts the connection using accept(). After connection establishment via TCP 3-way handshake, the client sends a message using send() and the server receives it using read() or recv(). Finally the server sends a response and both sides close the socket."
This structured explanation impresses interviewers.

** TCP sockets are used in **:
Web servers
Database servers
Chat applications
Microservices
Distributed systems



*/