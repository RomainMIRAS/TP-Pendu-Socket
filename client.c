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


#include "client.h"
#include "socket_utils.h"

#define SERVICE_DEFAUT "1111"
#define SERVEUR_DEFAUT "127.0.0.1"

void client_appli (char *serveur, char *service);


/*****************************************************************************/
/*--------------- programme client -----------------------*/

int main(int argc, char *argv[])
{

	char *serveur= SERVEUR_DEFAUT; /* serveur par defaut */
	char *service= SERVICE_DEFAUT; /* numero de service par defaut (no de port) */


	/* Permet de passer un nombre de parametre variable a l'executable */
	switch(argc)
	{
 	case 1 :		/* arguments par defaut */
		  printf("serveur par defaut: %s\n",serveur);
		  printf("service par defaut: %s\n",service);
		  break;
  	case 2 :		/* serveur renseigne  */
		  serveur=argv[1];
		  printf("service par defaut: %s\n",service);
		  break;
  	case 3 :		/* serveur, service renseignes */
		  serveur=argv[1];
		  service=argv[2];
		  break;
    default:
		  printf("Usage:client serveur(nom ou @IP)  service (nom ou port) \n");
		  exit(1);
	}

	/* serveur est le nom (ou l'adresse IP) auquel le client va acceder */
	/* service le numero de port sur le serveur correspondant au  */
	/* service desire par le client */
	
	client_appli(serveur,service);
}
/*****************************************************************************/
void client_appli (char *serveur,char *service)

/* procedure correspondant au traitement du client de votre application */

{
	// Création de la socket client
	int id_socket_client = h_socket(AF_INET,SOCK_STREAM);
	// Bind de la socket client
	struct sockaddr_in * psockclient = malloc(sizeof(struct sockaddr_in));
	adr_socket(NULL,"200.0.0.1",SOCK_STREAM,&psockclient);
	h_bind(id_socket_client,psockclient);

	// Connection à la socket
	struct sockaddr_in * psockserv = malloc(sizeof(struct sockaddr_in));
	adr_socket(service,serveur,SOCK_STREAM,&psockserv);
	h_connect(id_socket_client,psockserv);

	char* ligne;

	//printf("%s",read_line(id_socket_client)); // TODO ENLEVER LE COMMENTAIRE	

	int state = PLAY;
	printf("Veillez rentrer votre niveau de difficulté : \n");
	send_line_from_keyboard(id_socket_client);
	while (state == PLAY)
	{
		ligne = read_line(id_socket_client);

		// Essaie de réponse
		send_line_from_keyboard(id_socket_client);

		printf("MOT ACTUEL : %s",read_line(id_socket_client));
		state = atoi(read_line(id_socket_client));
	}
}



/*****************************************************************************/

