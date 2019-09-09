#ifndef alias
#define alias
#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string.h>
#include<unordered_map>

class Alias
{
	string a="alias";
	vector<char*> v;

public:
	bool if_alias(char** command)
	{
		if(command[0]==a)
		{
			return true;
		}
	}

	vector<char*> ali_split(char s[])
	{
		vector<char*> v1;
		char* temp=strtok(s, "=");
		while(temp!=NULL)
		{
			v1.push_back(temp);
			temp=strtok(NULL,"=");
		}
		
		return v1;
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


	bool check_alias(string s, unordered_map<string, string> &alia)
	{	

		s=s.substr(6);

			string str="";
			for(int i=0;i<s.length();i++)
			{
				if(s[i]!=39)
				{
					str+=s[i];
				}
			}

			int x;
			char cc[str.length()+1];
			for(x=0;x<str.length();x++)
			{
				cc[x]=str[x];
			}
			cc[x]='\0';

		v=ali_split(cc);
	    string key(v[0]);
		string val(v[1]);
		alia.insert(make_pair(key, val));
       
return true;
	}
	bool if_present(char** command, unordered_map<string, string> &alia)
	{   

		string to_find(command[0]);
		unordered_map<string, string>:: iterator it;
		it=alia.find(to_find);
        if(it==alia.end())
		{	
			return false;
		}
 
        return true;		
	}

	char* get_command(char** command, unordered_map<string, string> alia)
	{
		unordered_map<string, string>:: iterator itr;
		
		string s(command[0]);
		itr = alia.find(s);
		
		string com=itr->second;

		char c[204];
		int len=com.length();
		int i;
		for(i=0;i<len;i++)
		{
			c[i]=com[i];
		}
		c[i]='\0';
		
		char** news=splits(c);
		
		if(execvp(news[0], news))
			cout<<"Unable to run alias."<<endl;
	
	}
};

#endif