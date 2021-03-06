/******************************************************************************
  @ File Name: huffmanzip.h
  @ Authors: 08015338
  08015436
  08015437
  08015438
  @ Description:this file is the core algorithm header file included by the 
  project, providing the definition of classes, varibles, micros and 
  functions.
  @ Compiler: we strongly recommend you to compile this project with GCC g++
  compiler supporting c++11 standard. We have tested this project with 
  GCC g++ 5.4.0 compiler and finished an RC version in current dictionary.
  @ Copyright by authors
 ******************************************************************************/

#ifndef HUFFMANZIP_H
#define HUFFMANZIP_H



/******************************************************************************
 * please include all header files here and do not 
 * attempt to include header files at other place
 *****************************************************************************/
#include<iostream>
#include<algorithm>
#include<climits>
#include<thread>
#include<fstream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<map>
#include<sstream>
#include<stack>
#include<queue>
using namespace std;

/******************************************************************************
 * here are micros to call in the project
 *****************************************************************************/



/******************************************************************************
 * here are classes of the project
 *****************************************************************************/

class Node
{
	public:
		char chName;
		Node* child0=nullptr;
		Node* child1=nullptr;
		long long weight=0;
		short n=-1;
		Node* parent=nullptr;
	public:
		bool isCoded=false;
		Node* GetChild(short i);
		Node(Node* child0,Node* child1);
		Node(char,long long);
		Node();
};

class HuffmanTree
{
	private:
		vector<Node> nodes;
		Node* root=nullptr;
		void __MakeCode();
	public:
		void BuildTree();
};
struct ThreadEncodeParam
{
	int count;
	int number;
	string URL;
	string FileName;
};
class Methods
{
	public:
		static void SetFile(string PATH,string FileName);
		static void EncodeFile(string PATH,string FileName,short threadCount,void* param=nullptr);
		static void DecodeFile(string PATH,string FileName,short threadCount,void* param=nullptr);
		static void CountFreq(string PATH,string FileName);
		static void BuildTree(string PATH,string FileName);
		static void WriteLog(string PATH,string FileName,short threadCount);
		static void Finalize();
	private:
		static void* __ThreadEncodeFile(int,int);	
        static void* __ThreadDecodeFile(int i,int n);
};


map<char,string> temp;
map<string,char> temp_dictionary;
map<string,string>temp_trueorfalse;
class global
{
	public:
		static map<char,string> huffmanMap;
		static string PATH;
		static string FileName;
		static int fileLength;
		static long long* Freq;
        static char *Ans;
        static map<string,char>Dictionary;
        static map<string,string>trueorfalse;
};


map<char,string> global::huffmanMap=std::move(temp);
string global::PATH="";
string global::FileName="";
int global::fileLength=0;
long long* global::Freq=nullptr;
char *global::Ans=nullptr;
map<string,char>global::Dictionary=std::move(temp_dictionary);
map<string,string>global::trueorfalse=std::move(temp_trueorfalse);


/************************************************************************************
 * @Function definition for class Node
 ***********************************************************************************/

/**
 * @brief GetChild		get the child of current node
 *
 * @param i				huffman code of child
 *
 * @return		nullptr					when current node is a leaf
 *				pointer to child		when current node is not a leaf
 */
Node* Node::GetChild(short i)
{
	if(i==0)
		return this->child0;
	if(i==1)
		return this->child1;
	cerr<<"argument error: invalid argument in function Node::GetChild";
	exit(1);
}

/**
 * @brief Node called only when making huffman tree, make a parent node for child0,child1
 *
 * @param child0
 * @param child1
 */
Node::Node(Node* child0,Node* child1)
{
	this->weight=child0->weight+child1->weight;
	this->child0=child0;
	this->child1=child1;
}

Node::Node()
{

}
Node::Node(char ch,long long freq)
{
	this->weight=freq;
	this->chName=ch;
	this->child0=nullptr;
	this->child1=nullptr;
}

/************************************************************************************
 * @Function definition for class HuffmanTree
 ***********************************************************************************/

/**
 * @brief BuildTree			 estabilsh huffman tree
 */
void HuffmanTree::BuildTree()
{
	int x=0,y;
	Node treenodes[512];
	for(int i=0;i<256;++i)
	{
		if(global::Freq[i]!=0)
		{
			treenodes[x]=Node(char(i-128),global::Freq[i]);
			x++;
		}
	}
	Node* temp1,* temp2,*tt;
	tt=new Node(1,1);
	tt->weight=LLONG_MAX;
	x--;
	y=x;
	while(y--)
	{
		temp2=tt;
		temp1=tt;
		for(int i=0;i<2*x-y;i++)
		{
			if(treenodes[i].isCoded==false&&treenodes[i].weight<temp1->weight)
			{
				temp2=temp1;
				temp1=&treenodes[i];
			}
			else if(treenodes[i].isCoded==false&&treenodes[i].weight<temp2->weight)
				temp2=&treenodes[i];
		}
			temp1->n=0;
			temp2->n=1;
			temp1->isCoded=temp2->isCoded=true;
			treenodes[2*x-y]=Node(temp1,temp2);
			temp1->parent=temp2->parent=&(treenodes[2*x-y]);
	}
	delete tt;

	Node node;
	for(int i=0;i<=x;i++)
	{
		node=treenodes[i];
		
		string code;
		stringstream ss;
		Node* t;
		t=&node;
		while(t->parent!=nullptr)
		{
			ss<<t->n;
			t=t->parent;
		}
		ss>>code;
		reverse(code.begin(),code.end());
		Node* tem=&(treenodes[2*x-1]);
		for(short bar: code)
		{
			tem->GetChild(bar-'0');
		}
		global::huffmanMap.emplace(node.chName,code);
	}

	
}

/************************************************************************************
 * @Function definition for class Methods
 ***********************************************************************************/

/**
 * @brief EncodeFile		encode a txt file 
 *
 * @param PATH				path to the current executable file
 * @param FileName			name of the file to encode
 * @param threadCount		number of threads function can allocate
 * @param param				additional paramenters needed(if necessary)
 */
void Methods::EncodeFile(string PATH,string FileName,short threadCount,void* param)
{
	std::thread thread[8];
	ThreadEncodeParam thparam[8];
	short i=0;
	for(i=0;i<threadCount;i++)
	{
		thread[i]=std::thread(&__ThreadEncodeFile,i,threadCount);
		cout<<"executing thread "<<i;
	}
	for(i=0;i<threadCount;i++)
	{
		thread[i].join();
	}

}

/**
 * @brief DecodeFile		decode a binary file 
 *
 * @param PATH				path to the current executable file
 * @param FileName			name of the file to encode
 * @param threadCount		number of threads function can allocate
 * @param param				additional paramenters needed(if necessary)
 */
void Methods::DecodeFile(string PATH,string FileName,short threadCount,void* param)
{
	//TODO: edit your function code here
        std::thread thread[8];
        short i=0;
        long long length;
        string s="";
        s=PATH+FileName+".log";
        freopen(s.data(),"r",stdin);
        int num_thread;
        cin>>num_thread>>length;
        global::fileLength=length;
        string dst=global::PATH;
        dst+=FileName;

        //build the map:
        int asc;
        string code;

        global::Ans=new char[global::fileLength];

        while(cin>>asc>>code)
        {
            global::Dictionary[code]=char(asc);
            global::trueorfalse[code]=code;
        }

        //

       // cout<<threadCount<<" "<<global::fileLength<<endl;
        for(i=0;i<num_thread;i++)
        {
            thread[i]=std::thread(&__ThreadDecodeFile,i,num_thread);
            //cout<<"executing thread "<<i<<endl;
        }
        for(i=0;i<num_thread;i++)
        {
            thread[i].join();
        }
        ofstream outfile(dst.data(),ios::binary);
        outfile.write(global::Ans,global::fileLength);
        outfile.close();
}

/**
 * @brief CountFreq			count the frequency of characters
 *
 * @param PATH				path to the current executable file
 * @param FileName			name of the file to encode
 */
void Methods::CountFreq(string PATH,string FileName)
{
	ifstream read(PATH+FileName,ifstream::in|ifstream::binary);

	global::Freq=new long long[256];
	memset(global::Freq,0,256*sizeof(long long));
	char c;
	while(!read.eof())
	{
		++global::fileLength;
		read.get(c);
		global::Freq[128+int(c)]++;
	}
    global::fileLength-=1;
	read.close();
}

/**
 * @brief BuildTree  establish a temporary huffman tree to gain a map of 
 *					characters and its code
 *
 * @param PATH
 * @param FileName
 */
void Methods::BuildTree(string PATH,string FileName)
{
	HuffmanTree tempTree;
	tempTree.BuildTree();
}

/**
 * @brief __ThreadEncodeFile    called for a single thread to encode the txt file
 *
 * @param param					paramenters needed
 *
 */
void* Methods::__ThreadEncodeFile(int i,int n)
{
	
	string src=global::PATH;
	string dst=global::PATH;
	src+=global::FileName;
	dst+=global::FileName;
	dst+=char('0'+i);
	dst+=".bin";

	uint buffer;//regard buffer as a queue of boolean varibles
	buffer^=buffer;

	uint hufcode=0B0;
	short pos=31;

	ifstream charin(src,ios::binary);
	ofstream charout(dst,ios::out);
	long long charCount=(global::fileLength/n)+
		(global::fileLength%n>i?1:0);

	char buf;
	charin.seekg(i,ios::cur);

	while(charCount--)
	{
		charin.read(&buf,1);
		charin.seekg(n-1,ios::cur);
		for(char c: global::huffmanMap[buf])
		{
			buffer|=(c-'0')<<(pos--);
			if(pos==23)
			{
				hufcode=buffer>>24;
				charout<<char(uint(hufcode));
				pos+=8;
				buffer<<=8;
                //cout<<"thread: "<<i<<endl<<hex<<uint(hufcode)<<endl;
			}
		}
	}
	hufcode=buffer>>24;
    //cout<<"thread: "<<i<<endl<<hex<<uint(hufcode)<<endl;
	charout<<(char)hufcode;
	charin.close();
	charout.close();
}


/**
 * @brief __ThreadDecodeFile	called for a single thread to decode the binary file
 *
 * @param param					paramenters needed
 *
 */
void* Methods::__ThreadDecodeFile(int i,int n)
{
	//TODO: edit your function code here
    string src=global::PATH;
    string log=global::PATH;
    queue <char> temp1;

    src+=global::FileName;
    src=src.substr(0,src.length()-4);
    src+=char('0'+i);
    src+=".bin";

    log+=global::FileName;
    log+=".log";



    /*Build the map*/


    ifstream infile(src,ios::binary);

    infile.seekg(0,ios::end);
    long long length_temp=infile.tellg();
    infile.seekg(0,ios::beg);
    char *source=new char[length_temp+1];
    infile.read(source,length_temp);



    //cout<<source<<endl;
    for(int j=0;j<length_temp;j++)
    {
        if(((source[j])&0x80)==0x80)temp1.push('1');
        else temp1.push('0');

        if((source[j]&0x40)==0x40)temp1.push('1');
        else temp1.push('0');

        if((source[j]&0x20)==0x20)temp1.push('1');
        else temp1.push('0');

        if((source[j]&0x10)==0x10)temp1.push('1');
        else temp1.push('0');

        if((source[j]&0x08)==0x08)temp1.push('1');
        else temp1.push('0');

        if((source[j]&0x04)==0x04)temp1.push('1');
        else temp1.push('0');

        if((source[j]&0x02)==0x02)temp1.push('1');
        else temp1.push('0');

        if((source[j]&0x01)==0x01)temp1.push('1');
        else temp1.push('0');


    }

    string s="";
    long long num=0;
    long long thisthread=global::fileLength/n;
    if(i<global::fileLength%n)thisthread++;


    for(;num<thisthread;){
        //s.clear();
        for(int t=0;t<50;t++)
        {
            s+=temp1.front();
            temp1.pop();
            if(global::trueorfalse[s]==s){
                    global::Ans[n*num+i]=global::Dictionary[s];
                    s.clear();
                    num++;
                    break;
            }
        }
    }

}

void Methods::Finalize()
{
	delete[] global::Freq;
	global::Freq=nullptr;
	global::PATH.erase();
	global::FileName.erase();
	global::fileLength=0;
	global::huffmanMap.clear();
    global::Ans=nullptr;
    global::Dictionary.clear();
    global::trueorfalse.clear();
}


void Methods::WriteLog(string PATH,string FileName,short threadCount)
{
	fstream dout(PATH+FileName+".log",ios::out);
	dout<<threadCount<<' '<<global::fileLength<<endl;
	for(auto& bar: global::huffmanMap)
		dout<<int(bar.first)<<' '<<bar.second<<endl;
}
#endif
/*--End-Of-File--*/
