#include"wordlist.h"

/// DEBUG MODEL
#define DEBUG 0

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
            cout << "The value of -n should be an integer"<<endl;
            exit(0);
        }
    }
    return num;
}

void HandleException()
{
    try{
        if(wordList::wc1_paranum == 0 && !wordList::specWordLens){
            throw "-w or -c or -n must be chooesd ";
            exit(0);
        }

        if(wordList::wc1_paranum > 1||wordList::h_paranum > 1||wordList::t_paranum > 1
            ||wordList::n_paranum > 1||wordList::f_paranum > 1){
            throw "The same parameter can occur only once";
            exit(0);
        }

        if(wordList::inputfromscreen){
            throw "No file opened";
            exit(0);
        }
        if(wordList::wc1_paranum == 1 && wordList::WordLens && wordList::specWordLens){
            throw "-w and -n cannot be choosed together";
            exit(0);
        }
        // if(wordList::specWordLens && wordList::specLength <2){
        //     std::cout << "Word length should >1" <<std::endl;
        //     exit(0);
        // }
        if(wordList::spechead && (wordList::temp_head.size()!=1 || !isalpha(wordList::temp_head[0]))){
            throw "The value of -h should be a character";
            exit(0);
        }
        else if(wordList::spechead) wordList::head = char(wordList::temp_head[0]);
        if(wordList::spectail && (wordList::temp_tail.size()!=1 || !isalpha(wordList::temp_tail[0]))){
            throw "The value of -t should be a character";
            exit(0);
        }
        else if(wordList::spectail) wordList::tail = char(wordList::temp_tail[0]);
    }catch(char const *s){
        cerr << s << endl;
    }
    
}

void cmdParametersParser(int argc, char **argv){
    int ch;

    while((ch=getopt(argc,argv,"wch:t:n:f:"))!=-1)
    {
        switch(ch)
        {
            case 'w':
                    wordList::WordLens = true;
                    wordList::wc1_paranum ++;
                    break;
            case 'c':
                    wordList::WordLens = false;
                    wordList::wc1_paranum ++;
                    break;
            case 'h':wordList::temp_head = optarg;
                    wordList::spechead = true;
                    wordList::h_paranum ++;
                    COUT(wordList::head);break;
            case 't':wordList::temp_tail = optarg;
                    wordList::spectail = true;
                    wordList::t_paranum ++;
                    COUT(wordList::tail);break;
            case 'n':wordList::specWordLens = true;
                    wordList::specLength = StringtoNum(optarg);
                    wordList::n_paranum ++;
                    COUT(wordList::specLength);
                    break;
            case 'f':wordList::FileName = optarg;
                    wordList::inputfromscreen = false;
                    wordList::f_paranum ++;
                    COUT(wordList::FileName);
                    break;
            default:;
        }
    }
}

int main(int argc, char *argv[])
{
    cmdParametersParser(argc, argv);
    return 0;
}