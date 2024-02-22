/* Codi solucio de la practica: SERVIDOR */

/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MIDA_BUFFER 1024
 

bool consultaNum(int n){
    bool correcte=false;
    if((n>=0)&&(n<=99)){
        correcte=true;
    }
    return correcte;
}


int main( ){
 
    int s;    /* Per treballar amb el socket */
    struct sockaddr_in serv_adr, client_adr;
    char buffer[MIDA_BUFFER];
    socklen_t mida;
    int n, i;
    
    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM, 0); //0->protocol per defecte UDP (0)

    /* Posem les dades del socket */
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = INADDR_ANY; //El servidor escoltarà desde qualsevol interfície de xarxa
    serv_adr.sin_port = htons(44444);

    /* Enllacem el socket (blind retorna un valor enter >=0 si s'ha pogut vincular)*/
    n = bind(s, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

    if (n < 0) //si blind es menor que 0, no s'ha pogut fer la connexió
    {
        printf("No s'ha pogut enllacar el socket\n");
    }
    else
    {
        i = 0;
        int n1,n2;
        /* Servidor operatiu! */
        printf("Servidor operatiu!\n");
        printf("Esperant peticions dels clients...\n");    

        do  /* Bucle infinit */
        {
            recvfrom(s, (char*)buffer, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, &mida); //rebem la info del client al buffer
            sscanf(buffer, "%d %d",&n1,&n2); //rebem les dades del buffer passant-les a enters cadascun dels dos valors 
            printf("Petició rebuda!\n");
            int result;
            char res[MIDA_BUFFER];
            char numRes[MIDA_BUFFER];
            if((consultaNum(n1)) && (consultaNum(n2))){  //si els dos valors estan dins del rang fem l'operació i la retornem al client
                result=n1*n2; //fem l'operació
                sprintf(numRes,"%d\nAdeu!!!",result); //guardem en string el resultat (com a cadena de caràcters)
                char frase[]="El resultat es "; //creem una altra variable de cadena de caràcters per fer una concatenació del resultat anterior amb un missatge en específic
                strcat(strcpy(res, frase), numRes); //concatenació de caràcters (res=frase+numRes)               
            }
            else    //en el cas de que algun dels dos números del client no es trobin dins del rang, enviem un missatge d'error al client sense fer l'operació
            {
                printf("Error->");
                char resString[]="El servidor diu error amb el rang dels números \nAdeu!!!";
                strcpy(res,resString);  //passem a la variable de chars res el contingut (missatge d'error de la variable resString)
            }        
            sendto(s, (char*)res, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, sizeof(client_adr));  //enviar info al client dins de la variable res
            printf("Resposa enviada!\n");
        
        }while(1);
    }

    /* Tanquem el socket */
    close(s);
    return 0;
}