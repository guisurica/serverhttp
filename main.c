#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char** argv) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr addr = {
    AF_INET,
    0x901f,
    0
  };
  
  bind(s, &addr, sizeof(addr));

  listen(s, 10);

  int client_fd = accept(s, 0, 0);

  char buffer[256] = {0};
  recv(client_fd, buffer, 256, 0);

  char* f = buffer + 5;
  *strchr(f, ' ') = 0;
  int opened_fd = open(f, O_RDONLY);
  sendfile(client_fd, opened_fd, 0, 256);
  close(opened_fd);
  close(client_fd);
  close(s);
}
