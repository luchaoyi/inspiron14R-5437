//广义表是递归定义的

typedef enum{ATOM,LIST}ElemTag;
typedef struct GLNode{
	ElemTag tag;
	union{
		AtomType atom;
		struct GLNode *hp;
	};

	struct GLNode *tp; //相当于next指针指向下一个元素，如果有下一个元素则下一个元素必定为列表递归定义的
}

//另一种存储结构
typedef struct GLNode{
	ElemTag tag;
	union{
		AtomType atom;
		struct {
			GLNode *hp,*tp 
		}ptr;
	};

}

//递归函数设计时将递归操作当作一个简单的已有的可靠的函数调用不去怀疑它
//正如数学归纳法归纳时不去怀疑假设一样，递归函数就是一个假设


int GListDepth(GList L)
{
	if(!L ) return 1 ; //() 空表depth 1
	if(L.tag== ATOM) return 0;

	 return max(GListDepth(L->hp),GListDepth(L->tp))+1; //两个子元素深度
}


Status CopyList(GList &T,GList L)
{
	if(!L) T=NULL;
	else
	{
		if(!(T=(GList*)malloc(sizeof(GLNode)))) exit(OVERFLOW);
		T->tag=L->tag;

		if(L->tag == ATOM) T->atom=L->ATOM;
		else
		{
			CopyList(T->hp,L->hp);
			CopyList(T->tp,L->tp);

		}
	}
}



Status CreateGList(GList &L,SString S)
{
	"emp=()"
	if(StrCompare(S,emp)) L=NULL;
	else
	{
		if(...) exit(OVERFLOW); //malloc L

		//单个字符的字符串
		if(StrLength(S) == 1) 
		{
			L->tag=ATOM;
			L->atom=S;
		}
		//递归递归版
		else
		{
			L->tag=LIST;
			sever(S,hS);//分离 S='abcde'->S='a'+' S' '
			CreateGList(L->hp,hS);
			CreateGList(L->tp,S);
		}
		
	}
}



