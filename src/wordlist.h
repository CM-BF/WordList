#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
#include<stdio.h>

#define LIMITED_MAX 1000000000


namespace wordList{

    struct cell{
        int count;
        int estimatedMax;
        std::vector<std::string> array;
    };

    class CwordMatrix{
        private:
        struct cell matrix[26][26];
        
        public:
        CwordMatrix(){
            for(int i=0; i<26; i++){
                for(int j=0; j<26; j++){
                    matrix[i][j].count = 0;
                    matrix[i][j].estimatedMax = LIMITED_MAX;
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
            matrix[begin - 'a'][end - 'a'].array.push_back(word);
        }

        std::string popWord(char begin, char end){
            auto word = matrix[begin - 'a'][end - 'a'].array.back();
            matrix[begin - 'a'][end - 'a'].array.pop_back();
            return word;
        }

    };

    CwordMatrix wordMatrix;
    std::string inFileName = "../data/inFile.txt";
    std::string outFileName;
    
    std::vector<std::string> filter(std::string);
}
