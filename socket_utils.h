#ifndef _SOCKET_UTILS_H_
#define _SOCKET_UTILS_H_

#define WIN 1
#define LOOSE 0
#define PLAY 2

#include <stdio.h>
#include <curses.h> 		/* Primitives de gestion d'ecran */
#include <sys/signal.h>
#include <sys/wait.h>
#include<stdlib.h>

#include "fon.h"   		/* primitives de la boite a outils */

#include <string.h>
    
char* get_line_keybord(char* line,int* nombre_char);

void send_line_from_keyboard(int id_socket_client);

void send_string(int id_socket_client,char* ligne,int nombre_char);

char* read_line(int id_socket);

#endif