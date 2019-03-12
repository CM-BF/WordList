#include"wordlist.h"
#include<unistd.h>
using namespace std;

/// DEBUG MODEL
#define DEBUG 1
#if DEBUG == 1
#define COUT(x) std::cout<<x<<std::endl
void outputMatrix(){
    for(char i='a'; i<='z'; i++){
        if(i == 'a'){
            printf(" ");
            for(char j='a'; j<='z'; j++){
                printf("\033[;31m%3c\033[0m", j);
            }
            printf("\n");
        }
        printf("\033[;31m%c\033[0m", i);
        for(char j='a'; j<='z'; j++){
            auto count = wordList::wordMatrix.count(i, j);
            if(count != 0){
                printf("\033[;31m%3d\033[0m", count);
            }else
                printf("%3d", count);
        }
        printf("\n");
    }
}
#else
#define COUT(x) 
void outputMatrix(){}
#endif

bool inRange(char c){
    if((c>='a' && c<='z') || (c>='A' && c<='Z'))
        return true;
    else
        return false;
    
}

std::vector<std::string> wordList::filter(std::string S){
    std::vector<std::string> vec;
    S = S + "$";
    int begin=0;
    for(int i=0; i<S.length(); i++){
        if(inRange(S.at(i))){
            char c = S.at(i);
            if(c>='A' && c<='Z'){
                S.at(i) = char(S.at(i)) - 'A' + 'a';
            }
        }else{
            if(begin != i){
                vec.push_back(S.substr(begin, i - begin));
            }
            begin = i + 1;
        }
    }
    return vec;
}

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

void loadingWords(){
    std::unordered_map<std::string, int> Smap;
    std::ifstream inFile(wordList::inFileName);
    while(!inFile.eof())
    {
        std::string S;
        inFile>>S;
        auto Svector = wordList::filter(S);
        for(auto it = Svector.begin(); it != Svector.end(); it++){
            auto s = *it;
            if(Smap.count(s) == 0){
                Smap[s] = 1;
                COUT(s);
                wordList::wordMatrix.incCount(s);
                wordList::wordMatrix.pushWord(s);
            }          
        }
    }
    outputMatrix();
}

void cmdParametersParser(int argc, char **argv){
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
}

int main(int argc,char **argv){
    
    cmdParametersParser(argc, argv);
    loadingWords();

    return 0;
}