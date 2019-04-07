#include<gtest/gtest.h>
#include<string>
#include<vector>
#include"wordlist.h"
using namespace std;

char s[] = "asdf fsetsgsdgdshf fsersds Fsrtf sdfsg dfhd dfv veTry ye eth hup pose";
int lens;
vector<string> result1;
vector<vector<string>> result2;
string a,b;

TEST(Test1,FindMaxWordsChain)
{
    lens = wordList::get_chain_word(s,result1,0,0);
    ASSERT_EQ(lens,7);
    for(int i = 0;i < result1.size()-1;i++){
        a = result1.at(i);
        b = result1.at(i+1);
        ASSERT_EQ(a[a.size()-1],b[0]);
    }
    result1.clear();
}

TEST(Test2,FindMaxCharsChain)
{
    lens = wordList::get_chain_char(s,result1,0,0);
    ASSERT_EQ(lens,34);
    for(int i = 0;i < result1.size()-1;i++){
        a = result1.at(i);
        b = result1.at(i+1);
        ASSERT_EQ(a[a.size()-1],b[0]);
    }
    result1.clear();
}

TEST(Test3,FindSpecHTChain)
{
    lens = wordList::get_chain_word(s,result1,'d','p');
    ASSERT_EQ(lens,6);
    for(int i = 0;i < result1.size()-1;i++){
        a = result1.at(i);
        b = result1.at(i+1);
        ASSERT_EQ(a[a.size()-1],b[0]);
        if(i==0) ASSERT_EQ(a[0],'d');
        if(i==result1.size()-2) ASSERT_EQ(b[b.size()-1],'p');
    }
    result1.clear();
}

TEST(Test4,FindSpecLengthChain)
{
    lens = wordList::get_chain_spec(s,3,result2,0,0);
    ASSERT_EQ(lens,16);
    for(auto it = result2.begin();it != result2.end();it++)
        ASSERT_EQ(it->size(),3);
}

int main(int argc,char*argv[])
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}