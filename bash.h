#ifndef bash_H
#define bash_H


#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>


using namespace std;

class MyBash
{
    public:
      MyBash()
{
    fstream fs;
    string path;
    fs.open("/etc/environment",ios::in);
    getline(fs,path);
    //cout<<path<<endl;
    fs.close();

    fstream fs1;
    string host;
    fs1.open("/etc/hostname",ios::in);
    getline(fs1,host);
    //cout<<host<<endl;
    fs1.close();

    fstream fs2;
    string line;
    string user;
    string home;
    fs2.open("/etc/passwd",ios::in);
    int i=0;
    while(i<41)
    {
      getline(fs2,line);
      i++;
    }
    //cout<<line<<endl;

    int len=line.size();
    char s[200];
    for(int i=0;i<len;i++)
    {
      s[i]=line[i];
    }
    s[i]='\0';

    vector<char*> v;

    v=split(s);

    /*for(int i=0;i<v.size();i++)
    {
      cout<<v[i]<<endl;
    }*/
    fs2.close();

    fstream st;
    st.open("my_bash.txt",ios::out);
      if(!st)
      {
        cout<<"Cannot initialize variables.";
      }
      else
      {
        st<<"$"<<endl; //PS1
        st<<path<<endl; //PATH
        st<<host<<endl; //HOSTNAME
        st<<v[0]<<endl; //USER
        st<<v[5]<<endl; //HOME

      }

    st.close();
}

vector<char*> split(char s[])
  {
    vector<char*> v;

   char* temp=strtok(s, ":");
    while(temp!=NULL)
    { 
      //cout<<temp<<endl;
      v.push_back(temp);
      temp=strtok(NULL,":");
    }
    return v; 
  }

};

#endif


