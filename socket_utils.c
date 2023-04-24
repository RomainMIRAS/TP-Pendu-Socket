#include "socket_utils.h"

// Convertisseur d'entier en chaine de caractére
char* itoa(int nombre){
	char* nb = malloc(4);
	snprintf(nb, 4, "%d", nombre);
	return nb;
}

// Récupére une ligne de la console
char* get_line_keybord(char* line,int* nombre_char)
{
	// clean
	fflush(stdin);

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

//Envoie une ligne de la console dans la socket
void send_line_from_keyboard(int id_socket_client){
		int nombre_char = 0;
		char* ligne = malloc(100*sizeof(char));

		//Supprimer le buffer
		ligne = get_line_keybord(ligne,&nombre_char);

		send_string(id_socket_client,ligne,nombre_char);
}

// Envoie une ligne dans la socket
void send_string(int id_socket_client,char* ligne,int nombre_char){
		h_writes(id_socket_client, itoa(nombre_char), 4);
		h_writes(id_socket_client, ligne, nombre_char);
}

// Envoie un entier dans la socket
void send_int(int id_socket_client, int nombre){
	h_writes(id_socket_client, itoa(nombre), 4);
}

// Lit un entier de la socket
int read_int(int id_socket){
	fflush(stdout);
	char *nb = malloc(4);
	h_reads(id_socket, nb, 4);
	return atoi(nb);
}

// Lit une ligne de la socket
char * read_line(int id_socket){
	fflush(stdout);
	char *nb = malloc(4);
	h_reads(id_socket, nb, 4);

	int nombre_char = atoi(nb);
	char *c = malloc(nombre_char);
	h_reads(id_socket, c, nombre_char);

	return c;
}

// Envoie du message de bienvenue
void welcome(int id_socket){
	char *msg = "Bienvenue dans le jeu du pendu !\nVeillez rentrer votre niveau de facilité :\n(Nombre d'essaie supplémentaire)\n";
	send_string(id_socket, msg,strlen(msg));
}

// Génère un mot aléatoire dans un fichier
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

// Génère un mot aléatoire
char *generate_word(){
	srand(clock());
	int seed = rand()%50;
	return find_word("dico.txt", seed);
}

// Envoie l'état du jeu de fin au client
void end_game(int id_socket, char *word, int state){
	char* msg;
	if (state == WIN){
		msg = "Félicitations ! Vous avez trouvé le mot : ";
	}
	else{
		msg = "Désolé ! Vous avez perdu.. Il fallait trouver le mot : ";
	}

	int length = strlen(word) + strlen(msg) + 1;
	char* new_msg = malloc(length);  // allocate memory 
	strcpy(new_msg, msg);  // copy first string 
	strcat(new_msg, word);  // then check your function to concat strings
	send_string(id_socket, new_msg, length);
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
