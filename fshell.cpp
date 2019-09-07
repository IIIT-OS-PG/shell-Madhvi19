#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h> 
#include <signal.h>
#include <stack>
#include "bash.h"
#include "echo_variable.h"
#include<fcntl.h>


using namespace std;

#define clear() printf("\033[H\033[J")
pid_t process_id;
bool append;
bool output_redirect;
char* ap;
char* op;
//stack <pid_t> stk;

bool check(char** command)
	{	
		string app=">>";
		string out=">";
		int i=0;
		
		while(command[i]!=NULL)
		{
			if(command[i]==app)
			{	
				append=true;
				command[i]=NULL;
				//cout<<command[i+1]<<endl;
				ap=command[i+1];
				//cout<<"ap="<<ap<<endl;
				return true;	
			}

			else if(command[i]==out)
			{
				output_redirect=true;
				command[i]=NULL;
				//cout<<command[i+1]<<endl;
				op=command[i+1];
				//cout<<"op="<<op<<endl;
				
				return true;
			}
			i++;
		}

		return false;

	}

void exec_re(char** command)
{	
	if(append==true)
	{
		int f= open(ap, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(f,1);
		append=false;
		//close(f);
		if(execvp(command[0],command)<0)
			cout<<"Cannot execute command";
	}
	else if(output_redirect==true)
	{
		int f=open(op, O_WRONLY | O_CREAT, 0644);
		dup2(f,1);
		output_redirect=false;
		
		if(execvp(command[0],command))
			cout<<"Cannot execute command";
		close(f);
					
	}


}
void currentDir()
{	//cout<<"this is my directory";
	char *path=NULL;
	cout<<getenv("USER")<<"::";
	
	//cout<<process_id<<endl;

    size_t size=1024;
    cout<<getcwd(path,size)<<"$";
    cout<<endl;
   	//cout<<"\n Current Path:"<<path;
}

char** splits(char s[])
{
	vector<char*> v;

	char* temp=strtok(s, " ");
	while(temp!=NULL)
	{
		v.push_back(temp);
		temp=strtok(NULL," ");
	}
	char** command=new char*[v.size()+1];
	for(int i=0;i<v.size();i++)
	{
		command[i]=v[i];
	}

	command[v.size()]=NULL;


	return command;
}

void execute(char** command, vector<string> history)
{

	string cd="cd";
	string h="history";
	string dollar="$$";
	string dq="$?";
	string echo="echo";
	pid_t pid=fork();

	if(pid<0)
	{
		cout<<"Command cannot be processed.";
	}

	else if(pid==0)
	{	

		if(command[0]==cd)
		{
			//int flag;
			if (chdir(command[1])<0)
			{
				cout<<"Wrong path"<<endl;
			}

		}


		else if (command[0]==dollar)
		{
			cout<<process_id;
		}

		else if(command[0]==echo)
		{	
			if(check(command))
			{	//cout<<"ab mera exec chlega"<<endl;
				exec_re(command);
			}

			else
			{			
				EchoVar ev;
				ev.echo(command);
			}
		}

		/*else if(command[0]==dq)
		{
			stk.pop();
			int i=stk.top();
			cout<<i<<endl;
		}*/
		
		else if(command[0]==h)
		{
			int len=history.size();
			for(int i=0;i<len;i++)
			{
				cout<<history[i]<<endl;
			}
		}


		else
		{
			if(execvp(command[0], command)<0); 
    		cout<<"Could not execute command."<<endl; 
			
		}
	}

	else
	{
		wait(NULL);
		//cout<<"Parent here";
	}
}
/*void sigintHandler(int sig_num) 
{ 
    signal(SIGINT, sigintHandler); 
    fflush(stdout); 
} */

int main()
{	
	clear();
	MyBash mb;
	process_id=getpid();
	//signal(SIGINT, sigintHandler);
    vector<string> history;
	while(1)
	{
		currentDir();
		string s;
		string rec="record start";
		
		getline(cin,s);
		//cout<<s<<endl;
		history.push_back(s);
		//cout<<history[0];

		if(s.compare(rec)==0)
		{

			//cout<<"you are being recorded";

		}
		char c[204];
		//cin.getline(c,204);
		int len=s.length();
		int i;
		for(i=0;i<len;i++)
		{
			c[i]=s[i];
		}
		c[i]='\0';
		

		//cout<<s<<endl;
		if(c[0]=='\0')
		{
			continue;
		}

		char** command=splits(c);
	

		string e="exit";	
		if(command[0]==e)
		{	//cout<<"dvewfgef"<<endl;
			return -1;
		}
			
			

			execute(command, history);
	
	}


	return 0;
}