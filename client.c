
#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>

int main(int argc, char** argv) {


    
        int skt_desc;
        int skt_desc1;
        struct sockaddr_in ser_addr;
        struct sockaddr_in ser_addr1;
        char ser_msg[2000], cli_msg[2000];
            char buffer[256];
            int n;
        
        //Flushing Buffers
        
        memset(ser_msg,'\0',sizeof(ser_msg));
        memset(cli_msg,'\0',sizeof(cli_msg));
        
        //Creating Socket
        
        skt_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(skt_desc < 0)
        {
                printf("\nsocket not created!\n");
                return -1;
        }
        
        printf("\nSocket is Created\n");
        
   
        
        ser_addr.sin_family = AF_INET;
        ser_addr.sin_port = htons(2000);
        ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        //connect()
        
        if(connect(skt_desc, (struct sockaddr*)&ser_addr, sizeof(ser_addr)) < 0)
        {
                printf("\nConnection is Failed!");
                return -1;
        }
        
        printf("\nConnected successfully!\n");
        
        
        //Receiving
        
        if(recv(skt_desc, ser_msg, sizeof(ser_msg),0) < 0)
        {
                printf("\nReceiving failed\n");
                return -1;
        }
        
        printf("\nMessage from main server: \n%s\n",ser_msg);
        
      //input
        
        printf("\nEnter your course name: ");
        
        gets(cli_msg);
        
        //Send msg
        
        if(send(skt_desc, cli_msg, strlen(cli_msg),0) < 0)
        {
                printf("\nSending Failed!\n");
                return -1;
        }
        
        //Receiving
        
        memset(ser_msg,'\0',sizeof(ser_msg));
        
        if(recv(skt_desc, ser_msg, sizeof(ser_msg),0) < 0)
        {
                printf("\nReceiving Failed!\n");
                return -1;
        }
        

        printf("\nMessage from server: %s\n",ser_msg); 			 ///spliting the message
        
        char port_number[10],ip_address[20],course_name[10];
        
        int i=0;
        int j=0;
        for(i=0;ser_msg[i]!=',';i++)
        {
            course_name[i]=ser_msg[i];
        }
        i++;
        for(j=0;ser_msg[i]!=',';i++,j++)
        {
            ip_address[j]=ser_msg[i];
        }
        i++;
        for(j=0;ser_msg[i]!='\0';i++,j++)
        {
            port_number[j]=ser_msg[i];
        }
        
        
        int ss_port=atoi(port_number);
        
        printf("\nCourse Name:%s\n",course_name);
        printf("IP address:%s\n",ip_address);
        printf("Port Number: %i\n",ss_port);

        
        memset(ser_msg,'\0',sizeof(ser_msg));
        memset(cli_msg,'\0',sizeof(cli_msg));
        
        //socket close
        
        close(skt_desc);
        
        										//Creating Socket for sub server
        skt_desc1 = -1;
        skt_desc1 = socket(AF_INET, SOCK_STREAM, 0);
        
        if(skt_desc1 < 0)
        {
                printf("\nsocket not created!\n");
                return -1;
        }
        
        printf("\nSub Socket is Created\n");
        
       
        
        ser_addr1.sin_family = AF_INET;
        ser_addr1.sin_port = htons(ss_port);
        ser_addr1.sin_addr.s_addr = inet_addr("127.0.0.1");
        
      
         if(connect(skt_desc1, (struct sockaddr*)&ser_addr1, sizeof(ser_addr1)) < 0)
        {
                printf("\nSub server Connection Failed! ");
                return -1;
        }
      
        
        printf("\nConnected to Sub Server\n");
        
        //Flushing Buffers
        
        memset(ser_msg,'\0',sizeof(ser_msg));
        memset(cli_msg,'\0',sizeof(cli_msg));
        
        //Receiving
        
        if(recv(skt_desc1, ser_msg, sizeof(ser_msg),0) < 0)
        {
                printf("\nReceiving Failed!\n");
                return -1;
        }
        
        printf("\nMessage from Sub Server: \n%s\n",ser_msg);
        
        
        //Get Input 
        
        printf("\nEnter topic name: ");
       
        gets(cli_msg);
        
        //Send the message to Server
        
        if(send(skt_desc1, cli_msg, strlen(cli_msg),0) < 0)
        {
                printf("\nSub Server Send Failed!\n");
                return -1;
        }
        
       
        int z=0;
		for(z=0;z<3;z++){

                memset(ser_msg,'\0',sizeof(ser_msg));
                memset(cli_msg,'\0',sizeof(cli_msg));
                if(recv(skt_desc1, ser_msg, sizeof(ser_msg),0) < 0)
        {
                printf("\nReceiving Failed!\n");
                return -1;
        }
        printf("\nMessage from Sub Server: %s\n",ser_msg);
   

	gets(cli_msg);
        
        //Send the message to Server
        
        if(send(skt_desc1, cli_msg, strlen(cli_msg),0) < 0)
        {
                printf("\nSub Server Send Failed. Error!!!!\n");
                return -1;
        }
        
        
        
      }
      
        printf("\n\nQuiz Ended!\n");
        
        close(skt_desc1);
        
    
    
    return (EXIT_SUCCESS);
}
