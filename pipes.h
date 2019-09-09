#ifndef pipes
#define pipes
#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h> 
#include <signal.h>
#include<fcntl.h>

class Pipes
{
		int countp=0;
public:
	bool is_pipe(string s)
	{
		for(int i=0;i<s.length();i++)
		{
			if(s[i]==124)
			{	
				return true;
			}

		}
		return false;

	}

	void pipe_close(int x)
	{
		close(x);
	}

	char** split_pipes(char s[])
	{	
		vector<char*> v;

		char* temp=strtok(s, "|");

		while(temp!=NULL)
		{
			v.push_back(temp);
			temp=strtok(NULL,"|");
		}
	char** command=new char*[v.size()+1];
	for(int i=0;i<v.size();i++)
	{
		command[i]=v[i];
	}

	command[v.size()]=NULL;


	return command;
	}

	char** split(char s[])
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


	int exec_pipes(string s)
	{	
			
		int i=0;
		int exit_state;

		for(int i=0;i<s.length();i++)
		{	
			if(s[i]==124)
				countp++;
		}
		char c[204];
		int len=s.length();

		for(i=0;i<len;i++)
		{
			c[i]=s[i];
		}
		c[i]='\0';
		

		char** command=split_pipes(c);

		int filedes=0, x=0; 
		int rw[2];
		while(x<(countp+1))
		{
			pipe(rw);
			pid_t p=fork();
			if(p<0)
			{
				cout<<"Something is Wrong!";
			}
			else if(p==0)
			{

				dup2(filedes,0);
				if(x+1<(countp+1))
					dup2(rw[1],1);
				pipe_close(rw[0]);
				pipe_close(rw[1]);

				char** newcom=split(command[x]);
				if(execvp(newcom[0],newcom)<0)
				{
					cout<<"Cannot execute pipes."<<endl;
				}
			}
			else
			{	
				wait(&exit_state);
				filedes=rw[0];
				pipe_close(rw[1]);
				
			}
			x++;
		}

	return exit_state;

	}
};
#endif