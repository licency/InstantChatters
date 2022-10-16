///////////////////////////////////server/////////////////////////////////////////
#include"../header/sheader.h"

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
void send_individual_client_message(char *s, int uid)
{
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i<MAX_CLIENTS; ++i)
	{
		if(clients[i])
		{
			if(clients[i]->uid == uid)
			{
				if(write(clients[i]->sockfd, s, strlen(s)) < 0)
				{
					perror("ERROR: write to descriptor failed");
					break;
				}
			}
		}
	}
	pthread_mutex_unlock(&clients_mutex);
}


void *handle_client(void *arg)
{
	char buff_out[BUFFER_SZ];
	char name[32];  
	int leave_flag = 0;

	FILE *fp,*fpass;

	
	cli_count++;
	client_t *cli = (client_t *)arg;

	// Name of client 
	if(recv(cli->sockfd, name, 32, 0) <= 0 || strlen(name) <  2 || strlen(name) >= 32-1)
	{
	//	printf("Name should be greater than 2 and smaller than 32 characters. Try rejoining ...\n");
		leave_flag = 1;
	} 
	else
	{
		strcpy(cli->name, name);

		int count =0; //name is done 0 for pass 

		bzero(buff_out, BUFFER_SZ);
		
		while(1){
				if (leave_flag) 
				{
					break;
				}

				int receive = recv(cli->sockfd, buff_out, BUFFER_SZ, 0);
				if (receive > 0)
				{
						if(count==0)
						{
							bzero(buff_out,BUFFER_SZ);
							sprintf(buff_out,"name is taken already. Enter the pass now %s :",cli->name);
							send_individual_client_message(buff_out,cli->uid);
							bzero(buff_out,BUFFER_SZ);

							recv(cli->sockfd,buff_out,BUFFER_SZ,0);
							strcpy(cli->pass,buff_out);
							bzero(buff_out,BUFFER_SZ);
							printf("pass taken pass = %s \n",cli->pass);

							sprintf(buff_out,"%s are u new user or old ? give 'o' or 'n' only :  ",cli->name);
							send_individual_client_message(buff_out,cli->uid);
							bzero(buff_out,BUFFER_SZ);

							char chc[32];
							recv(cli->sockfd,chc,32,0);
							printf("  chc = %s  ", chc);

							count++;
							char d; d= chc[strlen(chc)-2];    printf("  d= %c  \n",d);
								if(d=='n')
								{
									fpass= fopen("../data/passfile.txt","a+");
									fputs(cli->pass,fpass);
									fputs("\n",fpass);
									fclose(fpass);
								}
								else 
								{
									int flag=0;

//open file of password and check if name and password is correct
									fpass = fopen("../data/passfile.txt","r");
									while(1)
									{
										char pass_str[100];

										if(fgets(pass_str,100,fpass)==NULL)
											break;
										else 
										{		
											if(strcmp(cli->pass,pass_str)==0)
											{
												flag=0;
												printf("Found \n"); 
												break;
											}
											else flag=1;
										}
									}

									if(flag==1)
									{
							//printf("Destroy the thread here  match not found \n");
										bzero(buff_out,BUFFER_SZ);
										sprintf(buff_out,"%s denied joining, pass wrong ",cli->name);
										send_individual_client_message(buff_out,cli->uid);
										bzero(buff_out,BUFFER_SZ);
										close(cli->sockfd);
  										queue_remove(cli->uid);
										free(cli);
  										cli_count--;
  										pthread_detach(pthread_self());

										return NULL;
									}

								}

  //     pthread_mutex_unlock(&clients_mutex);		}

						if(strlen(buff_out) > 0 && count==1){
				
						//new 4 lines
							bzero(buff_out,BUFFER_SZ);
							sprintf(buff_out,"%s Thanks for credentials , Enjoy chatting !!! \n",cli->name);
							send_individual_client_message(buff_out,cli->uid);
							bzero(buff_out,BUFFER_SZ);
							count++;
				
						}



						if(strlen(buff_out) > 0 && count>1){
					
				
							send_message(buff_out, cli->uid);

							str_trim_lf(buff_out, strlen(buff_out));
	
			
						//maintaining chat history inside txt file			
							fp =fopen("../data/logfile.txt","a+");
							fputs(buff_out , fp);
							fputs("\n",fp);
							fclose(fp);



						}
			} else if (receive == 0 || strcmp(buff_out, "exit") == 0){
					sprintf(buff_out, "%s has left\n", cli->name);
					printf("%s", buff_out);
					send_message(buff_out, cli->uid);
					leave_flag = 1;
			} else {
					printf("ERROR: -1\n");
					leave_flag = 1;
				}

			bzero(buff_out, BUFFER_SZ);
			}

  /* Delete client from queue and yield thread */
			close(cli->sockfd);
			queue_remove(cli->uid);
			free(cli);
 			cli_count--;
 			pthread_detach(pthread_self());

			return NULL;
		}

return NULL;

}


void str_overwrite_stdout() {
    printf("\r%s", "> ");
    fflush(stdout);
}

void str_trim_lf (char* arr, int length) {
  int i;
  for (i = 0; i < length; i++) { // trim \n
    if (arr[i] == '\n') {
      arr[i] = '\0';
      break;
    }
  }
}

//when max clients added, then show this client cannot be added 
void print_client_addr(struct sockaddr_in addr){
    printf("%d.%d.%d.%d",
        addr.sin_addr.s_addr & 0xff,
        (addr.sin_addr.s_addr & 0xff00) >> 8,
        (addr.sin_addr.s_addr & 0xff0000) >> 16,
        (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

/* Add clients to queue */
void queue_add(client_t *cl){
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i < MAX_CLIENTS; ++i){
		if(!clients[i]){
			clients[i] = cl;
			break;
		}
	}




	//////////////adding active list///////////////
	printf("\n Active users list is from queue Add :  \n");
	for(int i=0; i < MAX_CLIENTS; ++i){
		if(clients[i]!=NULL){
			printf("%s ",clients[i]->name);
	
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

/* Remove clients to queue */
void queue_remove(int uid){
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i < MAX_CLIENTS; ++i){
		if(clients[i]){
			if(clients[i]->uid == uid){
				clients[i] = NULL;
				break;
			}
		}
	}
	
	//////////////adding active list///////////////
	printf("\n Active users list from queue remove is :  \n");
	for(int i=0; i < MAX_CLIENTS; ++i){
		if(clients[i]!=NULL){
			printf("%s ",clients[i]->name);
	
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

/* Send message to all clients except sender */
void send_message(char *s, int uid){
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i<MAX_CLIENTS; ++i){
		if(clients[i]){
			if(clients[i]->uid != uid){
				if(write(clients[i]->sockfd, s, strlen(s)) < 0){
					perror("ERROR: write to descriptor failed");
					break;
				}
			}
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}








int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: %s <port>\n", argv[0]);
		return EXIT_FAILURE;
	}

	char *ip = "127.0.0.1";
	int port = atoi(argv[1]);
	int option = 1;
	int listenfd=0, connfd = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	pthread_t tid;

  /* Socket settings */
  	listenfd = socket(AF_INET, SOCK_STREAM, 0);   
  	serv_addr.sin_family = AF_INET;
  	serv_addr.sin_addr.s_addr = inet_addr(ip);
  	serv_addr.sin_port = htons(port);

  /* Ignore pipe signals */
	signal(SIGPIPE, SIG_IGN);

//setsockopt to control socket behaviour 

	if(setsockopt(listenfd, SOL_SOCKET,( SO_REUSEADDR),(char*)&option,sizeof(option)) < 0){
			perror("ERROR: setsockopt failed");
		        return EXIT_FAILURE;
	}

	/* Bind */
  	if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    		perror("ERROR: Socket binding failed");
    		return EXIT_FAILURE;
  	}

  /* Listen   (listenfd, 10 = backlog amount to maintain queue, if lot of clients wants to listen at a time ) */
  	if (listen(listenfd, 10) < 0) {
    		perror("ERROR: Socket listening failed");
    		return EXIT_FAILURE;
	}
//printf("\n----listen called already---\n");
	
	printf("=== WELCOME TO THE CHATROOM ===\n");

	while(1){
			socklen_t clilen = sizeof(cli_addr);

			connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);  //at this point it will not go further unless it has accepted new client 
	
			/* Check if max clients is reached */
			if((cli_count + 1) == MAX_CLIENTS){
				printf("Max clients reached. Rejected: ");
				print_client_addr(cli_addr);  // in case of max clients reached show that this client whose address is this cannot connect.
				printf(":%d\n", cli_addr.sin_port);
				close(connfd);
				continue;
			}

		/* Client settings */
		client_t *cli = (client_t *)malloc(sizeof(client_t));
		cli->address = cli_addr;
		cli->sockfd = connfd;
		cli->uid = uid++;

		/* Add client to the queue and fork thread */
		print_client_addr(cli_addr);



		queue_add(cli);

		pthread_create(&tid, NULL, &handle_client, (void*)cli);
		











		/* Reduce CPU usage */
		sleep(1);
	}

	return EXIT_SUCCESS;
}

