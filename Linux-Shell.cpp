/*
Troy Seide
Linux Shell
CIS 3207
10/14/2019 
*/

/* 
 * File:   Linux-Shell.cpp
 * Author: Owner
 *
 * Created on September 27, 2019, 2:04 AM
 */
#include<string.h> 
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
void TokenizedWords(char *line, char **TokenArray);
void ExternalCommands(char **TokenArray);
int Environ();
void clr();
void echo(char **arr);
void help();
void quit();
void cd(char **arr);
int wordcount=0;
int main(){
    
	char *path2;
	char *arr[100];
	char *Tokenized;
	char words[100];
	char *TokenArray[100];
        
	while(true){
            //cout<< "myShell-> ";
            cin.getline(words,100);
            
            TokenizedWords(words, TokenArray);
            
            if(strcmp(TokenArray[0], "quit") == 0){
                quit();
                    //break;
            }
            else if(strcmp(words, "\n") == 0){
                    continue;
            }
            else if(strcmp(TokenArray[0], "clr")==0){
                clr();
            }
            else if(strcmp(TokenArray[0], "echo")==0){
                echo(TokenArray);
            }
            else if(strcmp(TokenArray[0], "help")==0){
                help();
            }
            ExternalCommands(TokenArray);
    }
	return 0;
}

void ExternalCommands(char **TokenArray){
    pid_t pid;
    int pos;
    int child;
    pid = fork();
    if(pid == 0){    
    int input=0,outputcount=0;
    char words[100],output[100];
    //tried to check for redirection
    /*
    for(int i=0; i<wordcount;i++){
        if(strcmp(TokenArray[i],"<")==0){        
            TokenArray[i]=NULL;
            strcpy(words,TokenArray[i+1]);          
        }               
        if(strcmp(TokenArray[i],">")==0){      
            TokenArray[i]=NULL;
            strcpy(output,TokenArray[i+1]);
        }         
    }
    */
    child = execvp(*TokenArray, TokenArray);
    if (child < 0){
        cout<<"An error has occurred"<<endl;  
    }
    exit(1);
    }
    else if(pid < 0){
        cout<< "An error has occurred"<<endl;
    }
    else {   
        int pos;
        waitpid(pid, &pos, 0);
    }
}

void TokenizedWords(char *words, char **TokenArray){
    char *Token;
    Token = strtok(words, " ");
    while(Token != NULL){
        wordcount++;
        *TokenArray++  = Token;
        Token = strtok(NULL, " ");
    }
    *TokenArray = NULL;      
}

int Environ(){
    char *environ;
    char *Tokenarr[100];
    char *strings;
    environ= getenv("PATH");
    strings= strtok(environ, ":");
    int i= 0;
    while(strings != NULL){
            Tokenarr[i] = strings;
            strings = strtok(NULL, ":");
            i++;
    }

    Tokenarr[i] = NULL;
}

void clr(){
    //cout<<"The screen has been cleared";
    cout<<"\033[H\033[2J";
}
void echo(char **arr){
    for(int i=1; i<wordcount; i++){
        cout<<arr[i];
        cout<<" ";
    } 
    cout<<"\n";
}
void help(){
    cout<<"\ncd: Change the directory.\n";
    cout<<"clr: Clear the screen.\n";
    cout<<"dir: Print the contents of the current directory or a user-specified directory.\n";
    cout<<"environ: List the environment variables.\n";
    cout<<"echo: Print the user’s input.\n";
    cout<<"help: Display the user manual.\n";
    cout<<"pause: Pause the shell until the user presses Enter.\n";
    cout<<"quit: Exit the program.\n";
}
/*
void pause(){
    
}
*/

void quit(){
    cout<<"\nThe program has exited";
    exit(0);
}

