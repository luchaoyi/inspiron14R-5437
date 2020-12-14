/*************************************************************************
    > File Name: trie.cpp
    > Author: lcy
    > Mail: 751714700@qq.com 
    > Created Time: 2017年11月14日 星期二 15时12分41秒
 ************************************************************************/
//Prefix Tree
#include<string>
#include<iostream>
#include<stdio.h>
using namespace std;


#define ALPHABET_SIZE 26


typedef struct trie_node{

	//bool isKey; //只需要判断字符串是否存在的则不需要记录数字
	int count;//记录该节点代表的单词个数
	trie_node *children[ALPHABET_SIZE];
}* trie;

trie_node * create_trie_node(){
	trie_node* pNode = new trie_node();
	pNode->count=0;
	for(int i=0;i<ALPHABET_SIZE;++i)
		pNode->children[i]=NULL;
	return pNode;
}



void trie_insert(trie root,char *key){
	trie_node* node=root;
	char *p=key;
	while(*p){
		if(node->children[*p-'a']==NULL){
			node->children[*p-'a']=create_trie_node();
		}
		node=node->children[*p-'a'];
		++p;
	}

	node->count+=1;//读到字符串尾部，此位置计数+1,计数为０的不存在，只是前缀
}


/*
 不存在返回0，不存在计数为０代表是一个前缀，为NULL代表彻底没有
 存在返回次数
 * */
int trie_search(trie root,char *key){
	trie_node* node=root;
	char *p=key;

	while(*p &&node!=NULL){
		node=node->children[*p-'a'];
		++p;
	}

	if(node==NULL)
		return 0;
	else
		return node->count;
}




//c+s+r 反撤销
int main(){
	char keys[][8]={"the","a","there","answer","any","by","bye","their"};
	trie root=create_trie_node();
	for(int i=0;i<8;i++){
		trie_insert(root,keys[i]);
	}
	 // 检索字符串
    char s[][32] = {"Present in trie", "Not present in trie"};
    printf("%s --- %s\n", "the", trie_search(root, "the")>0?s[0]:s[1]);
    printf("%s --- %s\n", "these", trie_search(root, "these")>0?s[0]:s[1]);
    printf("%s --- %s\n", "their", trie_search(root, "their")>0?s[0]:s[1]);
    printf("%s --- %s\n", "thaw", trie_search(root, "thaw")>0?s[0]:s[1]);

    return 0;
}


