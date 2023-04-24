
OBJ1 = socket_utils.o fon.o client.o 
OBJ2 = socket_utils.o fon.o serveur.o
OPTIONS	=
# Adaptation a Darwin / MacOS X avec fink
# Du fait de l'absence de libtermcap on se fait pas mal
# cracher dessus mais ca marche...
ifeq ($(shell uname), Darwin)
LFLAGS	+= -L/opt/local/lib
CFLAGS	+= -I /opt/local/include
endif
#Changer si necessaire le chemin d'acces aux librairies

# Adaptation a Linux
ifeq ($(shell uname), Linux)
OPTIONS	+= -ltermcap
endif

# Adaptation a FreeBSD
# Attention : il faut utiliser gmake...
ifeq ($(shell uname),FreeBSD)
OPTIONS	+= -ltermcap
endif

# Adaptation a Solaris

ifeq ($(shell uname),SunOS)
OPTIONS	+= -ltermcap  -lsocket -lnsl
CFLAGS	+= -I..
endif

EXEC = ${OBJ1} client ${OBJ2} serveur
all: ${EXEC} 

fon.o : fon.h fon.c 
	gcc -c fon.c
	#gcc -c fon.c

client.o : fon.h socket_utils.o client.c
	gcc  $(CFLAGS) -c  client.c	

socket_utils.o : socket_utils.h fon.h 
	gcc  $(CFLAGS) -c  socket_utils.c	

serveur.o : fon.h serveur.c
	gcc  $(CFLAGS) -c  serveur.c	

client : ${OBJ1}
	gcc $(LFLAGS) ${OBJ1} -o client -lcurses $(OPTIONS)

serveur : ${OBJ2}
	gcc $(LFLAGS) ${OBJ2} -o serveur -lcurses $(OPTIONS)

clean : 
	rm -f ${EXEC} core

