#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>

int message_to_main_ser(char message[])
{

    int skt_desc;
        struct sockaddr_in ser_addr;
        char ser_msg[2000], cli_msg[2000];

                    
        
        //Flushing Buffers
        
        memset(ser_msg,'\0',sizeof(ser_msg));
        memset(cli_msg,'\0',sizeof(cli_msg));
        
        //Creating Socket
        
        skt_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(skt_desc < 0)
        {
                printf("Socket Not Created!\n");
                return -1;
        }
        
        printf("Socket is Created\n");
        
     
        
        ser_addr.sin_family = AF_INET;
        ser_addr.sin_port = htons(2001);
        ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        //connect()
        
        if(connect(skt_desc, (struct sockaddr*)&ser_addr, sizeof(ser_addr)) < 0)
        {
                printf("Failed to Connect!");
                return -1;
        }
        
        printf("Connected\n");
        
        //Send to main server
        
        strcpy(ser_msg,message);
        printf("%s",ser_msg);

        if(send(skt_desc, ser_msg, strlen(ser_msg),0) < 0)
        {
                printf("Sending Failed!\n");
                return -1;
        }
        
        memset(ser_msg,'\0',sizeof(ser_msg));
        memset(cli_msg,'\0',sizeof(cli_msg));
        
        //Close sokcet
        
        close(skt_desc);
        
        return 0;
}

struct cli_information
{
    int socket;
    int port_number;
    char ip_addr[10];
    struct cli_information* l;
};



void *cli_t_func (void* c_info)    //function to be executed
{

	char buffer[256];
	bzero(buffer,256);
	char SS[256];
          bzero(SS,256);
          
          int count[4];
          int ans[1];
          ans[0] = 0;
          bzero(count,4);
          bzero(ans,1);
		int n;

    
    char ser_msg[2000], cli_msg[2000],port_buffer[7];
    struct cli_information *info=(struct cli_information*) c_info;
    int cli_socket=info->socket;
    printf("\nSocket: %i",cli_socket);
    printf("\nPort: %i",info->port_number);
    printf("\nIP: %s",info->ip_addr);
    
    char topic_name[]="Enter your topic name:\nMemory Management\nIO Management \nDisk Scheduling\n";
    
    //Flushing Buffers

    memset(ser_msg,'\0',sizeof(ser_msg));
    memset(cli_msg,'\0',sizeof(cli_msg));
    
    strcpy(ser_msg,topic_name);
    if (send(cli_socket, ser_msg, strlen(ser_msg),0)<0)
    {
        printf("Sending Failed.\n");
        return;
    }
    
    //Receiving

        if (recv(cli_socket, cli_msg, sizeof(cli_msg),0) < 0)
        {
                printf("Receivig Failed.\n");
                return;
        }


        
        printf("Message from Client: %s\n",cli_msg);
        
    
        memset(port_buffer,'\0',sizeof(port_buffer));
        
         if(strcmp(cli_msg,"Disk Scheduling")==0)        
         {              
               
                      
              int i;
              char topic_name[3][500]  ={
              "\nQuestion 1. Which disk scheduling algorithm is poor for database systems?\nA. SSTF\nB. FIFO\nC. PRI\nD. SCAN\nType your answer : ",
              "\nQuestion 2. Which level of RAID is not a true RAID?\nA. 0\nB. 1\nC. 2\nD. 3\nType your answer : ",
              "\nQuestion 3. In which level of RAID a Hamming code is used?\nA. 0\nB. 1\nC. 2\nD. 3\nType your answer : "
              };      
              
              
              char* answers[]={"C","A","C"};
              
              for(i=0;i<3;i++){		 
                                                                                     
            
              memset(ser_msg,'\0',sizeof(ser_msg));	   
             memset(cli_msg,'\0',sizeof(cli_msg));    	  
                                                                                      	       
             strcpy(ser_msg,topic_name[i]);	    
                                                                                      	       
	 if (send(cli_socket, ser_msg, strlen(ser_msg),0)<0)	 
	{	        
	printf("Sending Failed!\n");	        
	return;	    
	}   

  	if (recv(cli_socket, cli_msg, sizeof(cli_msg),0) < 0)        
  	{                
  	printf("Receiving Failed.\n");                
  	return;        
  	} 
  	
  	printf("Message from Client: %s\n",cli_msg);    
  	
		if(strcmp(cli_msg,answers[i])==0){		
		count[i] = 1;		
		}
		else{
		count[i] = 0;
		} 
		 
		
       	} 
       	for(int j=0;j<3;j++){
		   printf("\ncount = %d \n",count[j]);
		   
		}  
		strcpy(cli_msg,"Disk Scheduling");
		                                      
       	 sprintf(port_buffer, "%d", info->port_number);         
       	    strcpy(ser_msg,info->ip_addr);            
       	    strcat(ser_msg,",");            
       	    strcat(ser_msg,port_buffer);            
       	    strcat(ser_msg,",OS,");            
       	    strcat(ser_msg,cli_msg); 
       	                                                        
       	     } 
        else if( strcmp(cli_msg,"IO Management")==0){
        
                      
              int i;
              char topic_name[3][500]  ={
              "\nQuestion 1. Which of these is not a human readable device\nA. Mouse\nB. Keyboard\nC. Sensor\nD. Terminal\nType your answer : ",
              "\nQuestion 2. Which of these is a machine readable device?\nA. Mouse\nB. Keyboard\nC.Terminal\nD. None\nType your answer : ",
              "\nQuestion 3. Which of these are Block-oriented device?\nA. USB keys\nB. Disks\nC.Both\nD. None\nType your answer : ",
              };      
              
              
              char* answers[]={"C","D","C"};
              
              for(i=0;i<3;i++){		 
                                                                                     
              memset(ser_msg,'\0',sizeof(ser_msg));	   
             memset(cli_msg,'\0',sizeof(cli_msg));    	  
		strcpy(ser_msg,topic_name[i]);	    
                                                                                      	       
 if (send(cli_socket, ser_msg, strlen(ser_msg),0)<0)	 
{	        
printf("Sending Failed.\n");	        
return;	    
}   

  if (recv(cli_socket, cli_msg, sizeof(cli_msg),0) < 0)        
  {                
  printf("Receiving Failed.\n");           
  return;        
  } 
    	printf("Message from Client: %s\n",cli_msg);            
  		                 
  
		if(strcmp(cli_msg,answers[i])==0){		
		count[i] = 1;		
		}
		else{
		count[i] = 0;
		} 
		 
       	} 
       	for(int j=0;j<3;j++){
		   printf("\ncount = %d \n",count[j]);
		   
		}  
		strcpy(cli_msg,"IO Management ");
		                                        
       	 sprintf(port_buffer, "%d", info->port_number);         
       	    strcpy(ser_msg,info->ip_addr);            
       	    strcat(ser_msg,",");            
       	    strcat(ser_msg,port_buffer);            
       	    strcat(ser_msg,",OS,");            
       	    strcat(ser_msg,cli_msg); 
       	    
        }
        else if(strcmp(cli_msg,"Memory Management")==0){
                     
              int i;
              char topic_name[3][500]  ={
              "\nQuestion 1. What happens when we use dynamic partioning?\nA. Internal Fragmentation\nB. External Fragmentation\nC. Both\nD. None\nType your answer : ",
              "\nQuestion 2. What happens when we use fixed partioning?\nA. Internal Fragmentation\nB. External Fragmentation\nC. Both\nD. None\nType your answer : ",
              "\nQuestion 3. What is Actual location in main memory?\nA. Logical Address\nB. Physical Address\nC. Relative Address\nD. None\nType your answer : "
              };      
              
              
              char* answers[]={"B","A","B"};
              
              for(i=0;i<3;i++){		 
                                                                                     
              memset(ser_msg,'\0',sizeof(ser_msg));	   
             memset(cli_msg,'\0',sizeof(cli_msg));    	  
                                                                                      	      
	 strcpy(ser_msg,topic_name[i]);	    
                                                                                      	       
 if (send(cli_socket, ser_msg, strlen(ser_msg),0)<0)	 
{	        
printf("Sending Failed.\n");	        
return;	    
}   

  if (recv(cli_socket, cli_msg, sizeof(cli_msg),0) < 0)        
  {                
  printf("Receiving Failed\n");                
  return;        
  }  
    	printf("Message from Client: %s\n",cli_msg);
		if(strcmp(cli_msg,answers[i])==0){		
		count[i] = 1;		
		}
		else{
		count[i] = 0;
		} 
		 
		
       	} 
       	for(int j=0;j<3;j++){
		   printf("\ncount = %d \n",count[j]);
		   
		}  
		strcpy(cli_msg,"Memory Management");
		                                      
       	 sprintf(port_buffer, "%d", info->port_number);         
       	    strcpy(ser_msg,info->ip_addr);            
       	    strcat(ser_msg,",");            
       	    strcat(ser_msg,port_buffer);            
       	    strcat(ser_msg,",OS,");            
       	    strcat(ser_msg,cli_msg); 
       	    
        }
        else
            strcpy(ser_msg, "Input is Invalid!");
        

         for(int j=0;j<3;j++){
		   
		   ans[0] = ans[0] + count[j];
	}
	printf("\nTotal : %d\n",ans[0]);
	 sprintf(SS, "%d", ans[0]);
	  strcat(ser_msg,",");
	strcat(ser_msg,SS);
        //Send
        if (send(cli_socket, ser_msg, strlen(ser_msg),0)<0)
        {
                printf("Sending Failed.\n");
                return;
        }
        
        if(message_to_main_ser(ser_msg)==-1)
            return -1;
    
    close(cli_socket);
    free(info->l);
    pthread_exit(NULL); 
}

int client_connection(char my_ip[], char my_port[])
{   
    int port_number=atoi(my_port);
    
    
    int skt_desc, cli_socket, cli_size; 
        struct sockaddr_in ser_addr, client_addr;
        pthread_t t;
        
        //socket create
        
        skt_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(skt_desc < 0)
        {
                printf("Socket not created\n");
                return -1;
        }
        
        printf("Socket is Created\n");
        
        //Binding 
        
        ser_addr.sin_family = AF_INET;
        ser_addr.sin_port = htons(port_number);
        ser_addr.sin_addr.s_addr = inet_addr(my_ip);
        
        if(bind(skt_desc, (struct sockaddr*)&ser_addr, sizeof(ser_addr))<0)
        {
                printf("Binding Failed\n");
                return -1;
        }        
        
        printf("Binding Done successfully\n");
        
        //Listen..
        
        if(listen(skt_desc, 1) < 0)
        {
                printf("Listening Failed!\n");
                return -1;
        }
        
        printf("Listening...\n");
        
        
        while(1)
        {
            //Accept
            

            cli_size = sizeof(client_addr);
            cli_socket = accept(skt_desc, (struct sockaddr*)&client_addr, &cli_size);

            if (cli_socket < 0)
            {
                    printf("Accepting failed!\n");
                    return -1;
            }
            else
            {
                struct cli_information *info;
                info=malloc(sizeof(struct cli_information));
                strcpy(info->ip_addr,inet_ntoa(client_addr.sin_addr));
                info->port_number=ntohs(client_addr.sin_port);
                info->socket=cli_socket;
                info->l=info;
                
                int r = pthread_create(&t, NULL, cli_t_func, (void *)info);    	/// pointer,NULL,function to be called, function args
                if (r!=0)
                {
                    printf("Thread not created\n");
                }
            }


        }
              
        //sokcet close


        close(skt_desc);
        pthread_exit(NULL); 
    
    return 0;
}


int main(int argc, char** argv) {

    char message[100];
    char course[]="OS";
    char my_ip[]="127.0.0.1";
    char my_port[]="2020";
    
    memset(message,'\0',sizeof(message));

    strcpy(message,course);
    strcat(message,",");
    strcat(message,my_ip);
    strcat(message,",");
    strcat(message,my_port);
        
    if(message_to_main_ser(message)==-1)
        return -1;
    
    client_connection(my_ip,my_port);

    
    return (EXIT_SUCCESS);
}
