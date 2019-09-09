#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h> 
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h> 
#include <signal.h>
#include <stack>
#include "bash.h"
#include "echo_variable.h"
#include "pipes.h"
#include <fcntl.h>
#include "alias.h"

using namespace std;

#define clear() printf("\033[H\033[J")
Alias a;
unordered_map<string, string> alia;
pid_t process_id;
bool append;
bool output_redirect;
char* ap;
char* op;

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
				ap=command[i+1];

				return true;	
			}

			else if(command[i]==out)
			{
				output_redirect=true;
				command[i]=NULL;
				op=command[i+1];
				
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

		if(execvp(command[0],command)<0)
			cout<<"Cannot execute command";
	}
	else if(output_redirect==true)
	{
		int f=open(op, O_WRONLY | O_CREAT, 0644);
		dup2(f,1);
		output_redirect=false;
		
		if(execvp(command[0],command)<0)
			cout<<"Cannot execute command";
		close(f);
					
	}


}
void currentDir()
{	
	char *path=NULL;
	cout<<getenv("USER")<<"::";

    size_t size=1024;
    cout<<getcwd(path,size)<<"$";
    cout<<endl;
  
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
		//cout<<command[i]<<endl;
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
			string tild="~";
			if(command[1]==tild)
			{
				if(chdir("/home/madhvi")<0)
					cout<<"Wrong path"<<endl;	
			}

			else
			{
				if(chdir(command[1])<0)
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
			{	
				exec_re(command);
			}

			else
			{		
				EchoVar ev;
				ev.echo(command);
			}
		}
		
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
			if(a.if_present(command, alia))
			{
				a.get_command(command, alia);
			}
			else
			{
				if(execvp(command[0], command)<0)
    			cout<<"Could not execute command."<<endl;
    		} 
		}
	}

	else
	{
		wait(NULL);
	}
}

int main()
{	
	clear();
	MyBash mb;
	process_id=getpid();
    vector<string> history;
	while(1)
	{
		currentDir();
		string s;
		string rec="record start";


		getline(cin,s);
		history.push_back(s);

		if(s.compare(rec)==0)
		{

			//cout<<"you are being recorded";

		}
		char c[204];
		int len=s.length();
		int i;
		for(i=0;i<len;i++)
		{
			c[i]=s[i];
		}
		c[i]='\0';
		
		if(c[0]=='\0')
		{
			continue;
		}

		string e="exit";	
		if(s.compare(e)==0)
		{
			return -1;
		}

		Pipes p;
		if(p.is_pipe(s))
		{	
			p.exec_pipes(s);
			continue;
		}
		
		char** command=splits(c);
		
		if(a.if_alias(command))
		{
			if(a.check_alias(s, alia))
			cout<<"Alias created successfully."<<endl;
			continue;
		}


		execute(command,history);
	}


	return 0;
}

