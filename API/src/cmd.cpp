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
            auto count = wordMatrix.count(i, j);
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

bool specWordLens = false;
bool WordLens = true;   //find the wordlist with most word or most letters
int wc1_paranum = 0,h_paranum = 0,t_paranum = 0,n_paranum = 0,f_paranum = 0;
char head = 0,tail = 0;
char *filename;
int n;
int maxletter;

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

void Output(vector<string> &vec,string outfile)
{
    ofstream out(outfile);
    if(WordLens) out << vec.size()<<endl;
    else out << maxletter <<endl;
    for(auto it = vec.begin();it != vec.end();it++){
        out << *it << endl;
    }
    out.close();
}

void Outputspec(vector<vector<string>> &vec,string outfile)
{
    ofstream out(outfile);
    out << vec.size()<<endl;
    for(auto it1 = vec.begin();it1 != vec.end();it1++){
        for(auto it2 = it1->begin(); it2 != it1->end();it2++)
            out << *it2 << endl;
        out << endl;
    }
    out.close();

}

void HandleException()
{
    try{
        if(wc1_paranum == 0 && !specWordLens){
            throw "-w or -c or -n must be chooesd ";
        }

        if(wc1_paranum > 1||h_paranum > 1||t_paranum > 1
            ||n_paranum > 1||f_paranum > 1){
            throw "The same parameter can occur only once";
        }

        if(wc1_paranum == 1 && WordLens && specWordLens){
            throw "-w and -n cannot be choosed together";
        }
        // if(specWordLens && specLength <2){
        //     std::cout << "Word length should >1" <<std::endl;
        //     exit(0);
        // }
        // if(spechead && (temp_head.size()!=1 || !isalpha(temp_head[0]))){
        //     throw "The value of -h should be a character";
        //     exit(0);
        // }
        // else if(spechead) head = char(temp_head[0]);
        // if(spectail && (temp_tail.size()!=1 || !isalpha(temp_tail[0]))){
        //     throw "The value of -t should be a character";
        //     exit(0);
        // }
        // else if(spectail) tail = char(temp_tail[0]);
    }catch(char const *s){
        cerr << s << endl;
        exit(1);
    }
    
}

void cmdParametersParser(int argc, char **argv){
    int ch;
    while((ch=getopt(argc,argv,"wch:t:n:f:"))!=-1)
    {
        switch(ch)
        {
            case 'w':
                    WordLens = true;
                    wc1_paranum ++;
                    break;
            case 'c':
                    WordLens = false;
                    wc1_paranum ++;
                    break;
            case 'h':head = *optarg;
                    h_paranum ++;
                    COUT(head);break;
            case 't':tail = *optarg;
                    t_paranum ++;
                    COUT(tail);break;
            case 'n':specWordLens = true;
                    n = StringtoNum(optarg);
                    n_paranum ++;
                    COUT(n);
                    break;
            case 'f':filename = optarg;
                    f_paranum ++;
                    COUT(FileName);
                    break;
            default:;
        }
    }
}

int main(int argc, char *argv[])
{
    string rawstr;
    vector<string> result;
    vector<vector<string>> result1;
    string outFileName = "../data/solution.txt";

    cmdParametersParser(argc, argv);
    HandleException();
    wordList::text_preprocess(filename,rawstr);

    //call the api according to the cmd arguments
    if(specWordLens && WordLens) wordList::get_chain_spec(rawstr,n,result1,head,tail);
    else if(specWordLens) maxletter = wordList::get_chain_char(rawstr,result,head,tail,true,n);
    else if(WordLens) wordList::get_chain_word(rawstr,result,head,tail);
    else maxletter = wordList::get_chain_char(rawstr,result,head,tail);
    //output the result to specified file
    if(specWordLens && WordLens) Outputspec(result1,outFileName);
    else Output(result,outFileName);
    return 0;
}