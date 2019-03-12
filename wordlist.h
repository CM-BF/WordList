#include<iostream>
#include<vector>
#include<string>


namespace wordList{

    struct cell{
        int count;
        std::vector<std::string> array;
    };

    class wordMatrix{
        struct cell matrix[26][26];

        int getCountByPos(char begin, char end){
            return matrix[begin - 'a'][end - 'a'].count;
        }

        std::vector<std::string> getArrayByPos(char begin, char end){
            return matrix[begin - 'a'][end - 'a'].array;
        }
    };
    
}
