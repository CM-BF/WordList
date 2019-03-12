#include"wordlist.h"
#include<unistd.h>
using namespace std;

int StringtoNum(char *optarg)
{
    int num = 0;
    for(int i = 0;optarg[i]!='\0';i++){
        if(optarg[i]>='0'&&optarg[i]<='9')
        {
            num *= 10;
            num += optarg[i]-'0';
        }
        else {
            printf("\n");
            exit(0);
        }
    }
    return num;
}

int main(int argc,char **argv){
    int ch;
    int opennum = 0;
    bool maxWordLen = false, maxCharLen = false, fixedLen = false;
    bool wordnum = true;
    string  filename;
    int listlens;
    char head='\0',tail='\0';
    while((ch=getopt(argc,argv,"w:c:h:t:n:"))!=-1)
    {
        switch(ch)
        {
            case 'w':filename = optarg;
                    opennum++;
                    wordnum = true;
                    cout << filename <<endl;
                    maxWordLen = true;break;
            case 'c':filename = optarg;
                    opennum++;
                    wordnum = false;
                    cout << filename <<endl;
                    maxCharLen = true;break;
            case 'h':head = *optarg;
                    cout << head <<endl;break;
            case 't':tail = *optarg;
                    cout << tail <<endl;break;
            case 'n':fixedLen = true;
                    listlens = StringtoNum(optarg);
                    cout << listlens <<endl;
                    break;
            default:;
        }

    }

    if(opennum != 1)
    {
        printf("\n");
        exit(0);
    }

    if(fixedLen && !maxWordLen)
    { 
        printf("\n");
        exit(0);
    }

    if(fixedLen)  ;
    else if(maxWordLen) ;
    else (maxCharLen) ;

    return 0;
}