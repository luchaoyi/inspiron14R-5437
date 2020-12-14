//子串匹配，搜索S第pos个之后位置,暴力匹配
int Index_BF(S,T,pos)
{
	if(StrEmpty(S)||StrEmpty(T)||pos<0) return ERROR;
	n=StrLength(S);
	m=StrLength(T);

	for(i=pos;i<=n-m;i++)
	{
		flag=1;
		for(j=0;j<m;j++)
		{
			if(S[i+j]!=T[j])
			{
				flag=0;
				break;
			}
		}
		if(flag==1) return i;
	}
	return 0

}

//1.定长顺序存储
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1]; //PASCAL语言中0号存放串长度，而不用'\0'结束


//T=S1+S2 定长切掉 > MAXSTRLEN
Status Concat(SString &T,SString S1,SString S2)
{
	if(S1[0]>=MAXSTRLEN) 
	{
		T=S1;
		return (CUT);
	}
	
	if(S1[0]+S2[0]>MAXSTRLEN)
	{
		T[1:end]=(S1[1:end],S2[1:MAXSTRLEN-S1[0]]);
		T[0]=MAXSTRLEN;
		return (CUT);
	}
	else
	{
		T[1:end]=(S1[1:end],S2[1:end]);
		T[0]=S1[0]+S2[0];
		return (NCUT);
	}
}

//截取子串
Status SubString(SString &Sub,S,pos,len)
{
	//上下界，定义域
	if(pos<=0||len<0 ||pos>S[0] || len>S[0]+1-pos ) return ERROR;

	//pos 2:len 3: |2 3 4 |2+3-1|  1 2 3|1:len|
	Sub[1:len]=S[pos:pos+len-1];
	S[0]=len;

	return OK;
}
//定长切掉了尾部
//next下一次失配匹配位置i不回溯


/*

	while(i<=S[0] && j<=T[0]) //1-S[0]
	{
		if(S[i]==P[j])
		{
			i++;
			j++;
		}
		else
		{
			j=next[j];
			if(j==0)
			{
				i++;
				j=1; //j=0->j=1 j++
			}
		}	
	}
*/

//next 与 KMP 很相似 自身匹配自身 匹配则满足递推 next[j+1]=next[j]+1 
//否则回溯在推
void get_next(SString T,int next[])
{
	i=1;
	next[1]=0;
	j=0;

	while(i<T[0])
	{
		if(j == 0 || T[i]==T[j]) {
			
			i++;
			j++;
			next[i]=j;
 
		}

		else
		{
			j=next[j];
		}
	}
}

//改进 next数组存储的Si与Pj在失配时使j回溯的回溯点
//if Si!=Pj  -->j=next[j] 
//在判断 Si与Pj(回溯后j)但是 若 Pj=P(next[j]) 回溯点与回溯点相等则 Si != Pj(回溯后j)
//则会引发继续回溯
//所以改进next在填入next位置时判断Pi==Pj  j是k的位置即当前前缀匹配位置也是回溯点位置 i为假设P串失配位置则此处
//将next[i] i失配回溯位置 原来next[i]=j即i失配时回溯到j匹配Pj改为 next[i]=next[j]即由于相等时
//i回溯处会继续生回溯还不如让其直接为j回溯位置即回溯点的回溯点这样将所有点关联起来则按先后顺序填入的位置就是
//回溯到头的点
void get_next(SString T,int next[])
{
	i=1;
	next[1]=0;
	j=0;

//j is k 
	while(i<T[0])
	{
		if(j == 0 || T[i]==T[j]) {
			
			i++;
			j++;

			k=j;

			if(T[i]!=T[j])
			{
				//next[i]=j;
				next[i]=k;
			}
			else
				next[i]==next[j];
 
		}

		else
		{
			//失配回溯位置
			k=next[j];
			j=k;
			//j=next[j];
		}
	}
}


//算法思想描述

int index KMP(int pos,int *next,SString S,SString P)
{
	if(pos<=0 || pos>S[0]-P[0]+1) return ERROR;
	i=1,j=1;

	while(i<=S[0] && j<=T[0]) //1-S[0]
	{
		if(j=0||S[i]==P[j])
		{
			i++;
			j++;
		}
		else
		{
			j=next[j];
		}
	}

	if(j>T[0]) return i-T[0];
	else return 0;
}


//串操作，长度变化时需释放原空间重新分配空集
Status StrInsert(HString &S,int pos,HString T){
	if(pos<1 || pos >S.length+1) return ERROR;
	if(T='') return OK;

	S.ch=(char*)realloc(sizeof(char)*(S.length+T.length));
	if(!S.ch) exit(OVERFLOW);
//先安全
//后逻辑
    
	for(i=S.length-1;i>=pos;i--)
	{
		//后移insert长度
		//pos前insert ==pos 继续移动
		S.ch[i+T.length]=S.ch[i];
	}
	//Insert
	for(i=0;i<T.length;i++) S.ch[pos+i]=T.ch[i];
}

int StrCompare(HString S,HString T)
{
	for(i=0;i<S.length&&i<T.length;++i)
	{
		if(S.ch[i]!=T.ch[i])
			return S.ch[i]-T.ch[i];
	}

	return S.length-T.length;
}
//3.串的链or块链存储
//A-->B-->C     | ABC-->DEF




//---------------------------------------------------------------------------//
































