#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <limits.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

vector<string> PARSE_STRING(string input,char delim)
{
    int pos=0;
    int prev=0;
    vector<char>tokens;
    vector<string>command;
    while(input[pos]!='\0')
    {
        if(input[pos]=='"')
        {
            tokens.push_back(input[pos]);
            pos++;
            while(input[pos]!='"'&& input[pos]!='\0')
            {
                tokens.push_back(input[pos]);
                pos++;
            }
            tokens.push_back(input[pos]);
            pos++;
        }
        else if(input[pos]=='\'')
        {
            tokens.push_back(input[pos]);
            pos++;
            while(input[pos]!='\''&& input[pos]!='\0')
            {
                tokens.push_back(input[pos]);
                pos++;
            }
            tokens.push_back(input[pos]);
            pos++;
        }

        else if(delim=='|' && input[pos]=='|' && input[pos+1]!='\0' && input[pos+1]=='|')
        {
            tokens.push_back(input[pos]);
            pos++;
            tokens.push_back(input[pos]);
            pos++;
        }
        else if(input[pos]!=delim)
        {
            tokens.push_back(input[pos]);
            pos++;
        }
        else
        {
            if(!tokens.empty())
            {
                //    tokens.push_back('\0');
                string s(tokens.begin(),tokens.end());
                if(s.compare(" ")!=0)
                {
                    command.push_back(s);
                    //               cout<<"token = "<<s<<" and length = "<<s.length()<<endl;
                }
                tokens.clear();
            }
            pos++;
        }
    }
    if(!tokens.empty())
    {
        //        tokens.push_back('\0');
        string s(tokens.begin(),tokens.end());
        if(s.compare(" ")!=0)
        {
            command.push_back(s);
            //  cout<<"token = "<<s<<" and length = "<<s.length()<<endl;
        }
        tokens.clear();
    }
    return command;
}
