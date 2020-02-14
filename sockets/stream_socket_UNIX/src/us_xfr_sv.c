/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU Lesser General Public License as published   *
* by the Free Software Foundation, either version 3 or (at your option)   *
* any later version. This program is distributed without any warranty.    *
* See the files COPYING.lgpl-v3 and COPYING.gpl-v3 for details.           *
*                                                                         *
* MODIFIED  for learning purposes                                         *
\*************************************************************************/

/* 
 * @file usr_xfr_cl.c 
 * @date 05.12.2017
 * @brief Stream socket server. It performs the following steps: 
 *  - create a socket, 
 *  - construct the address structure of the server socket, and connect it to 
 *    to that address.
 *  - Execute a loop that copies its standard input to the socket connection. 
 *    When encontreing EOF, the client terminets, closing the socket and the 
 *    server sees EOF on the other end 
 *
 * */


#include "us_xfr.h"
#include <sys/socket.h>

#define BACKLOG 5

int main() {
  struct sockaddr_un addr;
  int sfd, cfd;
  ssize_t numRead;
  char buf[BUF_SIZE];

  /* Create a socket */
  sfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sfd == -1)
    errExit("socket"); 

  if (strlen(SV_SOCK_PATH) > sizeof(addr.sun_path) - 1)
     fatal("Server socket path too long: %s", SV_SOCK_PATH);

  /* Remove any existing file with the pathname we want to bind the socket to */
  if ((remove(SV_SOCK_PATH)) == -1 && errno != ENOENT) 
    errExit("remove-%s", SV_SOCK_PATH);
 
  /* Set all structure fields to 0*/
  memset(&addr, 0, sizeof(struct sockaddr_un));

  /* Initialize the sockaddr_un structure */
  addr.sun_family=AF_UNIX; 
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

  /* Bind the socket */
  if ((bind(sfd, (struct sockaddr *)  &addr, sizeof(struct sockaddr_un))) == -1)
    errExit("bind");

  /* Make the socket a listening socket if possible */
  if (listen(sfd, BACKLOG) == -1)
    errExit("listen");

  /* Infinite loop, handle client connections iteratively  */
  for (;;) {
    /* Accept a connection. The conection is returned on a new socket, 'cfd';
     * The listening socket, 'sfd' remains open and can be used to accept 
     * further connections. */

    cfd = accept(sfd, NULL, NULL);
    if (cfd == -1)
      errExit("accept");
  
    /* Transfer data from connected socket to stdout until EOF */
    while ((numRead = read(cfd, buf, BUF_SIZE)) > 0) 
      if (write(STDOUT_FILENO, buf, numRead) != numRead) 
        fatal("partial/failed write");
      if (numRead == -1)
        errExit("read");
      if (close(cfd) == -1) 
        errMsg("close");
  }
  return 0;
}
