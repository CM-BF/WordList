#include"wordlist.h"
#include<unistd.h>



int main(int argc,char **argv){
    int ch;
    int opennum = 0;
    bool maxWordLen = false, maxCharLen = false, fixedLen = false;
    bool wordnum = true;
    string filename;
    int listlens;
    char head='\0',tail='\0';
    while((ch=getopt(argc,arv,"w:c:h:t:n:"))!=-1)
    {
        switch(ch)
        {
            case 'w':filename = optarg;
                    opennum++;
                    wordnum = true;
                    maxWordLen = true;break;
            case 'c':filename = optarg;
                    opennum++;
                    wordnum = false;
                    maxCharLen = true;break;
            case 'h':head = (char)optarg;break;
            case 't':tail = (char)optarg;break;
            case 'n':fixedLen = true;
                    break;
            default:;
        }

    }

    if(opennum != 1)
    {
        printf("");
        exit(0);
    }

    if(fixedLen && !maxWordLen)
    { 
        printf("");
        exit(0);
    }

    if(fixed)  ;
    else if(maxWordLen) ;
    else (maxCharLen) ;

    return 0;
}