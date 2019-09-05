#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h> 
#include <signal.h>

using namespace std;

#define clear() printf("\033[H\033[J")

void currentDir()
{	//cout<<"this is my directory";
	char *path=NULL;
	cout<<getenv("USER")<<"::";
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

	pid_t pid=fork();
	if(pid<0)
	{
		cout<<"Command cannot be processed.";
	}
	else if(pid==0)
	{	if(command[0]==cd)
		{
			int flag;
			if (chdir(command[1])<0)
			{
				cout<<"wrong path"<<endl;
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
			if(execvp(command[0], command) < 0); 
    		cout<<"Could not execute command."; 
			
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
	//signal(SIGINT, sigintHandler);
    vector<string> history;
	while(1)
	{
		currentDir();
		string s;
		
		getline(cin,s);
		//cout<<s<<endl;
		history.push_back(s);
		//cout<<history[0];

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
		//cout<<command[0]<<endl;
		//cout<<command[1]<<endl;
		//cout<<command[2]<<endl;
		//string changedir="cd";	
		string e="exit";	
		if(command[0]==e)
		{	//cout<<"dvewfgef"<<endl;
			return -1;
		}



		execute(command, history);
	}
	return 0;
}