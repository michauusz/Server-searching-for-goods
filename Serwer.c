#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#define MAX 80
//#define PORT 8092
#define SA struct sockaddr

struct products
{
    char nazwa [20];
    int id;
    float cena;

};
int atoi(const char *string);
double atof(const char *string);
void Print_Towar(struct products prod[],int length);



// Function designed for chat between client and server.
void func(int sockfd,struct products prod[])
{
    char buff[MAX];
//char ch;

    //int n;

    int id, len=0, i;
    char cc, ch;
    char *haslo;



    for (;;)
    {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, MAX);
        id = atoi(buff);
        //bzero(buff, MAX);
        int k;
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }


        if (strncmp("admin", buff, 5) == 0)    //sprawdzamy czy admin
        {
            printf("\nClient try run admin mode.\n");
            bzero(buff, MAX);




            buff[0] = 'H';
            buff[1] = 'a';
            buff[2] = 's';
            buff[3] = 'l';
            buff[4] = 'o';
            buff[5] = ':';
            write(sockfd, buff, MAX); //wysylamy komunikat
            bzero(buff, MAX);
            //pobieramy zaszyforwane haslo z pliku password.txt
            FILE* file = fopen("Password.txt", "r");
            while((cc = fgetc(file)) != EOF)
            {
                if (cc == '\n')
                {
                    break;
                }
                len++;//lenght of first row
            }


            // allocate memory for size of first line (len)
            haslo = (char *) malloc(sizeof(char) * len);

            // seek to beginning of file
            fseek(file, 0, SEEK_SET);

            fread(haslo, sizeof(char), len, file);



            fclose(file);
            //printf("\nhaslo: %s", haslo); Odvzytano z pliku
            //Dect
            for(i = 0; haslo[i] != '\0'; ++i)
            {
                ch = haslo[i];

                if(ch >= 'a' && ch <= 'z')
                {
                    ch = ch - 3;

                    if(ch < 'a')
                    {
                        ch = ch + 'z' - 'a' + 1;
                    }

                    haslo[i] = ch;
                }
                else if(ch >= 'A' && ch <= 'Z')
                {
                    ch = ch - 3;

                    if(ch < 'A')
                    {
                        ch = ch + 'Z' - 'A' + 1;
                    }

                    haslo[i] = ch;
                }

            }
            //After decrypting
            read(sockfd, buff, MAX); //odczytujemy haslo


            if (strncmp(haslo, buff, 5) == 0) // sprawdzamy czy podane prawdidlowe
            {
                bzero(buff, MAX);

                buff[0] = 'Z';
                buff[1] = 'a';
                buff[2] = 'l';
                buff[3] = 'o';
                buff[4] = 'g';
                buff[5] = 'o';
                buff[6] = 'w';
                buff[7] = 'a';
                buff[8] = 'n';
                buff[9] = 'o';

                write(sockfd, buff, MAX); //wysylamy komunikat zalogowano
                bzero(buff, MAX);
                printf("Client has logged as admin.\n");

            }
            else //jesli nie to odsylamy wiadomosc bledne haslo
            {
                bzero(buff, MAX);



                buff[0] = 'B';
                buff[1] = 'l';
                buff[2] = 'e';
                buff[3] = 'd';
                buff[4] = 'n';
                buff[5] = 'e';
                buff[6] = ' ';
                buff[7] = 'H';
                buff[8] = 'a';
                buff[9] = 's';
                buff[10] = 'l';
                buff[11] = 'o';
                printf("Login declined.\n");
                write(sockfd, buff, MAX); //wysylamy komunikat bledne haslo
                bzero(buff, MAX);

            }

        }
        //Wypisywanie towaru. Skoro nie admin
        else
        {
            for(k=0; k<100; ++k)
            {

                if(prod[k].id==id) //jezeli jest taki produkt to wykonuje wysylanie do klienta danych
                {

                    //   bzero(buff, MAX);
                    buff[0] = prod[k].id;
                    write(sockfd, buff, MAX);
                    bzero(buff, MAX);
                    unsigned char* bytedFloat = (unsigned char*) &prod[k].cena;

                    buff[0] = bytedFloat[3];
                    buff[1] = bytedFloat[2];
                    buff[2] = bytedFloat[1];
                    buff[3] = bytedFloat[0];
                    write(sockfd, buff, MAX);
                    bzero(buff, MAX);

                    int n = 0;




                    strcat (prod[k].nazwa, " ");
                    while (prod[k].nazwa[n] != '\0')
                    {

                        buff[n] = prod[k].nazwa[n];
                        n++;
                    }



                    write(sockfd, buff, sizeof(buff));

                }

            }
        }



    }
}



int main(int argc, char *argv[])
{
    struct products prod[20];
    int sockfd, connfd, port;
    socklen_t len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification



    if (argc == 2)
    {
        port=atoi(argv[1]);
    }
    else
    {

        printf("socket creation failed...\n");
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    int k = 0;
//
//

//
//

//

//
//zaczynamy szukac potem do funckji
    FILE* file = fopen("file.txt", "r");
    char line[257];///jakos dynamicznie w przys
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        i++;
        if(i%4==1)
        {
            prod[k].id = atoi(line);
        }
        else if(i%4==2)
        {
            strcpy(prod[k].nazwa,line);
        }
        else if(i%4 == 3)
        {
            prod[k].cena = atof(line);
            k++;
        }

    }
    fclose(file);
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0)
    {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
        printf("server acccept the client...\n");


    func(connfd,prod);

    // After chatting close the socket
    close(sockfd);
}
