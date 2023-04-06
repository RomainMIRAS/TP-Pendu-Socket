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

void send_line(int id_socket_client){
		int nombre_char = 0;
		char* ligne = malloc(100*sizeof(char));

		//Supprimer le buffer
		fflush(stdin);
		printf("test\n");
		
		ligne = get_line_keybord(ligne,&nombre_char);

		h_writes(id_socket_client, (char*)&nombre_char, 4);
		
		h_writes(id_socket_client, ligne, nombre_char);
		free(ligne);
}