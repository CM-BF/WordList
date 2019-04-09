#include"wordlist.h"

using namespace std;
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


bool wordList::WordLens = true;   //find the list with max words or max letters 
int  wordList::wc_paranum = 0;     //para -w -c
bool wordList::specWordLens = false;  // para -n
bool wordList::spechead = false,wordList::spectail = false; //para -h -t
bool wordList::inputfromscreen = false; //when use cmd,represent para -f
char wordList::head,wordList::tail;

wordList::CwordMatrix wordList::wordMatrix;

vector<wordList::wordSides> wordList::maxWordList;
vector<wordList::wordSides> wordList::tempMaxWordList;
vector<vector<wordList::wordSides>> wordList::specWordLists;
vector<string> wordList::tempspecWordList;
int wordList::maxLength = 0;
int wordList::tempEstimatedMaxLength = 0;
int wordList::specLength = 0;
int wordList::recDeep = 0;
int wordList::wordnum = 0;
clock_t wordList::begin,wordList::end;
    //new variables for lab1-2
    //vectors that save return value 
vector<string> wordList::maxWordList_api;
vector<vector<string>> wordList::specWordLists_api;

string wordList::result;
string wordList::FileName;
string wordList::inFileName = "../data/";
string wordList::outFileName = "../data/outFile.txt";

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
/*
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
*/
bool wordList::Compare(const std::string s1,const std::string s2)
{
    return s1.length() > s2.length();
}


void wordList::loadingWords(){
    std::unordered_map<std::string, int> Smap;
    /*if(!inputfromscreen){
        std::ifstream inFile(inFileName);
        while(!inFile.eof())
        {
            std::string S;
            inFile>>S;
            auto Svector = filter(S);
            for(auto it = Svector.begin(); it != Svector.end(); it++){
                auto s = *it;
                if(Smap.count(s) == 0){
                    Smap[s] = 1;
                    COUT(s);
                    wordMatrix.incCount(s);
                    wordMatrix.pushWord(s);
                }          
            }
        }
        inFile.close();
    }
    else{*/
        auto Svector = filter(inFileName);
            for(auto it = Svector.begin(); it != Svector.end(); it++){
                auto s = *it;
                if(Smap.count(s) == 0){
                    Smap[s] = 1;
                    wordnum ++;
                    COUT(s);
                    wordMatrix.incCount(s);
                    wordMatrix.pushWord(s);
                }          
            }
    //}
    
    outputMatrix();
}
/*
void cmdParametersParser(int argc, char **argv){
    int ch;

    while((ch=getopt(argc,argv,"wch:t:n:f:"))!=-1)
    {
        switch(ch)
        {
            case 'w':
                    wordList::WordLens = true;
                    wordList::wc_paranum ++;
                    break;
            case 'c':
                    wordList::WordLens = false;
                    wordList::wc_paranum ++;
                    break;
            case 'h':wordList::head = *optarg;
                    wordList::spechead = true;
                    cout << wordList::head <<endl;break;
            case 't':wordList::tail = *optarg;
                    wordList::spectail = true;
                    cout << wordList::tail <<endl;break;
            case 'n':wordList::specWordLens = true;
                    wordList::specLength = StringtoNum(optarg);
                    cout << wordList::specLength <<endl;
                    break;
            case 'f':wordList::FileName = optarg;
                    wordList::inputfromscreen = false;
                    cout << wordList::FileName << endl;
                    break;
            default:;
        }

    }

}
*/

void wordList::DFS(int deep, char begin){
/*Deep First Search:
branches range from 'a' to 'z'
pay attention that a branch means an end letter of a word in graph. 
When you choose a branch, that means you choose a cell of wordMatrix[last branch][new branch]
Then, we can check the estimatedMax for branch cutting off.*/

/* Parameters:
deep: it doesn't take the vertex decided in this layer into acount, so wordlist length == deep + 1
begin: it is decided by last layer(the end of last word)
*/
    end = clock();
    if(((double)(end-begin)/CLOCKS_PER_SEC)>8.0) return;//when time out,end the search

    for(char i='a'; i<='z'; i++){
        /// choose a branch i
        if(wordMatrix.count(begin, i) == 0)
            continue;
        if(specWordLens && recDeep == specLength)
            continue;
        //COUT("complete");
        if(deep + wordMatrix.estimatedMax(begin, i) > maxLength){
            /// pass branch cutting condition
            wordSides wordsides={begin:begin, end:i};
            /// record list
            tempMaxWordList.push_back(wordsides);

            wordMatrix.decCount(begin, i);
            recDeep++;

            DFS(deep + wordMatrix.getIncrement(begin,i), i);
            wordMatrix.incCount(begin, i);

            recDeep--;
            tempMaxWordList.pop_back();
        }else
        {
            // this branch is cutted, but we have to give an estimation.
            if(wordMatrix.estimatedMax(begin, i) != LIMITED_MAX
            && deep + wordMatrix.estimatedMax(begin, i) > tempEstimatedMaxLength){
                tempEstimatedMaxLength = deep + wordMatrix.estimatedMax(begin, i);
            }
        } 
        if(deep == 0){
            /* variable explaination:
            tempEstimatedMaxLength: it is only for a list that the beginning word has been
            decieded. It's a local estimated max value.
            maxLength: it is a global max value*/ 

            // deep == 0 means it comes back to the first cell(vertex). 
            // It's time to set estimatedMax of this cell.
            wordMatrix.setEstimatedMax(begin, i, tempEstimatedMaxLength);

            // initial tempEstimatedMaxLength for next beginning word list
            tempEstimatedMaxLength = 0;

            tempMaxWordList.clear();
        }     
    }
    if(spectail){
        if(recDeep > 1 && deep >= maxLength && recDeep >= specLength && begin==tail){
        maxLength = deep;
        tempEstimatedMaxLength = maxLength;
        maxWordList = tempMaxWordList;
        if(recDeep==specLength) specWordLists.push_back(maxWordList);
        }
    }
    else {
        if(recDeep > 1 && recDeep >= specLength && deep >= maxLength){
        maxLength = deep;
        tempEstimatedMaxLength = maxLength;
        maxWordList = tempMaxWordList;
        if(recDeep==specLength) specWordLists.push_back(maxWordList);
        }
    }
    
}

void wordList::output(){
    int count[26][26] = {0};
    COUT(maxLength);
    for(auto it=maxWordList.begin(); it!=maxWordList.end(); it++){
        auto wordsides = *it;
        auto word = wordMatrix.popWord(wordsides.begin, wordsides.end);
        maxWordList_api.push_back(word);
        COUT(word);
    }
    COUT("");
}

void output_print(int deep,std::vector<wordList::wordSides> tempwordList){
    if(wordList::specWordLists_api.size()>9999) return;
    if(deep == tempwordList.size()){
        wordList::specWordLists_api.push_back(wordList::tempspecWordList);
        return;
    }
    wordList::wordSides wordsides = tempwordList.at(deep);
    for(int i = 0;i < wordList::wordMatrix.getsize(wordsides.begin,wordsides.end);i++){
        auto word = wordList::wordMatrix.erase(wordsides.begin,wordsides.end,i);

        wordList::tempspecWordList.push_back(word);
        output_print(deep + 1,tempwordList);
        wordList::tempspecWordList.pop_back();
        wordList::wordMatrix.insert(wordsides.begin,wordsides.end,word,i);
    }
}

void wordList::outputspecWordList(){
   
    for(auto it1 = specWordLists.begin();it1!=specWordLists.end();it1++){
        output_print(0,*it1);
        COUT("");
    }
}


void wordList::Find_WordList(){
    if(spechead) DFS(0,head);
    else {
        for(int i='a'; i<='z'; i++){
        // choose a beginning letter, not a beginning word.
        DFS(0, i);
        }
    }
    
}
/*
void wordList::Find_specWordList(){
    if(spechead) DFS_specwordlens(0,head);
    else{
        for(int i='a'; i<='z'; i++){
        // choose a beginning letter, not a beginning word.
        DFS(0, i);
        }
    }
    wordList::outputspecWordList();
}*/

/*
int main(int argc,char **argv){
    
    cmdParametersParser(argc, argv);
    HandleException();
    wordList::loadingWords();
    
    
    wordList::Find_WordList();
    if(wordList::specWordLens && wordList::WordLens) wordList::outputspecWordList();
    else wordList::output();

    return 0;
}
*/
void Init()
{
    wordList::result = "";
    wordList::recDeep = 0;
    wordList::maxLength = 0;
    wordList::tempEstimatedMaxLength = 0;
    wordList::wordnum = 0;
    wordList::maxWordList.clear();
    wordList::tempMaxWordList.clear();
    wordList::specWordLists.clear();
    wordList::tempspecWordList.clear();
    wordList::maxWordList_api.clear();
    wordList::specWordLists_api.clear();
    wordList::wordMatrix.Init();
    wordList::begin = clock();
}


void wordList::HandleException()
{
    try{
        if(spechead && !isalpha(head)){
            throw "The value of argument -h must be a letter";
        }
        if(spectail && !isalpha(tail)){
            throw "The value of argument -t must be a letter";
        }
        if(wordnum == 0){
            throw "There is no words in input file";
        }
        if(specWordLens && specLength < 2){
            throw "The specified word length must >1";
        }

    }
    catch(const char* msg){
        cerr << msg << endl;
        exit(1);
    }
}


void wordList::text_preprocess(char* filename,string &rawstr)
{   
    string s = "";
    string tempstr;
    ifstream inFile(filename);
    try{
        if(!inFile.is_open())
        throw "File does not exist or no file choosed";
    }
    catch(const char* msg){
        cerr << msg <<endl;
        exit(1);
    }
    while(!inFile.eof()){
        inFile >> tempstr;
        s += tempstr + " ";
    }
    rawstr = s;
    inFile.close();
}

int wordList::get_chain_word(string &words,vector<string> &result,char head,char tail)
{
    inFileName = words;
    WordLens = true;
    specWordLens = false;
    inputfromscreen = true;
    if(head!='\0'){
        spechead = true;
        wordList::head = head;
    }
    else spechead = false;
    if(tail!='\0'){
        spectail = true;
        wordList::tail = tail;
    }
    else spectail = false;

    Init();
    wordList::loadingWords();
    HandleException();
    wordList::Find_WordList();
    wordList::output();

    for(auto it = maxWordList_api.begin();it != maxWordList_api.end();it++)
        result.push_back(*it);

    if(result.size()< 2){//if the result contains only one word,it's not acceptable
        result.clear();
        maxLength = 0;
    }
    return maxLength;
}

int wordList::get_chain_char(string &words,vector<string> &result,char head,char tail,bool specn,int n)
{
    inFileName = words;
    WordLens = false;
    specWordLens = specn;
    specLength = n;
    inputfromscreen = true;
    if(head!='\0'){
        spechead = true;
        wordList::head = head;
    }
    else spechead = false;
    if(tail!='\0'){
        spectail = true;
        wordList::tail = tail;
    }
    else spectail = false;
    Init();
    wordList::loadingWords();
    HandleException();
    wordList::Find_WordList();
    wordList::output();

    for(auto it = maxWordList_api.begin();it != maxWordList_api.end();it++)
        result.push_back(*it);
    if(result.size()< 2){//if the result contains only one word,it's not acceptable
        result.clear();
        maxLength = 0;
    }
    
    return maxLength;
}

int wordList::get_chain_spec(string &words,int n,vector<vector<string>> &result,char head,char tail)
{
    inFileName = words;
    WordLens = true;
    specWordLens = true;
    specLength = n;
    inputfromscreen = true;
    if(head!='\0'){
        spechead = true;
        wordList::head = head;
    }
    else spechead = false;
    if(tail!='\0'){
        spectail = true;
        wordList::tail = tail;
    }
    else spectail = false;

    Init();
    wordList::loadingWords();
    HandleException();
    wordList::Find_WordList();
    wordList::outputspecWordList();

    for(auto it = specWordLists_api.begin();it != specWordLists_api.end();it++)
        result.push_back(*it);
    return result.size();
}
/*
extern "C"
{
const char* Kana(char* FileName,bool WordLens,bool spechead,char head,
    bool spectail,char tail,bool specWordLens,int Length,bool inputfromscreen){

        
        wordList::inFileName = FileName;
        wordList::WordLens = WordLens;
        wordList::spechead = spechead;
        wordList::head = head;
        wordList::tail = tail;
        wordList::spectail = spectail;
        wordList::specWordLens = specWordLens;
        wordList::specLength = Length;
        wordList::inputfromscreen = inputfromscreen;

        Init();
        wordList::loadingWords();
        wordList::Find_WordList();
        if(wordList::specWordLens && wordList::WordLens) wordList::outputspecWordList();
        else wordList::output();
        
        COUT(wordList::result);
        return wordList::result.c_str();
    }
}*/