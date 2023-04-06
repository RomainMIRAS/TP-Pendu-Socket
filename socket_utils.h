#ifndef _SOCKET_UTILS_H_
#define _SOCKET_UTILS_H_

#include <stdio.h>
#include <curses.h> 		/* Primitives de gestion d'ecran */
#include <sys/signal.h>
#include <sys/wait.h>
#include<stdlib.h>

#include "fon.h"   		/* primitives de la boite a outils */

#include <string.h>
    
    


char* get_line_keybord(char* line,int* nombre_char);

void send_line(int id_socket_client);

void read_line(int id_socket, char *c);

#endif