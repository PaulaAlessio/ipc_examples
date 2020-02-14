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
 *  - remove any existing file with the same pathname
 *  - construct the address structure of the server socket, bind the socket 
 *    to that address, and mark the socket as listening socket.
 *  - Execute an infinite loop to handle incoming client requests: 
 *      -- accepts the connection --> cfd
 *      -- read the data and write it to stdout
 *      -- close the connected socket cfd
 *
 * */

#include "us_xfr.h"

#define BACKLOG 5 

int main() {
 
  struct sockaddr_un addr; 
  int sfd; 
  ssize_t numRead; 
  char buf[BUF_SIZE]; 

  /* Create client socket */ 
  sfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sfd  == -1) 
    errExit("socket");
  
  /* Construct server address */ 
  
  /* Set address structure to 0 */ 
  memset(&addr, 0, sizeof(struct sockaddr_un));
  /* Initialize server address */
  addr.sun_family = AF_UNIX; 
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

  /* make the connection*/
  if (connect(sfd, (struct sockaddr*) &addr, sizeof(struct sockaddr_un)) == -1) 
     errExit("connect");
  
  /* Copy stdin to socket */  
  while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) 
    if (write(sfd, buf, numRead) != numRead) 
      fatal("partial/failed write");

  if (numRead == -1) 
    errExit("read");

  /* Closes our socket, server sees EOF */
  exit(EXIT_SUCCESS);
  return 0; 
}
