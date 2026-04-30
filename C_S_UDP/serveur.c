#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 4500
#define MAX_LEN_NUMERO 5
#define MAX_LEN_NOM 64

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


    sockfd= socket( AF_INET, SOCK_DGRAM, 0 );
	if ( sockfd == -1 )	{
		perror("Erreur dans la création d’un socket :");
		exit( 1 );
	}	/* if */
	err= bind( sockfd, ( struct sockaddr * ) & sock_name, sizeof( sock_name ) );
	if ( err == -1 )	{
		perror("Erreur lors de l’appel à bind :");
		exit( 1 );
	}	/* if */
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
        err = recvfrom(sockfd, nom, sizeof(nom), 0, (struct sockaddr *)&conn_addr, &length);
        if (err == -1){
            perror("Erreur lors de la reception");
            exit(5);
        }

        ficte(nom ,numero);
        printf("Nom: %s | Numero: %s -> envoye\n", nom, numero);

        err = sendto(sockfd, numero, sizeof(numero), 0, (struct sockaddr *)&conn_addr, sizeof(struct sockaddr));
        if (err == -1){
            printf("Erreur lors de l'envoi\n");
            exit(6);
        }
    }	
    return 0;
}

/*
     err = sendto(sockfd, nom, sizeof(nom), 0, (struct sockaddr *)&sock_name, sizeof(struct sockaddr));
    if (err == -1){
        printf("Erreur lors de lenvoi\n");
        exit(5);
    }
    err = recvfrom(sockfd, numero, sizeof(numero), 0, (struct sockaddr *)&sock_name, &length);
    if (err == -1){
        printf("Erreur lors de lenvoi\n");
        exit(5);
    }

 */
