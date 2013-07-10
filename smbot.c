#include "mysock/mysock.h"

#define SER "irc.freenode.org"
#define PORT 6667
#define NICK "NICK smbot\r\n"
#define USER "USER smbot sbmot irc.freenode.org :smbot\r\n"
#define JOIN "JOIN #linuxba\r\n"
#define MSG "PRIVMSG "
#define CHANNEL "#linuxba"

#define POST "POST /search.php HTTP/1.1\r\n"
#define HOST "Host: www.linuxmanpages.com\r\n"
#define CONNECTION "Connection: close\r\n"
#define CONTENT_TYPE "Content-Type: application/x-www-form-urlencoded\r\n"

void msgto(int sockfd,const char *channel,const char *nick,const char *msg)
{
	int len;
	char *buf;

	if(nick == NULL)
		len=strlen(MSG)+strlen(channel)+strlen(msg)+3;
	else
		len=strlen(MSG)+strlen(channel)+strlen(nick)+strlen(msg)+5;
	buf=malloc(len);
	bzero(buf,len);

	strncpy(buf,MSG,strlen(MSG));
	strncat(buf,channel,strlen(channel));
	strncat(buf," :",2);
	if(nick != NULL)
	{
		strncat(buf,nick,strlen(nick));
		strncat(buf,": ",2);
	}
	strncat(buf,msg,strlen(msg));

	send(sockfd,buf,strlen(buf),0);

	free(buf);
	buf=NULL;
}

char *get_nick(char *msg)
{
	char *buf=malloc(sizeof(int)*30);
	int i,j;

	for(i=1,j=0;msg[i];++i,++j)
		if(msg[i] == '!')
			break;
		else
			buf[j]=msg[i];

	buf[j]='\0';

	return buf;
}

int conect_man(char *url,int port)
{
	SA_IN server_addr;
	int sockfd;

	sockfd=Socket(AF_INET,SOCK_STREAM,0);
	init_data_with_client(&server_addr,url,port);
	Connect(sockfd,&server_addr);

	return sockfd;
}

char *get_man_url(int sockfd,char *msg)
{
	char *buf;
	char arg[2][20]={0};
	char *content_length="Content-Length: ";
	char *temp;
	char s_len[10];
	int len;
	int flags=0;
	int i,j;

	len=strlen("term=&section=&submitted=1");
	for(i=0;msg[i];++i)
		if(msg[i] == '!' && msg[i+1] == 'm' && msg[i+2] == 'a' && msg[i+3] == 'n')
			break;
	if(msg[i+4] == '\0'|| msg[i+4] == '\n' || msg[i+4] == '\r' || msg[i+4] != ' ')
		return "man <target>或者man [1-9] <target>\r\n";
	buf=msg+i+4;
	for(i=0;buf[i];++i)
		if(buf[i] == ' ')
			break;
	if(buf[i+1] >= '0' && buf[i+1] <= '9')
		flags=1;
	if(flags)
	{
		if(buf[i+2] != ' ')
			return "参数错误!\r\n";
		else
		{
			arg[0][0]=buf[i+1];
			arg[0][1]='\0';
		}

		for(buf=buf+3,i=0;buf[i];++i)
			if(buf[i] ==' ' || buf[i] == '\r')
				break;
		buf[i]='\0';
		strncpy(arg[1],buf,strlen(buf));
	}
	else
	{
		strncpy(arg[0],"-1",strlen("-1"));
		for(buf=buf+1,i=0;buf[i];++i)
			if(buf[i] == ' ' || buf[i] == '\r')
				break;
		buf[i]='\0';
		strncpy(arg[1],buf,strlen(buf));
	}

	len=len+strlen(arg[0])+strlen(arg[1]);
	sprintf(s_len,"%d",len);

	buf=malloc(len+5);
	bzero(buf,len+5);
	strncpy(buf,"term=",strlen("term="));
	strncat(buf,arg[1],strlen(arg[1]));
	strncat(buf,"&section=",strlen("&section="));
	strncat(buf,arg[0],strlen(arg[0]));
	strncat(buf,"&submitted=1",strlen("&submitted=1"));
	strncat(buf,"\r\n\r\n",strlen("\r\n\r\n"));

	temp=malloc(strlen(content_length)+strlen("\r\n\r\n")+strlen(s_len)+1);
	bzero(temp,strlen(content_length)+strlen("\r\n\r\n")+strlen(s_len)+1);
	strncpy(temp,content_length,strlen(content_length));
	strncat(temp,s_len,strlen(s_len));
	strncat(temp,"\r\n\r\n",strlen("\r\n\r\n"));

	send(sockfd,POST,strlen(POST),0);
	send(sockfd,HOST,strlen(HOST),0);
	send(sockfd,CONNECTION,strlen(CONNECTION),0);
	send(sockfd,CONTENT_TYPE,strlen(CONTENT_TYPE),0);
	send(sockfd,temp,strlen(temp),0);
	send(sockfd,buf,strlen(buf),0);

	free(buf);
	buf=NULL;
	free(temp);
	temp=NULL;

	while(buf=read_line(sockfd))
	{
		if(strstr(buf,"location: "))
			break;

		if(strstr(buf,"Sorry"))
		{
			free(buf);
			buf=NULL;
			
			return "Sorry,no result found!\r\n";
		}

		free(buf);
		buf=NULL;
	}

	if(buf == NULL)
		return "Sorry,no result found!\r\n";

	temp=malloc(strlen("http://www.linuxmanpages.com")+strlen(buf)-strlen("location: ")+3);
	bzero(temp,strlen("http://www.linuxmanpages.com")+strlen(buf)-strlen("location: ")+3);

	buf=buf+10;
	strncpy(temp,"http://www.linuxmanpages.com",strlen("http://www.linuxmanpages.com"));
	strncat(temp,buf,strlen(buf));
	strncat(temp,"\r\n",strlen("\r\n"));

	free(buf-10);
	buf=NULL;
	return temp;
}

char *query_ip(char *ip)
{
	int pipefd[2];
	char temp[200]={0};
	char *buf;
	int i,j;

	if(pipe(pipefd) == -1)
		return "创建管道失败!\r\n";

	for(i=0;ip[i];++i)
		if(ip[i] == '!' && ip[i+1] == 'i' && ip[i+2] == 'p')
			break;
	if(ip[i+3] == '\0' || ip[i+3] =='\r' || ip[i+3] != ' ')
		return "ip <ip address>\r\n";
	for(i+=4,j=0;ip[i];++i,++j)
		if(ip[i] == ' ' || ip[i] == '\r')
			break;
		else
			temp[j]=ip[i];

	if(fork() == 0)
	{
		close(pipefd[0]);

		dup2(pipefd[1],STDOUT_FILENO);
		dup2(pipefd[1],STDERR_FILENO);

		execl("./query_ip_addr","query_ip_addr",temp,NULL);
	}

	close(pipefd[1]);
	bzero(temp,sizeof(temp));

	read(pipefd[0],temp,sizeof(temp));
	buf=malloc(strlen(temp)+3);
	bzero(buf,strlen(temp)+3);
	strncpy(buf,temp,strlen(temp));
	strncat(buf,"\r\n",strlen("\r\n"));

	return buf;
}

char *get_time(void)
{
	time_t t;

	t=time(NULL);

	return ctime(&t);
}

char *dict(int sockfd,char *msg)
{
	char *buf;
	char temp[200]={0};
	char *get="GET /s?wd=";
	char *host="Host: dict.baidu.com\r\n";
	char *connection="Connection: close\r\n";
	char *content_type="Content-Type: */*\r\n\r\n";
	int len;
	int i,j;
	
	len=strlen(get)+strlen(" HTTP/1.1\r\n");
	for(i=0;msg[i];++i)
		if(msg[i] == '!' && msg[i+1] == 'd' && msg[i+2] == 'i' && msg[i+3] == 'c' && msg[i+4] == 't')
			break;
	if(msg[i+5] == '\0' || msg[i+5] == '\r' || msg[i+5] != ' ')
		return "dict <word>\r\n";

	for(i+=6,j=0;msg[i];++i,++j)
		if(msg[i] == ' ' || msg[i] == '\r')
			break;
		else
			temp[j]=msg[i];
	len+=strlen(temp);
	buf=malloc(len+1);
	bzero(buf,len+1);
	strncpy(buf,get,strlen(get));
	strncat(buf,temp,strlen(temp));
	strncat(buf," HTTP/1.1\r\n",strlen(" HTTP/1.1\r\n"));

	send(sockfd,buf,strlen(buf),0);
	send(sockfd,host,strlen(host),0);
	send(sockfd,connection,strlen(connection),0);
	send(sockfd,content_type,strlen(content_type),0);

	free(buf);
	buf=NULL;

	while(buf=read_line(sockfd))
	{
		if(strstr(buf,"dict-en-simplemeans-word"))
			break;
		if(strstr(buf,"dict-en-simplemeans-english"))
			break;

		free(buf);
		buf=NULL;
	}

	if(buf == NULL)
		return "Sorry,no result found!\r\n";
	bzero(temp,sizeof(temp));

	if(strstr(buf,"dict-en-simplemeans-word"))
	{
		for(i=0;buf[i];++i)
			if(buf[i] == 'w' && buf[i+1] == 'd' && buf[i+2] == '=')
				break;
		for(;buf[i];++i)
			if(buf[i] == '"' && buf[i+1] == '>')
				break;
		for(j=0,i+=2;buf[i];++i,++j)
			if(buf[i] == '<')
				break;
			else
				temp[j]=buf[i];
		free(buf);
		buf=NULL;

		buf=malloc(strlen(temp)+3);
		bzero(buf,strlen(temp)+3);
		strncpy(buf,temp,strlen(temp));
		strncat(buf,"\r\n",strlen("\r\n"));
		
		return buf;
	}

	if(strstr(buf,"dict-en-simplemeans-english"))
	{
		for(i=0;buf[i];++i)
			if(buf[i] == 's' && buf[i+1] == 'p' && buf[i+2] == 'a' && buf[i+3] == 'n')
				break;
		for(i+=5,j=0;buf[i];++i,++j)
			if(buf[i] == '<')
				break;
			else
				temp[j]=buf[i];

		free(buf);
		buf=NULL;

		buf=malloc(strlen(temp)+3);
		bzero(buf,strlen(temp)+3);
		strncpy(buf,temp,strlen(temp));
		strncat(buf,"\r\n",strlen("\r\n"));

		return buf;
	}
}

char *torrent(int sockfd,char *msg)
{
	char *get="GET /search/";
	char *host="Host: www.torrentkitty.com\r\n";
	char *content_type="Content-Type: */*\r\n";
	char *connection="Connection: close\r\n\r\n";
	char *buf;
	char temp[1024]={0};
	int len;
	int i,j;

	for(i=0;msg[i];++i)
		if(msg[i] == '!' && msg[i+1] == 't' && msg[i+2] == 'o' && msg[i+3] == 'r' && msg[i+4] == 'r' && msg[i+5] == 'e' && msg[i+6] =='n' && msg[i+7] == 't')
			break;

	if(msg[i+8] == '\0' || msg[i+8] =='\r' || msg[i+8] != ' ')
		return "torrent <target>\r\n";

	len=strlen(get)+strlen(" HTTP/1.1\r\n");
	for(i+=9,j=0;msg[i];++i,++j)
		if(msg[i] == ' ' || msg[i] == '\r')
			break;
		else
			temp[j]=msg[i];
	printf("temp=%s\n",temp);
	len+=strlen(temp);
	buf=malloc(len+1);
	bzero(buf,len+1);
	strncpy(buf,get,strlen(get));
	strncat(buf,temp,strlen(temp));
	strncat(buf," HTTP/1.1\r\n",strlen(" HTTP/1.1\r\n"));
	
	send(sockfd,buf,strlen(buf),0);
	send(sockfd,host,strlen(host),0);
	send(sockfd,content_type,strlen(content_type),0);
	send(sockfd,connection,strlen(connection),0);
	printf("%s%s%s%s",buf,host,content_type,connection);

	free(buf);
	buf=NULL;

	while(buf=read_line(sockfd))
	{
		if(strstr(buf,"<tr><td class=\"name\">"))
			break;

		free(buf);
		buf=NULL;
	}

	if(buf == NULL)
		return "Sorry,no result found!\r\n";

	for(i=0;buf[i];++i)
		if(buf[i] == 'h' && buf[i+1] == 'r' && buf[i+2] == 'e' && buf[i+3] == 'f')
			break;
	bzero(temp,sizeof(temp));
	for(i+=6,j=0;buf[i];++i,++j)
		if(buf[i] == '"')
			break;
		else
			temp[j]=buf[i];
	printf("%s\n",temp);

	free(buf);
	buf=NULL;

	printf("temp=%d\n",strlen(temp));
	buf=malloc(strlen(temp)+1);
	bzero(buf,strlen(temp)+1);
	strncpy(buf,temp,strlen(temp));
	printf("re=%s\n",buf);
	
	return buf;
}

char *get_magnet(int sockfd,char *url)
{
	char *host="Host: www.torrentkitty.com\r\n";
	char *connection="Connection: close\r\n";
	char *content_type="Content-Type: */*\r\n\r\n";
	char *buf;
	char *temp;
	int len;
	int i,j;

	len=(strlen("GET ")+strlen(url)+strlen(" HTTP/1.1\r\n"));
	buf=malloc(len+1);
	bzero(buf,len+1);

	strncpy(buf,"GET ",strlen("GET "));
	strncat(buf,temp,strlen(temp));
	strncat(buf," HTTP/1.1\r\n",strlen(" HTTP/1.1\r\n"));

	send(sockfd,buf,strlen(buf),0);
	send(sockfd,host,strlen(host),0);
	send(sockfd,connection,strlen(connection),0);
	send(sockfd,content_type,strlen(content_type),0);

	free(buf);
	buf=NULL;

	while(buf=read_line(sockfd))
	{
		if(strstr(buf,"<textarea readonly class=\"magnet-link\" onfocus=\"this.select()\">"))
			break;

		free(buf);
		buf=NULL;
	}

	if(buf == NULL)
		return "Sorry,no result found!\r\n";

	for(i=0;buf[i];++i)
		if(buf[i] == ')' && buf[i+1] == '"' && buf[i+2] == '>')
			break;
	j=i+3;
	for(i+=3,len=0;buf[i];++i,++len)
		if(buf[i] == '<')
			break;

	temp=malloc(len+3);
	bzero(temp,len+3);
	for(i=0;len;++j,--len)
		temp[i]=buf[j];
	strncat(temp,"\r\n",strlen("\r\n"));
	
	free(buf);
	buf=NULL;

	return temp;
}

int main(int argc,char **argv)
{
	SA_IN server_addr;
	int sockfd;
	int man;
	char *buf;
	int ret;
	fd_set reads;

	sockfd=Socket(AF_INET,SOCK_STREAM,0);
	init_data_with_client(&server_addr,SER,PORT);
	Connect(sockfd,&server_addr);

	send(sockfd,NICK,strlen(NICK),0);
	send(sockfd,USER,strlen(USER),0);
	send(sockfd,JOIN,strlen(JOIN),0);

	while(1)
	{
		FD_ZERO(&reads);
		FD_SET(sockfd,&reads);
		ret=select(sockfd+1,&reads,NULL,NULL,NULL);
		if(ret == -1)
			continue;

		buf=read_line(sockfd);
		//printf("%s",buf);

		if(strstr(buf,"!man") && strstr(buf,"PRIVMSG"))
		{
			printf("%s\n",buf);
			man=conect_man("www.linuxmanpages.com",80);
			msgto(sockfd,CHANNEL,get_nick(buf),get_man_url(man,buf));

			close(man);
		}

		if(strstr(buf,"!ip") && strstr(buf,"PRIVMSG"))
		{
			printf("%s\n",buf);

			msgto(sockfd,CHANNEL,get_nick(buf),query_ip(buf));
		}

		if(strstr(buf,"!time") && strstr(buf,"PRIVMSG"))
		{
			printf("%s\n",buf);

			msgto(sockfd,CHANNEL,get_nick(buf),get_time());
		}

		if(strstr(buf,"!dict") && strstr(buf,"PRIVMSG"))
		{
			printf("%s\n",buf);

			man=conect_man("dict.baidu.com",80);
			msgto(sockfd,CHANNEL,get_nick(buf),dict(man,buf));

			close(man);
		}

		if(strstr(buf,"!torrent") && strstr(buf,"PRIVMSG"))
		{
			char *temp;

			printf("%s\n",buf);

			/*msgto(sockfd,CHANNEL,get_nick(buf),"该搜索可能会比较慢，请耐心等待，在此期间也希望不要再呼叫我!\r\n");
			man=conect_man("www.torrentkitty.com",80);
			temp=torrent(man,buf);
			close(man);
			if(strstr(temp,"Sorry") || strstr(temp,"torrent"))
			{
				msgto(sockfd,CHANNEL,get_nick(buf),temp);
				continue;
			}
			man=conect_man("www.torrentkitty.com",80);
			msgto(sockfd,CHANNEL,get_nick(buf),get_magnet(man,temp));

			free(temp);
			temp=NULL;
			close(man);*/
			msgto(sockfd,CHANNEL,get_nick(buf),"由于无法连接到torrentkitty，所以暂时关闭该功能!\r\n");
		}

		if(strstr(buf,"!list") && strstr(buf,"PRIVMSG"))
		{
			printf("%s\n",buf);
			msgto(sockfd,CHANNEL,get_nick(buf),
					"man、ip、time、dict、torrent、list\r\n");
		}

		if(strstr(buf,"PING"))
			send(sockfd,buf,sizeof(buf),0);

		free(buf);
		buf=NULL;
	}

	close(sockfd);

	return 0;
}
