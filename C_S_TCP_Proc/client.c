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
	sockfd= socket( AF_INET, SOCK_STREAM, 0 );

    if ( sockfd == -1 )	{
		perror("Erreur lors de la création d’un socket :");
		exit(4);
	}

    err= connect( sockfd, (struct sockaddr * ) & sock_name, sizeof( sock_name ) );
	if ( err == -1 )	{
	    perror("Erreur lors de la demande de connexion :");
		exit( 1 );
	}
    err= write( sockfd, nom, MAX_LEN_NOM - 1 );
	if ( err < 0 )	{
		perror("Erreur lors de write :");   
    }

    err= read( sockfd, numero, MAX_LEN_NUMERO - 1 );
	if ( err < 0 )	{
	    perror( "Erreur dans read :");			
        exit( 1 );
	}

	printf("Le message reçu est :\n");
    printf("Nom: %s | Numero: %s\n", nom, numero);


    
    return 0;
}
