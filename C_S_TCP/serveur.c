#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 4500
#define MAX_LEN_NUMERO 5
#define MAX_LEN_NOM 64
#define MAX_CONNECTION_NB 10

#define LG_MAX_SIZE 40

void ficte(char nom[], char numero[]){
    char Ligne [LG_MAX_SIZE] ;
    FILE *fp;
    int Trouve = 0 ;
    
    fp = fopen("fictel","r") ;
    if (fp == NULL) {
        perror("Erreur ouverture fichier fictel");
        strcpy(numero, "????");
        return;
    }

    while (fgets (Ligne, LG_MAX_SIZE, fp) && ! Trouve) {
        Ligne [strlen(Ligne) - 1] = '\0';
        if (!strcmp(nom, Ligne + 5)){ 
            Trouve = 1; 
            strncpy(numero,Ligne,4);
        }
    }
    
    fclose(fp);
    if (!Trouve) strcpy(numero,"????");
}


int create_socket()	{
	int sockfd;
	struct sockaddr_in sock_name;
	int err;

    bzero((char *)&sock_name, sizeof(sock_name));
    sock_name.sin_family = AF_INET;
    sock_name.sin_addr.s_addr = INADDR_ANY;
    sock_name.sin_port = SERVER_PORT;


    sockfd= socket( AF_INET, SOCK_STREAM, 0 );
	if ( sockfd == -1 )	{
		perror("Erreur dans la création d’un socket :");
		exit( 1 );
	}
	err= bind( sockfd, ( struct sockaddr * ) & sock_name, sizeof( sock_name ) );
	if ( err == -1 )	{
		perror("Erreur lors de l’appel à bind :");
		exit( 1 );
	}
    err= listen( sockfd,  MAX_CONNECTION_NB);
	if ( err == -1 )	{
		perror("Erreur lors de l’appel à listen :");
		exit( 1 );
	}
	return sockfd;
}


int	main( int argc, char ** argv )	{

    printf(" ============== Serveur ============== \n");
    int sockfd;
	int err;
    int length = sizeof(struct sockaddr_in);
    char numero[MAX_LEN_NUMERO] ;
    char nom[MAX_LEN_NOM];


    sockfd= create_socket();	
    while ( 1 )	{
        struct sockaddr_in conn_addr;
        int desc= accept( sockfd, ( struct sockaddr * ) &conn_addr, &length );
		if ( desc < 0 )	{
			perror("Erreur dans l’appel de accept :");
			exit( 1 );
		}
        err= read( desc, nom, MAX_LEN_NOM - 1 );
        if (err == -1){
            perror("Erreur lors de read");
            exit(5);
        }

        ficte(nom ,numero);
        printf("Nom: %s | Numero: %s -> envoye\n", nom, numero);

        err= write( desc, numero, MAX_LEN_NUMERO - 1 );
        if (err == -1){
            printf("Erreur lors de write\n");
            exit(6);
        }
    }	
    return 0;
}


