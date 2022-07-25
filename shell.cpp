//
//  main.cpp
//  Anant_shell
//
//  Created by Anant Mehta on 28/11/21.
//
#include <iostream>
#include <string>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
# define delim " \t\r\n\a"
using namespace std;
vector<string> history;
string read_line(void){
    string buffer;
    getline(cin ,buffer);
    if(buffer!="history")
    history.push_back(buffer);
    return buffer;
}
vector<string> spilt_line(string &line){
    vector<string> tokens;
    string token;
    for(int i=0;i<line.size();i++){
        if(line[i]==' ' || line[i]=='\n' || line[i]=='\r' || line[i]=='\a' || line[i]=='\t'){
            tokens.push_back(token);
            token.clear();
        }
        else
            token.push_back(line[i]);
    }
    tokens.push_back(token);
    token.clear();
    return tokens;
}
int launch(vector<string> args){
    pid_t pid,w_pid;
    int status;
    pid=fork();
    char **g=new char*[args.size()];
    for(int i=0;i<args.size();i++){
        g[i]=new char[args.size()];
        for(int j=0;j<args[i].size();j++)
            g[i][j]=args[i][j];
    }
    if(pid==0){
        if(execvp(g[0],g)==-1){
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid<0)
        perror("lsh");
    else{
        w_pid=waitpid(pid,&status,WUNTRACED);
    }
    return 1;
}
int lsh_cd(vector<string> &args){
    char **g=new char*[args.size()];
    for(int i=0;i<args.size();i++){
        g[i]=new char[args.size()];
        for(int j=0;j<args[i].size();j++)
            g[i][j]=args[i][j];
    }
    if(args.size()==1){
        cout<<"Error encountered"<<endl;
    }
    else{
        if(chdir(g[1])!=0)
            perror("lsh");
    }
    return 1;
}
int lsh_help(vector<string> &args){
    int i;
    cout << "cd" << endl << "help" << endl << "exit" << endl << "history"<< endl;
    cout << "Use MAN command for information on the other programs " << endl;
    return 1;
}
int lsh_history(vector<string> &args)
{
    int i;
    for(i=0;i<history.size();i++)
    {
        cout<<history[i]<<endl;
    }
    return 1;
}
int lsh_exit(vector<string> &args){
    return 0;
}
int execute(vector<string> &args){
    int i;
    if(args.size()==0)
        return 1;
    if(args[0]=="cd")
        return lsh_cd(args);
    if(args[0]=="help")
        return lsh_help(args);
    else if(args[0]=="exit")
        return lsh_exit(args);
    else if(args[0]=="history")
    {
        cout<<"history is : "<<endl;
        return lsh_history(args);
    }
    return launch(args);
}

void lsh_loop(){
    string line;
    vector<string> args;
    int status;
    do{
        cout << "ANANT'S_shell->";
        line=read_line();
        args=spilt_line(line);
        status=execute(args);
        line.clear();
        args.clear();
    }while(status);
}
int main(int argc,char** agrv){
   // system("color 0A");
    cout << "Initiating shell:" << endl;
    sleep(1);
    cout<< "Including configuration files"<<endl;
    sleep(2);
    cout << "Please wait , your shell is starting soon ";
    cout << ".";
    sleep(1);
    cout << ".";
    sleep(1);
    cout << ".";
    sleep(1);
    cout << ".";
    sleep(3);
    cout << "Shell started !! please use this shell at your own risk !!\nI am keeping track of command history :) " << endl;
    lsh_loop();
    cout << "Thank me for using the shell :) , Exiting ..." << endl;
    sleep(3);
    return EXIT_SUCCESS;
}