#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
  int server_socket, client_socket;
  struct sockaddr_in server_address, client_address;
  char buffer[1024];
  int bytes_received;

  // Create a socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
    perror("socket");
    exit(1);
  }

  // Set up server address
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(PORT);

  // Bind the socket to the address
  if (bind(server_socket, (struct sockaddr*)&server_address,
           sizeof(server_address)) == -1) {
    perror("bind");
    exit(1);
  }

  // Listen for incoming connections
  if (listen(server_socket, 5) == -1) {
    perror("listen");
    exit(1);
  }

  printf("Server listening on port %d\n", PORT);

  // Accept a connection
  int addrlen = sizeof(client_address);
  client_socket = accept(server_socket, (struct sockaddr*)&client_address, &addrlen);
  if (client_socket == -1) {
    perror("accept");
    exit(1);
  }

  // Prepare response (simple HTML)
  const char* response =
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: text/plain\r\n"
      "\r\n"
      "Hello world";

  // Send the response
  if (send(client_socket, response, strlen(response), 0) == -1) {
    perror("send");
    close(client_socket);
    close(server_socket);
    exit(1);
  }

  // Receive data from client (can be ignored for this example)
  bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
  if (bytes_received == -1) {
    perror("recv");
  } else {
    // Optional: Process received data
    buffer[bytes_received] = '\0';
    printf("Received from client: %s\n", buffer);
  }

  // Close connections
  close(client_socket);
  close(server_socket);

  return 0;
}
