#include"try.h"

int client();
int server();

int error();
void send_file(FILE *fp, int sockfd);
void write_file(int sockfd);


int main()
{
    char mode[3]; //default no connection needed or abort
    char ping[2] ;//success or failure yes or no
    int flag,loop;
    printf("do you want to continue with client server connection?[y or n]\n");
    scanf("%s",mode);
    if(( strcmp(mode,"n")==0)&&(strcmp(ping,"n")==0))
    {
        flag =0;
    }
    if(( strcmp(mode,"n")==0)&&(strcmp(ping,"y")==0))
    {
        flag =1;
    }
    if(( strcmp(mode,"y")==0)&&(strcmp(ping,"n")==0))
    {
        flag =2;
    }
    if(( strcmp(mode,"y")==0)&&(strcmp(ping,"y")==0))
    {
        flag =3;
    }

    
    if(strcmp(mode,"y")==0)
    {
        char choice[3];
        printf("How do you want to continue? as server please press s as client please press c");
        scanf(" %s",choice);
        // char *ip = "192.168.60.41";
        char sip[200];
        // printf("Enter ip address of the client which is sending file system {other system }\n");

        // scanf("%s",sip);
        // char *ip = "192.168.60.79";
        char rip[200];
        
        // printf("enter  ip address of the server which is reciving {your system}\n");
        // scanf("%s",rip);
        
        










        if(flag==3){printf("connection is established but user is ready to connect\n");}
        if(strcmp(choice,"s")==0)
        {
            server();
        }
        else if (strcmp(choice,"c")==0)

        {
            client();
        }


    }
  
    else if(flag==0)
    
    {printf("connection is not established and user refused to connect\n");}
    else if(flag==1){printf("connection is established but user refused to connect\n");}
    else if(flag==2){printf("USer wants communication but connection is not available");}
    else{printf("Sorry!connection is not established\n");}
    flag=4;
    return 0;

}



int client()
{
    // printf("im inside client\n");


    char *ip = "192.168.60.39";
    // char sip[200];
    // char *ip = sip;

  int port = 8080;
  int e;
 
  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
 char stringer[500];
 printf("enter the file name along with extension to be sent\n");
 scanf("%s",stringer);
  char *filename = stringer;
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
    perror("[-]Error in socket\n");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
//  printf("The connection has been established succesfully between client and server\n");
  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
 printf("[+]Connected to Server.\n");
  int flag=1; //connection is done

int loop;

  printf("number of loops\n");
  scanf("%d",&loop);
    
     for(int i=0;i<=loop;i++)
     {
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.\n");
    exit(1);
  }
 
  send_file(fp, sockfd);
  printf("[+]File data sent successfully.\n");
 
  printf("[+]Closing the connection.\n");
  if(flag==2){printf("The connection status is : communication done successfully\n");}
else if(flag==1) {printf("The connection status is : connected yet to communicate\n");}
else{printf("The connection status is : not connected\n");}
  close(sockfd);

     }


    return 0;
}
int server()
{
    {
// printf("im inside server\n");
  
  
  char *ip = "192.168.60.79";
    // char rip[200];
    //  char *ip = rip;
     int port = 8080;
     int e;
     int sockfd, new_sock;
     struct sockaddr_in server_addr, new_addr;
     FILE *fp;
     socklen_t addr_size;

     char buffer[SIZE];

    
    
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
    perror("[-]Error in socket\n");
    exit(1);


    }
    //  printf("The connection has been established succesfully between client and server");
    printf("[+]Server socket created successfully.\n");
   


   
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    
    e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e < 0) {
    perror("[-]Error in bind\n");
    exit(1);
  }
  printf("[+]Binding successfull.\n");
 int flag=1; //connection is done

int loop;

  printf("number of loops\n");
  scanf("%d",&loop);
    
     for(int i=0;i<loop;i++)
     {

if(listen(sockfd, 10) == 0){
 printf("[+]Listening....\n");
 flag=3; //connected but ready to communication
 }else
 {
 perror("[-]Error in listening\n");
    exit(1);
 }
 
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  write_file(new_sock);
  flag=2; //communication started and finished
  printf("[+]Data written in the file successfully.\n");
//   printf("number of loops");
//   scanf("%d",&loop);




  if(flag==2){printf("The connection status is : communication done successfully\n");}
else if(flag==1) {printf("The connection status is : connected yet to communicate\n");}
else{printf("The connection status is : not connected\n");}

     }



return 0;
}

}



void send_file(FILE *fp, int sockfd)
{
  int n;
  char data[SIZE] = {0};
 
  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) 
    {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

void write_file(int sockfd){
  int n;
  FILE *fp;
//   char *filename = "recv.txt";

char receiver[500];
   printf("enter the file name along with extension to be received\n");
 scanf("%s",receiver);
  char *filename = receiver;
  char buffer[SIZE];
 
  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  return;
}

