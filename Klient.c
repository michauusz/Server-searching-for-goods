// Write CPP code here
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <termios.h>
#include <arpa/inet.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8092
#define SA struct sockaddr
struct products {
    char nazwa [20];
    int id;
    float cena;

};

int getch (void)
{
        int ch;
        struct termios oldt, newt;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON|ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch;
}

int atoi(const char *string);
void clrscr(void)
{
    printf("\033[2J");
    printf("\033[0;0f");
}
int lenHelper(int x) {
    if (x >= 1000000000) return 10;
    if (x >= 100000000)  return 9;
    if (x >= 10000000)   return 8;
    if (x >= 1000000)    return 7;
    if (x >= 100000)     return 6;
    if (x >= 10000)      return 5;
    if (x >= 1000)       return 4;
    if (x >= 100)        return 3;
    if (x >= 10)         return 2;
    return 1;
}
void add(int sockfd)
{
 struct products prod[20];
FILE* file = fopen("file.txt", "r");
    char line[257];///jakos dynamicznie w przys
    int i = 0;
int k=0;
    while (fgets(line, sizeof(line), file)) {
        i++;
        if(i%4==1)
        {
            prod[k].id = atoi(line);
        }
        else if(i%4==2){
            strcpy(prod[k].nazwa,line);
        }
        else if(i%4 == 3){
            prod[k].cena = atof(line);
            k++;
        }

}
 fclose(file);
int id;

int help=0;
char nazwa[20];
float cena;

printf("\nPodaj nr produktu(8cyfr): \n");
scanf("%d", &id);
fflush(stdin);
while(lenHelper(id) != 8 )
{
printf("\nBledny nr produktu: \n");
printf("\nPodaj nr produktu(8cyfr): \n");
scanf("%d", &id);
fflush(stdin);
}

do
{
for(i=0; i<100;++i)
{



if(prod[i].id==id)
{


    help = 1;
    break;
}
else{
    help = 0;

}
}
if(help==1)
{ printf("Podano duplikat nr");
	printf("\nPodaj nr produktu(8cyfr): \n");
	scanf("%d", &id);
	fflush(stdin);

}

}while(help!=0);


printf("Podaj nazwe produktu: \n");
scanf("%s", nazwa);
fflush(stdin);
printf("Podaj cene produktu: \n");
scanf("%f", &cena);
fflush(stdin);
printf("Nr: %d\nNazwa: %s\nCena: %.2f \n", id, nazwa, cena); //sprawdzenie

FILE *pFile;

    char buffer[256];
char newLine[5] = "\n";

    pFile=fopen("file.txt", "a");

        if(pFile==NULL) {
        perror("Error opening file.");
        }
         else {
		fprintf(pFile, "%s", newLine);

                fprintf(pFile, "%d", id);
		fprintf(pFile, "%s", newLine);
		bzero(buffer, MAX);
		strcat (nazwa, " ");
		int n=0;
		while (nazwa[n] != '\0')
        {

            buffer[n] = nazwa[n];
            n++;
        }
		fprintf(pFile, "%s", buffer);
		fprintf(pFile, "%s", newLine);
		bzero(buffer, MAX);

		fprintf(pFile, "%.2f", cena);
		bzero(buffer, MAX);
		fprintf(pFile, "%s", newLine);
		fclose(pFile);
	printf("\nPomyslnie dodano!\n");
	getchar();
        }

}
void adminPanel(int sockfd)
{
	int choose=0;
	while(choose!='3')

	{
	//clrscr();
	printf("Wybierz opcje:\n1-Dodaj towar\n3-wyloguj \n ");
		choose = getchar();
printf("\n");
		switch (choose) {
		   case '1':
		     add(sockfd);
			break;
		  // case '3':
		   //  printf("\n2\n");
			//break;
 		   case '2':
			printf("\nWylogowano\n");
			printf("\nThe Data Base has been updated, please reconnect.\n");


		     		break;
		     		case '3':
			printf("\nWylogowano\n");
			printf("\nThe Data Base has been updated, please reconnect.\n");


		     		break;

			}

	};
}
void func(int sockfd)
{
	char buff[MAX];
	int n;
	int id;
	float price;
	uint32_t temp;



	for (;;) {
		 //clrscr(); //clean

		char c = ' ';
		bzero(buff, MAX);
		printf("Enter the product number or command: \n");
		n = 0;
		while ((buff[n++] = getchar()) != '\n') //wprowadzanie tekstu
			;
		id=atoi(buff);
		if ((strncmp(buff, "exit", 4)) == 0) {  //jesli podane "exit" rozlacz sie z serwerem
		printf("Client Exit...\n");
		break;
		}
		if(strncmp(buff, "admin", 5)==0)  //jesli wpisane admin
       		 {

                write(sockfd, buff, sizeof(buff));  //wyslij slowo admin do serwera
                bzero(buff, sizeof(buff));  //czyszczenie bufora
                read(sockfd, buff, MAX);   //przeczyaj odpowiedz od serwera
                printf("\n %s\n", buff); //wyswietl odpowiedz serwera
 		bzero(buff, sizeof(buff));  //czyszczenie bufora

	            //wprowadzanie hasla
			 int k = 0;
			 while (k<=5){
   				 buff[k]=getch();
   				 c=buff[k];
   				 if(c==13) break;
  				 else printf("*");
  				  k++;
  			}



			write(sockfd, buff, MAX); //wyslanie hasla na serwer
			bzero(buff, MAX);  //czyszczenie bufora

			read(sockfd, buff, MAX);   //przeczyaj odpowiedz od serwera
			printf("\nOd serwera : %s\n", buff); //wyswietl odpowiedz serwera
		if(strncmp(buff, "Zalogowano", 10)==0)
		{
		adminPanel(sockfd); //jesli zalogowano to odpalamy funckje admina
		bzero(buff, MAX);

		break;
		}
		else
		{

		}

        }
        else if(lenHelper(id)==8){



		write(sockfd, buff, MAX);  //wysylanie podanej liczby
		bzero(buff, MAX);         //czyszczenie bufowa
		read(sockfd, buff, MAX);   //odczytywanie od serwera ID
		id = buff[0];                        //pobieranie do zmiennej
		printf("Product ID : %d\n", id);    //wyswietlanie

		bzero(buff, MAX);    //czyszczenie bufowa

		read(sockfd, buff, MAX);  //odczytywanie od serwera ceny(float)
		temp = ((buff[0] << 24) | (buff[1] << 16) | (buff[2] << 8) | buff[3]);  //konwertacja z tablicy na float
        	price = *((float *) &temp);   //przypisywanie z konwertacji
		printf("Product price : %.2f\n", price);   //wypisywnaie ceny float
		bzero(buff, MAX);    //czyszczenie bufowa



		read(sockfd, buff, MAX);  //odczytywanie od serwera nazwy
		printf("Product name : %s\n", buff);   //wypisywnaie nazwy
      	        bzero(buff, MAX); //czyszczenie bufora


        }
        else{
            printf("Nie ma takiego produktu!\n");
        }




	}
}



int main(int argc, char* argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;
	struct in_addr in;

	int port;

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);


	 if(inet_aton(argv[1], &in) == 0 )
    {
        printf("Nie poprawny adres IP\n");
        exit(-1);
    }
    else
        servaddr.sin_addr.s_addr = in.s_addr;

    if((port=atoi(argv[2])) == 0)
    {
        printf("Nie mozna przekonwertowac numeru portu\n");
        exit(-1);
    }





	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	//  wpisz informacje o serwerze
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = in.s_addr;
	servaddr.sin_port = htons(port);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}
