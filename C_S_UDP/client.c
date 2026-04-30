#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 4500
#define MAX_LEN_NOM 64
#define MAX_LEN_NUMERO 5

int	main( int argc, char ** argv )	{

    printf(" ============== Client ============== \n");
    int sockfd;
    int err;
    struct sockaddr_in sock_name;
    int length = sizeof(struct sockaddr_in);
	char * hostname;
	struct hostent * server;
	char nom[MAX_LEN_NOM];
    char numero[MAX_LEN_NUMERO];

	if ( argc != 3 )	{
    	fprintf( stderr, "Erreur dans le nombre d’arguments de la ligne de commande \n");
		exit(1);
	}

    hostname= argv[1];
	if ( strlen( argv[ 2 ] ) > MAX_LEN_NOM - 1 )	{
		fprintf( stderr, "L’argument de la chaîne de commande est trop long \n");
		exit(2);
	}

    strcpy( nom, argv[ 2 ]);
	server= gethostbyname(hostname);
	if ( ! server ) 	{
		fprintf( stderr, "Erreur dans la détermination du hostname \n");
		exit(3);
	}	
    
    sock_name.sin_port= SERVER_PORT;
    sock_name.sin_family= AF_INET;
	bcopy((char *) server->h_addr_list[0], ( char * ) & sock_name.sin_addr.s_addr,
									server->h_length );
	sockfd= socket( AF_INET, SOCK_DGRAM, 0 );

    if ( sockfd == -1 )	{
		perror("Erreur lors de la création d’un socket :");
		exit(4);
	}

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

    printf("Nom: %s | Numero: %s", nom, numero);
    
    return 0;
}
