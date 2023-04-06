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
}

void send_string(int id_socket_client,char* ligne,int nombre_char){
		h_writes(id_socket_client, (char*)&nombre_char, 4);
		
		h_writes(id_socket_client, ligne, nombre_char);
}


char * read_line(int id_socket){
	char *nb = malloc(4);
	h_reads(id_socket, nb, 4);

	char *c = malloc((int)*nb);
	h_reads(id_socket, c, (int)*nb);

	return c;
}

void welcome(int id_socket){
	char *msg = "Bienvenue dans le jeu du pendu !\n";
	send_string(id_socket, msg,strlen(msg));
}

char *find_word(char *file, int seed){
  FILE *f = fopen(file, "r");

  if (f == NULL){
    printf("Impossible d'ouvrir le fichier %s\n", file);
    exit(1);
  }

  char *mot = (char *)malloc(20*sizeof(char));

  for (int i = 0; i <= seed; i++){
    fgets(mot, 20, f);
  }

  int length = strlen(mot);
  mot[length-1] = '\0'; // Supprimer le caractère retour à la ligne '\n'
  return mot;
}

char *generate_word(){
	srand(clock());
	int seed = rand()%50;
	return find_word("dico.txt", seed);
}

/* void winner(int id_socket, char *word){
	char *msg = malloc(100;
	msg = "";
	send_string();
} */

void end_game(int id_socket, char *word, int state){
	char *msg = malloc(100);
	if (state == WIN){
		msg = "Félicitations ! Vous avez trouvé le mot";
	}
	else{
		msg = "Désolé ! Vous avez perdu.. Il fallait trouver le mot";
	}

	strcat(msg, word);
	
	send_string(id_socket, msg, strlen(msg));
}


// Check si la lettre est contenue dans le mot à trouver et update le mot actuel
// Test si victoire
void check_mot(char* mot_a_trouver, char* mot_actuel, char lettre){

  // Afin de tester la lettre en entier ( évite la casse )
	//   char lettre_lower = tolower(lettre);
	//   char lettre_upper = toupper(lettre);

  if(strchr(mot_a_trouver,lettre ) != NULL) { // Si le mot à trouver contient la lettre

    while (*mot_a_trouver){
      if (*mot_a_trouver == lettre) *mot_actuel = *mot_a_trouver;
      *mot_actuel++;
      *mot_a_trouver++;
    }
  }
}
