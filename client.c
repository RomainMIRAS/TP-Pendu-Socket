/******************************************************************************/
/*			Application: Pendu									    			*/
/******************************************************************************/
/*									      */
/*			 programme  CLIENT				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs : EL KANBI Asmae - HANI Pamella - MIRAS Romain 					*/
/*									      */
/******************************************************************************/	

#include <stdio.h>

int print_image()
{
	char *filename = "WELCOME.txt";
    FILE *fptr = NULL;
 
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }
    char read_string[128];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}

#include "socket_utils.h"

#define SERVICE_DEFAUT "1111"

void client_appli (char *serveur,char *service, char* client); /* programme client */

/*****************************************************************************/
/*--------------- programme client -----------------------*/

int main(int argc, char *argv[])
{

	char *service = SERVICE_DEFAUT; /* numero de service par defaut (no de port) */
	if (argc < 3 ){
		printf("Usage:client_ip serveur_ip [service_port] (nom ou port) \n");
	} else {
		/* serveur est le nom (ou l'adresse IP) auquel le client va acceder */
		/* service le numero de port sur le serveur correspondant au  */
		/* service desire par le client */
		//client_appli(serveur,service,client);

		if (argc == 4){
			service = argv[3];
		}

		client_appli(argv[2],service,argv[1]);}
	}

/*****************************************************************************/
void client_appli (char *serveur,char *service, char* client)

/* procedure correspondant au traitement du client de votre application */

{
	// Création de la socket client
	int id_socket_client = h_socket(AF_INET,SOCK_STREAM);
	// Bind de la socket client
	struct sockaddr_in * psockclient = malloc(sizeof(struct sockaddr_in));
	adr_socket(NULL,client,SOCK_STREAM,&psockclient);
	h_bind(id_socket_client,psockclient);

	// Connection à la socket
	struct sockaddr_in * psockserv = malloc(sizeof(struct sockaddr_in));
	adr_socket(service,serveur,SOCK_STREAM,&psockserv);
	h_connect(id_socket_client,psockserv);
	print_image();
	char* ligne; // Lecteur de ligne de Bienvenue
	printf("%s\n",read_line(id_socket_client));
	
	// Envoie du niveau de difficulté
	send_line_from_keyboard(id_socket_client);
	int nb_essais = read_int(id_socket_client);
	int state = PLAY;

	while (state == PLAY && nb_essais != 0)
	{	
		printf("Nombre d'essaie restant : %d\n",nb_essais);
		ligne = read_line(id_socket_client);
		printf("MOT ACTUEL : %s\n",ligne);
		// Essaie de réponse
		send_line_from_keyboard(id_socket_client);
		nb_essais = read_int(id_socket_client);
		state = read_int(id_socket_client);
	}

	ligne = read_line(id_socket_client);
	printf("%s\n",ligne);
	
	h_close(id_socket_client);

}



/*****************************************************************************/

