#include "socket_utils.h"

char* get_line_keybord(char* line,int* nombre_char)
{
	// clean

	int i = 0;
	char c;
	while((c = getchar()) != '\n')
	{
		line[i] = c;
		i++;
	}
	line[i] = '\0';
	*nombre_char = i;
	return line;
}

void send_line_from_keyboard(int id_socket_client){
		int nombre_char = 0;
		char* ligne = malloc(100*sizeof(char));

		//Supprimer le buffer
		fflush(stdin);

		ligne = get_line_keybord(ligne,&nombre_char);

		send_string(id_socket_client,ligne,nombre_char);

		free(ligne);
}

void send_string(int id_socket_client,char* ligne,int nombre_char){
		h_writes(id_socket_client, (char*)&nombre_char, 4);
		
		h_writes(id_socket_client, ligne, nombre_char);
		free(ligne);
}


char * read_line(int id_socket){
	char *nb = malloc(4);
	h_reads(id_socket, nb, 4);

	char *c = malloc((int)*nb);
	h_reads(id_socket, c, (int)*nb);
	
	return c;
}