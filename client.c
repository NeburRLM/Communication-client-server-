/* Codi solucio de la practica: CLIENT */

/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
#define MIDA_BUFFER 1024

int main(int argc, char **argv){
 
    if (argc != 2) { //el programa principal del client espera el nom de l'executable i l'adreça IP
        printf("Us: %s IP\n", argv[0]);
        exit(0);
    }
    
    int s;    /* Per treballar amb el socket */
    struct sockaddr_in adr;
    char buffer[MIDA_BUFFER];
    int i;

    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM, 0);

    adr.sin_family = AF_INET;
    adr.sin_port = htons(44444);    //port (enter)

    /* L'adreca de comunicacio sera la IP del servidor, es a dir el parametre */
    adr.sin_addr.s_addr = inet_addr(argv[1]);   //conversió de cadena de caràcters 
    
 

    //Preguntem els números a l'usuari i els guardem en cadascuna de les variables n1 i n2
     int n1,n2;
     printf("Introdueix el primer nombre: ");  
     scanf("%d", &n1);    
     printf("Introdueix el segon nombre: ");
     scanf("%d", &n2);
     
     //guardem els dos números en String amb el formar "n1 n2" al buffer
     sprintf(buffer,"%d %d",n1,n2);

     //printf("%s",buffer);

    
    int resultat;
    socklen_t mida;
    sendto(s, (char*)buffer, MIDA_BUFFER, 0, (struct sockaddr*)&adr, sizeof(adr)); //enviem la info guardada al buffer per a que ho executi el servidor

    printf("Esperant el resultat del servidor...\n");
        
    recvfrom(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&adr, &mida); //rebem la resposta del servidor respecte al que li hem enviat al mateix servidor
            
    printf("\n--->%s\n\n",buffer);  //mostra la resposta adquirida del servidor que hem rebut al client
        
    /* Tanquem el socket */
    close(s);
    return 0;
}
