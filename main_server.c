
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>
#include <pthread.h>


int format_chk(char st[])    /// checking ','
{
    int i=0;
    int count=0;
    for(i=0;i<strlen(st);i++)
    {
        if(st[i]==',')
            count++;
    }
    return count;
}

void *ss_t_func (int *cli_socket)
{

    char ser_msg[2000], cli_msg[2000];

    //Flushing Buffers

    memset(ser_msg,'\0',sizeof(ser_msg));
    memset(cli_msg,'\0',sizeof(cli_msg));


    if (recv(cli_socket, cli_msg, sizeof(cli_msg),0) < 0)
    {
            printf("Recieving failed!\n");
            return;
    }


    printf("\n Message from Client: %s\n",cli_msg);
    
    if(format_chk(cli_msg)==2)       //append in ss_info file
    {
        FILE *ss_info_file;
        ss_info_file = fopen("ss_info.txt", "a");   //open in append mode
        char new_entry[200];

        strcpy(new_entry, cli_msg);
        strcat(new_entry, "\n");

        fputs(new_entry, ss_info_file);
        fclose(ss_info_file);

    }
    else if(format_chk(cli_msg)==4)
    {
        FILE *cli_rec_file;
        cli_rec_file = fopen("cli_rec.txt", "a");
        char new_entry[200];

        strcpy(new_entry, cli_msg);
        strcat(new_entry, "\n");


        fputs(new_entry, cli_rec_file);
        fclose(cli_rec_file);
    }
    else
        printf("\nMessage format not correct");

    

    memset(ser_msg,'\0',sizeof(ser_msg));
    memset(cli_msg,'\0',sizeof(cli_msg));

    //socket close

    close(cli_socket);
    
    pthread_exit(NULL);       
}

int get_SS_info(char test_name[],char* info)               /////checking input whether it is valid or not (tried for error handling)
{
    memset(info,'\0',sizeof(info));
    
    FILE *fp;
    char st[100];
    
    fp = fopen("ss_info.txt", "r");
    if (fp == NULL){
        printf("File not open\n");
        return 1;
    }
    int flag=0;
    while (fgets(st, sizeof(st), fp) != NULL)
    {
        int i=0;
        flag=1;
        while(i<strlen(test_name))
        {
            if(st[i]!=test_name[i])
            {
                flag=0;
                break;
            }
            i++;
        }
        if(flag==1)
        {    
            strcpy(info,st);
         
            
            return 0;
        }
    }
    fclose(fp);
    return 1;

    
}


void *cli_t_func (int *cli_socket)
{

    char ser_msg[2000], cli_msg[2000];
    char st[]="Enter course name:\nCN\nOS\n\n";

    //Flushing Buffers

    memset(ser_msg,'\0',sizeof(ser_msg));
    memset(cli_msg,'\0',sizeof(cli_msg));
    
    strcpy(ser_msg,st);
    if (send(cli_socket, ser_msg, strlen(ser_msg),0)<0)
    {
        printf("Sending failed!\n");
        return;
    }

     if (recv(cli_socket, cli_msg, sizeof(cli_msg),0) < 0)
        {
                printf("Receiving Failed!\n");
                return;
        }

       
        printf("Message from client: %s\n",cli_msg);
		
        if(get_SS_info(cli_msg,ser_msg)==1)
            strcpy(ser_msg, "Input is invalid");
        

        //Send the message back to client
        if (send(cli_socket, ser_msg, strlen(ser_msg),0)<0)
        {
                printf("Sending failed\n");
                return;
        }

        memset(ser_msg,'\0',sizeof(ser_msg));
        memset(cli_msg,'\0',sizeof(cli_msg));


    //close socket
    close(cli_socket);
    
    pthread_exit(NULL);       
}


void *ss_func (int *s_skt_desc)
{
    
    int cli_socket, cli_size; 
    struct sockaddr_in cli_addr;
    char ser_msg[2000], cli_msg[2000];
    pthread_t t4;
    
    //Flushing buffers

    memset(ser_msg,'\0',sizeof(ser_msg));
    memset(cli_msg,'\0',sizeof(cli_msg));

    
    while(1){


        //Accepting

        cli_size = sizeof(cli_addr);
        cli_socket = accept(s_skt_desc, (struct sockaddr*)&cli_addr, &cli_size);

        if (cli_socket < 0)
        {
                printf("Accept not done!\n");
                return;
        }
        else
        {
            
            int r = pthread_create(&t4, NULL, ss_t_func, (int*)cli_socket);
            if (r!=0)
            {
                            printf("Thread not created\n");
            }
        }

        printf("A Client is Connected --> Port No: %i\n",ntohs(cli_addr.sin_port));

        
    }
    close(s_skt_desc);
    pthread_exit(NULL);    
}
void *cli_func (int *skt_desc)
{

    int cli_socket, cli_size; 
    struct sockaddr_in cli_addr;
    char ser_msg[2000], cli_msg[2000];
    pthread_t t3;
    
    //flushing buffer

    memset(ser_msg,'\0',sizeof(ser_msg));
    memset(cli_msg,'\0',sizeof(cli_msg));

    
    while(1){


        //Accepting

        cli_size = sizeof(cli_addr);
        cli_socket = accept(skt_desc, (struct sockaddr*)&cli_addr, &cli_size);

        if (cli_socket < 0)
        {
                printf("Accept not done!\n");
                return;
        }
        else
        {
            
            int r = pthread_create(&t3, NULL, cli_t_func, (int*)cli_socket);
            if (r!=0)
            {
                            printf("Thread not created\n");
            }
        }

        printf("A Client is Connected --> Port No: %i\n",ntohs(cli_addr.sin_port));

        
    }
    close(skt_desc);
    pthread_exit(NULL);   
}

int main(int argc, char** argv) {

    
    int skt_desc, s_skt_desc, cli_socket, cli_size; 
    struct sockaddr_in ser_addr, s_ser_addr, cli_addr;
    pthread_t t1,t2;

    //Creating Socket

    skt_desc = socket(AF_INET, SOCK_STREAM, 0);
    s_skt_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(skt_desc < 0)
    {
            printf("Socket not created!\n");
            return -1;
    }
    
    printf("Created a  main server Socket \n");
    
    if(s_skt_desc < 0)
    {
            printf("Sub Socket not created!\n");
            return -1;
    }


    printf("Created a sub server Socket\n");

    //Binding

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(2000);
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    s_ser_addr.sin_family = AF_INET;
    s_ser_addr.sin_port = htons(2001);
    s_ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(skt_desc, (struct sockaddr*)&ser_addr, sizeof(ser_addr))<0)
    {
            printf("Bind not done!\n");
            return -1;
    }        

    printf("Binding successful\n");
    
    if(bind(s_skt_desc, (struct sockaddr*)&s_ser_addr, sizeof(s_ser_addr))<0)
    {
            printf("Sub Bind not done!\n");
            return -1;
    }        

    printf("Sub Binding successful\n");

    //listen

    if(listen(skt_desc, 1) < 0)
    {
            printf("Listening not done!\n");
            return -1;
    }

    printf("Listening...\n");
    
    if(listen(s_skt_desc, 1) < 0)
    {
            printf("Sub Listening not done!\n");
            return -1;
    }

    printf("Sub Listening...\n");

    
    int r1 = pthread_create(&t1, NULL, ss_func, (int*)s_skt_desc);   /// thread for sub server
    if (r1!=0)
    {
                    printf("Thread for sub server not created\n");
    }
    int r2 = pthread_create(&t2, NULL, cli_func, (int*)skt_desc); /// thread for client
    if (r2!=0)
    {
                    printf("Thread for client not created\n");
    }
    
    
    
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    
    //Close socket

    //close(cli_socket);
    
    close(skt_desc);
    pthread_exit(NULL); //Terminates the parent thread
    
    return (EXIT_SUCCESS);
}

