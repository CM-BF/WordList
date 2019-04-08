#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
#include<stdio.h>
#include<algorithm>
#include<time.h>
#include<unistd.h>
using namespace std;

#define LIMITED_MAX 1000000000

#ifndef __WORDLIST_H__
#define __WORDLIST_H__

namespace wordList{

    struct cell{
        int count;
        int estimatedMax;
        std::vector<std::string> array;
    };

    int  wc1_paranum = 0,h_paranum=0,t_paranum =0,n_paranum=0,f_paranum=0; 
    std::string temp_head,temp_tail;
    
    extern int wc_paranum;
    extern bool WordLens;   //find the list with max words or max letters 
    extern bool specWordLens;  // para -n
    extern bool spechead ,spectail; //para -h -t
    extern bool inputfromscreen; //when use cmd,represent para -f
    extern char head,tail;
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
    void HandleException();
    //new Functions for lab1-2
    extern "C"
    {
    void text_process(char* filename, const char* rawstr);
    int get_chain_word(char* words,std::vector<std::string> &result,char head,char tail);
    int get_chain_char(char* words,std::vector<std::string> &result,char head,char tail);
    int get_chain_spec(char* words,int n,std::vector<std::vector<std::string>> &result,char head,char tail);
    }
    void Find_WordList();

    extern CwordMatrix wordMatrix;
    typedef struct {
        char begin;
        char end;
    }wordSides;
    extern std::vector<wordSides> maxWordList;
    extern std::vector<wordSides> tempMaxWordList;
    extern std::vector<std::vector<wordSides>> specWordLists;
    extern std::vector<std::string> tempspecWordList;
    extern int maxLength;
    extern int tempEstimatedMaxLength;
    extern int specLength;
    extern int recDeep;
    extern clock_t begin,end;
    //new variables for lab1-2
    //vectors that save return value 
    extern std::vector<std::string> maxWordList_api;
    extern std::vector<std::vector<std::string>> specWordLists_api;

    extern std::string result;
    extern std::string FileName;
    extern std::string inFileName;
    extern std::string outFileName;
    
    
}
#endif