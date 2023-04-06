/******************************************************************************/
/*			Application: Pendu									    			*/
/******************************************************************************/
/*									      */
/*			 programme  SERVEUR				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs : EL KANBI Asmae - HANI Pamella - MIRAS Romain 					*/
/*									      */
/******************************************************************************/		

#include<stdio.h>
#include <curses.h>

#include<sys/signal.h>
#include<sys/wait.h>
#include<stdlib.h>

#include "fon.h"     		/* Primitives de la boite a outils */

#define SERVICE_DEFAUT "1111"

void serveur_appli (char *service);   /* programme serveur */


/******************************************************************************/	
/*---------------- programme serveur ------------------------------*/

int main(int argc,char *argv[])
{

	char *service= SERVICE_DEFAUT; /* numero de service par defaut */


	/* Permet de passer un nombre de parametre variable a l'executable */
	switch (argc)
 	{
   	case 1:
		  printf("defaut service = %s\n", service);
		  		  break;
 	case 2:
		  service=argv[1];
            break;

   	default :
		  printf("Usage:serveur service (nom ou port) \n");
		  exit(1);
 	}

	/* service est le service (ou numero de port) auquel sera affecte
	ce serveur*/
	
	serveur_appli(service);
}


/******************************************************************************/	
void serveur_appli(char *service)

/* Procedure correspondant au traitemnt du serveur de votre application */

{

	int id_socket_serveur =  h_socket(AF_INET, SOCK_STREAM);
	struct sockaddr_in * psockserveur = malloc(sizeof(struct sockaddr_in *));
	adr_socket(service, NULL, SOCK_STREAM, &psockserveur);
	h_bind(id_socket_serveur, psockserveur);
	h_listen(id_socket_serveur, 1000);
	
	// Création de la socket avec laquelle on communique avec le client
	int new_s = h_accept(id_socket_serveur, psockserveur);


	// Lecture caractère par caractère
	char car;
	int valid = 10;
	while (valid != 0){
		valid = h_reads(new_s, &car, 1);
		printf("%c\n", car);


	}
	


}

/******************************************************************************/	

