#ifndef echo_variable
#define echo_variable

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;

class EchoVar
{

public:
	void echo(char** command)
	{
		vector<string> v;
		string temp;
		temp=command[1];
		
		fstream fs;
		fs.open("my_bash.txt",ios::in);
		string line;
		int i=0;
		while(getline(fs,line))
		{	//cout<<line<<endl;
			v.push_back(line);
			//cout<<v[i]<<endl;
			//i++;

		}
		string  ps1="$PS1";
		string path="$PATH";
		string host="$HOSTNAME";
		string user="$USER";
		if(command[1]==ps1)
		{
			cout<<v[0]<<endl;
		}
		
		else if(command[1]==path)
		{
			cout<<v[1]<<endl;
		}
		else if(command[1]==host)
		{
			cout<<v[2]<<endl;
		}
		
		else if(command[1]==user)
		{
			cout<<v[3]<<endl;
		}
		else
		{
			cout<<v[4]<<endl;
		}
	}

};


#endif