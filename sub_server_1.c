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
     
    char topic_name[]="Enter your topic name:\nEthernet\nWireless\nInternetworking\n";
    
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
        
         if(strcmp(cli_msg,"Internetworking")==0)        
         {              
              //memset(server_message,'\0',sizeof(server_message)); 
                      
              int i;
              char topic_name[3][500]  ={
              "\nQuestion 1. Which protocol is the most important tool to build scalable and hetrogenous network\nA. TCP\nB. UDP\nC. IP\nD. HTTP\nType your answer : ",
              "\nQuestion 2. What is full form of CIDR?\nA. Classless Interdomain Routing\nB. Classlful Interdomain Routing\nC. Classless Intradomain Routing\nD. Classless Interdirecting Routing\nType your answer : ",
              "\nQuestion 3. What is the maximum transmission unit for ethernet?\nA. 1000 bytes\nB. 1500 bytes\nC. 2000 bytes\nD. 2500 bytes\nType your answer : "
              };      
              
              
              char* answers[]={"C","A","B"};
              
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
       	    strcat(ser_msg,",CN,");            
       	    strcat(ser_msg,cli_msg); 
       	                                                        
       	     }
        else if( strcmp(cli_msg,"Wireless")==0){
        //memset(server_message,'\0',sizeof(server_message)); 
                      
              int i;
              char topic_name[3][500]  ={
              "\nQuestion 1. What is the approx range of Wi-fi\nA. 50m\nB. 100m\nC. 150m\nD. 200m\nType your answer : ",
              "\nQuestion 2. What uses n bit chipping codes?\nA. DSSS\nB. FHSS\nC. Both\nD. None\nType your answer : ",
              "\nQuestion 3. How IEEE 802.11 avoid collision?\nA. MACA\nB. DACA\nC. FACA\nD. HACA\nType your answer : "
              };      
              
              
              char* answers[]={"B","A","A"};
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
       	    strcat(ser_msg,",CN,");            
       	    strcat(ser_msg,cli_msg); 
       	                                                        
       	     }
        else if(strcmp(cli_msg,"Ethernet")==0){
            //memset(server_message,'\0',sizeof(server_message)); 
                      
              int i;
              char topic_name[3][500]  ={
              "\nQuestion 1. Ethernet uses which type of encoding schemes\nA. Manchester\nB. 4B/5B\nC. 8B/10B\nD. All of these\nType your answer : ",
              "\nQuestion 2. How many bits are assignd as prefix of ethernet address by AMD\nA. 16\nB. 24\nC. 32\nD. 8\nType your answer : ",
              "\nQuestion 3. What is the maximum transmission unit for ethernet?\nA. 1000 bytes\nB. 1500 bytes\nC. 2000 bytes\nD. 2500 bytes\nType your answer : "
              };      
              
              
              char* answers[]={"D","B","B"};
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
       	    strcat(ser_msg,",CN,");            
       	    strcat(ser_msg,cli_msg); 
       	                                                        
       	     }
        else
            strcpy(ser_msg, "Input is Invalid!");
        

         for(int j=0;j<3;j++){
		   
		   ans[0] = ans[0] + count[j];
	}
	printf("Total : %d\n",ans[0]);
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
    char course[]="CN";
    char my_ip[]="127.0.0.1";
    char my_port[]="2010";
    
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
