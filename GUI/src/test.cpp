#include"wordlist.h"
#include<iostream>
#include<string>
using namespace std;

int main(){
    char s[] = "asdf fsetsgsdgdshf fsersds Fsrtf sdfsg dfhd dfv veTry ye eth hup pose";
    int lens;
    //vector<string> result;
    vector<vector<string>> result;
    lens=wordList::get_chain_spec(s,3,result,0,0);
    cout << lens <<endl;
    //for(auto it = result.begin();it != result.end();it++)
    //    cout << *it << endl;
    for(auto it1 = result.begin();it1 != result.end();it1++){
        for(auto it2 = it1->begin();it2 != it1->end();it2++)
                cout << *it2 <<endl;
        cout << endl;
    }
}