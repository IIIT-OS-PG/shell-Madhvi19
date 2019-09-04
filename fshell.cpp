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

void execute(char** command)
{	string cd="cd";
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

	while(1)
	{
		currentDir();
		
		char c[204];
		cin.getline(c,204);

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


		execute(command);
	}
	return 0;
}