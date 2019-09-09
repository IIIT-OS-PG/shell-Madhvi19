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
	//unordered_map<char*, char*> alia;
	string a="alias";
	vector<char*> v;
	//unordered_map<char*, char*>:: iterator itr;

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
		//cout<<v1[0];
		//cout<<v1[1];
		
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
		//cout<<command[i]<<endl;
	}

	command[v.size()]=NULL;


	return command;
}


	bool check_alias(string s, unordered_map<string, string> &alia)
	{	

		s=s.substr(6);
			// cout<<s;
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
			//	cout<<cc[x];
			}
			cc[x]='\0';

			
			//cout<<endl;

			// for(int j=0;j<str.length();j++)
			// {
				// cout<<cc[j]<<endl;
			// }
			// cout<<7898<<endl;
		v=ali_split(cc);
		//cout<<"inside check "<<endl;
		//cout<<v[0]<<endl;
        //cout<<v[1]<<"v1"<<endl;
     //   char **to_be_executed=splits(v[1]);

       // cout<<to_be_executed[0]<<endl;
        //cout<<to_be_executed[1]<<endl;
        string key(v[0]);
		string val(v[1]);
		alia.insert(make_pair(key, val));
		
		// cout<<key<<endl;
		// cout<<val<<endl;
		
			
		/*int l=v.size();
		cout<<l<<endl;
		char** command=new char*[v.size()];
		command[0]=v[1];
		command[v.size()]=NULL;
		cout<<command[0]<<endl;*/

		
	/*	unordered_map<string, string>:: iterator it;
		for (it = alia.begin(); it != alia.end(); it++) 
   		{
   			cout << it->first <<"7878"<< it->second << endl; 
     	}*/ 
     	//char *check="ll";
        //if(strcmp(v[0],check)==0) cout<<"dono same toh hai\n";
       
return true;
	}
	bool if_present(char** command, unordered_map<string, string> &alia)
	{   

		//unordered_map<string, string>:: iterator it;
		/*for (it = alia.begin();it != alia.end(); it++) 
   		{	
   			//cout<<"inside for loop"<<endl;
   			cout << it->first <<"7878"<< it->second << endl;
     	} */
		string to_find(command[0]);
		//cout<<to_find<<endl;
		unordered_map<string, string>:: iterator it;
		it=alia.find(to_find);
        if(it==alia.end())
		{	
			// cout<<"not present"<<endl;
			return false;
		}
        	
        	//cout<<"Present hai yaar\n";
        	//cout<<it->second<<"pehla wala\n";
     
        return true;


		/*cout<<"if_Present"<<endl;
		cout<<command[0]<<"7878"<<endl;
		if(alia.find(command[0])==alia.end())
		{	
			cout<<"not present"<<endl;
			return false;
		}
		unordered_map<char*, char*>:: iterator itr;
		for(itr=alia.begin();itr!=alia.end();itr++)
		{	cout<<"inside for loop"<<endl;

			cout<<itr->first<<endl;
			return true;
		}
		/*itr = alia.find(command[0]);
		if(itr != alia.end())
		{
			return true;
		}*/
		/*while(itr->first!=command[0] && itr<alia.end())
		{

			itr++;
		}

		if(itr->first == command[0])
		{
			return true;
		}*/
		/*
		{
			unordered_map<char*,char*>:: iterator it;
			it=alia.find(command[0]);
			cout<<it->first<<endl;
			cout<<it->second<<endl;
			return true;
		}*/

		//return false;
	}

	char* get_command(char** command, unordered_map<string, string> alia)
	{
		unordered_map<string, string>:: iterator itr;
		/*while(itr->first!=command[0] && itr<alia.end())
		{

			itr++;
		}*/
		// cout<<" inside get command hun mai"<<endl;
		string s(command[0]);
		itr = alia.find(s);
		
		string com=itr->second;
		// cout<<com;
		char c[204];
		int len=com.length();
		int i;
		for(i=0;i<len;i++)
		{
			c[i]=com[i];
		}
		c[i]='\0';
		// cout<<"conversion done"<<endl;
		// for(int j=0;j<=len;j++)
		// {
			// cout<<c[j]<<endl;
		// }

		char** news=splits(c);
		// cout<<news[0]<<endl;
	//	cout<<news[1]<<endl;

		if(execvp(news[0], news))
			cout<<"Unable to run alias."<<endl;
	
	}
};

#endif