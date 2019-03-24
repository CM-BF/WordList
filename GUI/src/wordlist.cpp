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

bool wordList::Compare(const std::string s1,const std::string s2)
{
    return s1.length() > s2.length();
}


void wordList::loadingWords(){
    std::unordered_map<std::string, int> Smap;
    if(!inputfromscreen){
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
    else{
        auto Svector = filter(inFileName);
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
    
    outputMatrix();
}

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

/*
void wordList::DFS_spechead(char begin)
{
    if(specWordLens) DFS_specwordlens(0,begin);
    else DFS(0,begin);
}*/

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
    result += to_string(maxLength) + '\n';
    for(auto it=maxWordList.begin(); it!=maxWordList.end(); it++){
        auto wordsides = *it;
        auto word = wordMatrix.popWord(wordsides.begin, wordsides.end);
        COUT(word);
        result += word + '\n';
    }
    COUT("");
}

void output_print(int deep,std::vector<wordList::wordSides> tempwordList){
    if(deep == tempwordList.size()){
        for(auto it=wordList::tempspecWordList.begin(); it!=wordList::tempspecWordList.end(); it++){
            COUT(*it);
            wordList::result += *it + '\n';
        }
        wordList::result += '\n';
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
    int totalnum = 0;
    int tempnum = 1;
    for(auto it1 = specWordLists.begin();it1!=specWordLists.end();it1++){
        auto onewordlist = *it1;
        tempnum = 1;
        for(auto it2 = onewordlist.begin();it2 != onewordlist.end();it2++){
            auto wordsides = *it2;
            tempnum *= wordMatrix.getsize(wordsides.begin,wordsides.end);
        }
        totalnum += tempnum;
    }
    COUT(totalnum);
    result += to_string(totalnum) + '\n';
    for(auto it1 = specWordLists.begin();it1!=specWordLists.end();it1++){
        output_print(0,*it1);
        COUT("");
        result += '\n';
    }
}

void HandleException()
{
    if(wordList::wc_paranum == 0 && !wordList::specWordLens){
        std::cout << "-w or -c or -n must be chooesd " <<std::endl;
        exit(0);
    }

    if(wordList::wc_paranum > 1){
        std::cout << "parameters conflict" <<std::endl;
        exit(0);
    }

    if(wordList::inputfromscreen){
        std::cout <<"no file opened" <<std::endl;
        exit(0);
    }
    if(wordList::wc_paranum == 1 && wordList::WordLens && wordList::specWordLens){
        std::cout << "-w and -n cannot be choosed together" <<std::endl;
        exit(0);
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

int main(int argc,char **argv){
    
    cmdParametersParser(argc, argv);
    HandleException();
    wordList::loadingWords();
    
    
    wordList::Find_WordList();
    if(wordList::specWordLens && wordList::WordLens) wordList::outputspecWordList();
    else wordList::output();

    return 0;
}

void Init()
{
    wordList::result = "";
    wordList::recDeep = 0;
    wordList::maxLength = 0;
    wordList::tempEstimatedMaxLength = 0;
    wordList::maxWordList.clear();
    wordList::tempMaxWordList.clear();
    wordList::specWordLists.clear();
    wordList::tempspecWordList.clear();
    wordList::wordMatrix.Init();
    wordList::begin = clock();
}

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
}
