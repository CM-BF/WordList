#include<gtest/gtest.h>
#include<string>
#include<vector>
#include"wordlist.h"
using namespace std;

string s = "asdf fsetsgsdgdshf fsersds Fsrtf sdfsg dfhd dfv veTry ye eth hup pose";
string ss = "  ";
char filename[] = " ";
int lens;
vector<string> result1;
vector<vector<string>> result2;
string a,b;
//test get_chain_word
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
//test get_chain_char
TEST(Test2,FindMaxLettersChain)
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
//test the head letter and tail letter
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
//test get_chain_spec
TEST(Test4,FindSpecLengthChain)
{
    lens = wordList::get_chain_spec(s,3,result2,0,0);
    ASSERT_EQ(lens,16);
    for(auto it = result2.begin();it != result2.end();it++)
        ASSERT_EQ(it->size(),3);
}

//test find the most letters chain with length of n
TEST(Test5,NandC)
{
    lens = wordList::get_chain_char(s,result1,0,0,true,3);
    ASSERT_EQ(lens,25);
    ASSERT_EQ(result1.size(),3);
}
//test exception:file doesn't exist
TEST(Test6,EXCEPTION_OPENFILE)
{
    EXPECT_DEATH(wordList::text_preprocess(filename,s),"File does not exist or no file choosed");
}

//test exception:The head is not a letter
TEST(Test7,EXCEPTION_HEAD)
{
    EXPECT_DEATH(wordList::get_chain_word(s,result1,1,0),"The value of argument -h must be a letter");
}

//test exception:The tail is not a letter
TEST(Test8,EXCEPTION_TAIL)
{
    EXPECT_DEATH(wordList::get_chain_word(s,result1,0,1),"The value of argument -t must be a letter");
}

//test exception:thers is no word in the file
//ss is an empty string
TEST(Test9,EXCEPTION_EMPTY)
{
    EXPECT_DEATH(wordList::get_chain_word(ss,result1,0,0),"There is no words in input file");
}

//test exception:n is too small
TEST(Test10,EXCEPTION_N)
{
    EXPECT_DEATH(wordList::get_chain_spec(s,-1,result2,0,0),"The specified word length must >1");
}

int main(int argc,char*argv[])
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}