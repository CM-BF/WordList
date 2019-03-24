#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
#include<stdio.h>
#include<algorithm>
#include<time.h>
#include<unistd.h>

#define LIMITED_MAX 1000000000


namespace wordList{

    struct cell{
        int count;
        int estimatedMax;
        std::vector<std::string> array;
    };

    bool WordLens = true;   //find the list with max words or max letters 
    int  wc_paranum = 0;     //para -w -c
    bool specWordLens = false;  // para -n
    bool spechead = false,spectail = false; //para -h -t
    bool inputfromscreen = false; //when use cmd,represent para -f
    char head,tail='f';
    bool Compare(const std::string s1,const std::string s2);

    class CwordMatrix{
        private:
        struct cell matrix[26][26];
        
        public:
        CwordMatrix(){
            Init();
        }

        void Init(){
            for(int i=0; i<26; i++){
                for(int j=0; j<26; j++){
                    matrix[i][j].count = 0;
                    matrix[i][j].estimatedMax = LIMITED_MAX;
                    matrix[i][j].array.clear();
                }
            }
        }

        void setEstimatedMax(char begin, char end, int estimatedMax){
            matrix[begin - 'a'][end - 'a'].estimatedMax = estimatedMax;
        }

        int estimatedMax(char begin, char end){
            return matrix[begin - 'a'][end - 'a'].estimatedMax;
        }

        int count(char begin, char end){
            return matrix[begin - 'a'][end - 'a'].count;
        }

        int getsize(char begin,char end){
            return matrix[begin - 'a'][end - 'a'].array.size();
        }

        void incCount(char begin, char end){
            matrix[begin - 'a'][end - 'a'].count++;
        }

        void incCount(std::string word){
            auto begin = word.at(0);
            auto end = *(word.end()-1);
            matrix[begin - 'a'][end - 'a'].count++;
        }

        void decCount(std::string word){
            auto begin = word.at(0);
            auto end = *(word.end()-1);
            matrix[begin - 'a'][end - 'a'].count--;
        }

            

        void decCount(char begin, char end){
            matrix[begin - 'a'][end - 'a'].count--;
        }

        std::vector<std::string> array(char begin, char end){
            return matrix[begin - 'a'][end - 'a'].array;
        }

        void pushWord(std::string word){
            auto begin = word.at(0);
            auto end = *(word.end()-1);
            matrix[begin - 'a'][end - 'a'].array.insert(upper_bound(matrix[begin - 'a'][end - 'a'].array.begin(),
            matrix[begin - 'a'][end - 'a'].array.end(),word,Compare),word);
        }

        std::string getWord(char begin,char end,int pos){
            auto word = matrix[begin - 'a'][end - 'a'].array.at(pos);
            return word;
        }

        std::string popWord(char begin, char end){
            auto word = matrix[begin - 'a'][end - 'a'].array.back();
            matrix[begin - 'a'][end - 'a'].array.pop_back();
            return word;
        }

        int getIncrement(char begin,char end){
            int pos = matrix[begin - 'a'][end - 'a'].count;
            std::string word = matrix[begin - 'a'][end - 'a'].array.at(pos);
            if(WordLens) return 1;
            else return word.length();
        }
        
        std::string erase(char begin,char end,int pos){
            std::string word = matrix[begin - 'a'][end - 'a'].array.at(pos);
            matrix[begin - 'a'][end - 'a'].array.erase(matrix[begin - 'a'][end - 'a'].array.begin() + pos);
            return word;
        }

        void insert(char begin,char end,std::string word,int pos){
            matrix[begin - 'a'][end - 'a'].array.insert(matrix[begin - 'a'][end - 'a'].array.begin()+pos,word);
        }

    };
    
    void loadingWords();
    void DFS(int, char);
    std::vector<std::string> filter(std::string);
    void output();
    void outputspecWordList();
    //void DFS_spechead(char);
    //void DFS_specwordlens(int,char);

    void Find_WordList();

    CwordMatrix wordMatrix;
    typedef struct {
        char begin;
        char end;
    }wordSides;
    std::vector<wordSides> maxWordList;
    std::vector<wordSides> tempMaxWordList;
    std::vector<std::vector<wordSides>> specWordLists;
    std::vector<std::string> tempspecWordList;
    int maxLength = 0;
    int tempEstimatedMaxLength = 0;
    int specLength = 0;
    int recDeep = 0;
    clock_t begin,end;

    std::string result;
    std::string FileName;
    std::string inFileName = "../data/";
    std::string outFileName = "../data/outFile.txt";
    
    
    
}
