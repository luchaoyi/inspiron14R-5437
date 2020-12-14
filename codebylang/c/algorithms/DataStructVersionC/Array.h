#include<stdarg.h>

#define MAX_ARRAY_DIM 8

typedef struct
{
	ElemType *base;
	int dim; //维数
	int *bounds;//各维长度
	int *constants;
}

/*
下面是 <stdarg.h> 里面重要的几个宏定义如下：
typedef char* va_list;
void va_start ( va_list ap, prev_param );  ANSI version 
type va_arg ( va_list ap, type );
void va_end ( va_list ap );
va_list 是一个字符指针，可以理解为指向当前参数的一个指针，取参必须通过这个指针进行。
<Step 1> 在调用参数表之前，定义一个 va_list 类型的变量，(假设va_list 类型变量被定义为ap)；
<Step 2> 然后应该对ap 进行初始化，让它指向可变参数表里面的第一个参数，这是通过 va_start 来实现的，第一个参数是 ap 本身，第二个参数是在变参表前面紧挨着的一个变量,即“...”之前的那个参数；
<Step 3> 然后是获取参数，调用va_arg，它的第一个参数是ap，第二个参数是要获取的参数的指定类型，然后返回这个指定类型的值，并且把 ap 的位置指向变参表的下一个变量位置；
<Step 4> 获取所有的参数之后，我们有必要将这个 ap 指针关掉，以免发生危险，方法是调用 va_end，他是输入的参数 ap 置为 NULL，应该养成获取完参数表之后关闭指针的习惯。说白了，就是让我们的程序具有健壮性。通常va_start和va_end是成对出现。
*/
//三维 :A[1][2][3]
Status InitArray(Array &A,int dim,...)
{
	if(dim <1 || dim >MAX_ARRAY_DIM) return ERROR;

	A.dim=dim;
	A.bounds =(int *)malloc(dim*sizeof(int));

	if(!A.bounds) exit(OVERFLOW);

	elemtotal=1;
	va_start(ap,dim); //ap...变参列表
	for(i=0;i<dim;i++)
	{
		A.bounds[i]=va_arg(ap,int); //get arg from ap that arg is int type
		if(A.bounds[i]<0) return UNDERFLOW;//下溢出

		elemtotal*=A.bounds[i];
	}

	va_end(ap);

	A.base=(ElemType*)malloc(elemtotal*sizeof(ElemType));

	if(!A.base) exit(OVERFLOW);

	A.constants=(int *)malloc(dim * sizeof(int));

	if(A.constants) exit(OVERFLOW);
	
	A.constants[dim-1]=1;

	for(i=dim-2;i>=0;i--)
	{
		//A[][i][]-->A[][i+1][] 跨越的多少的基本元素
		A.constants[i]=A.bounds[i+1]*A.constants[i+1]; 


	}

	return OK;
}

Status Locate(Array A,va_list ap,int &off)
{
	off=0;

	for(i=0;i<A.dim;i++)
	{
		ind=va_arg(ap,int);

		if(ind 不合法) exit(...)
		off+=ind*A.constants[i];
	}

	return OK
}

//e<-A
Status getValue(Array A,ElemType &,...){

	va_start(ap,e);
	if((result=Locate(A,ap,off))<0) return ERROR;

	e=*(base+off);
	return OK;
}
//e->A
Status setValue(Array &A,ElemType e,...)
{

	va_start(ap,e);
	if((result=Locate(A,ap,off))<0) return ERROR;

	*(base+off)=e;
	return OK;
}

#define MAXSIZE 12500

typedef struct
{
	int i,j;
	ElemType e;
}Triple;

typedef struct{
	Triple data[MAXSIZE+1];//data[0]未用
	int mu,nu,tu; //m*n t个非零元
}TSMatrix;

//以行为主序存储，矩阵转置时预先计算出每个位置
//行--列，列-->行

//统计定位：统计排序，一种统计计算思想
Status FastTransposeSMatrix(TSMatrix M,TSMatrix &T)
{

	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=T.tu;

	int * count = (int*)malloc(sizeof(int)*(M.nu+1));
	//for(...) count[i]=0;
	
	for(i=1;i<=M.mu;i++)
	{
		count[M.data[i].j]++;
	}

	count[0]=1;
	for(i=1;i<=M.nu;i++)
	{
		count[i]+=count[i-1];//向前错了一格 start postion
	}

	for(i=1;i<=M.mu;i++)
	{
			  
		index=count[M.data[i].j-1]++;
		T[index].e=M[i].e;
		T[index].i=M[i].j;
		T[index].j=M[i].i;
	}

}

//矩阵数据结构加入行起始位置，行逻辑链接的顺序表


typedef struct{
	Triple data[MAXSIZE+1];//data[0]未用 
	int rpos[MAXRC+1]; //行链接
	int mu,nu,tu; //m*n t个非零元
}RLSMatrix;


//
Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
{
	if(M.nu!=M.mu) return ERROR;
	//Q.Mu...
	
	int tempMatrix[M.mu][N.nu];
	//for for Init 


	if(M.tu*N.tu!=0)
	{
		for(p=1;p<=M.mu;++p)
		{
			for(q=1;q<=N.mu;++q)
			{
	//
				//M*N (i,k)*(k,j) 找k等的
				if(M.data[p].j == N.data[q].i)
					tempMatrix[M.data[p].i][N.data[q].j]+=M.data[p].e*M.data[q].e;
			}

		}

		//扫描矩阵压缩到Q
	}
}


//-------------------------------------------------------
Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
{
	if(M.nu!=M.mu) return ERROR;
	Q.mu=M.mu;
	Q.nu=N.nu;

	Q.tu=0;

	if(M.tu*N.tu!=0)
	{
		for(arow=1;arow<=Q.mu;++arow)  //计算Q的此行
		{
			ctemp[]=0; //当前行各元素累计器clear 0
			Q.rpos[arow]=Q.tu+1;//行开始位置等于当前元素数下一个

			if(arow<M.mu) tp=M.rpos[arow+1]; //tp M当前行下一行起始位置
			else tp=M.tu+1;

			//用tp做为M界
			for(p=M.rpos[arow];p<tp;++p)
			{
				brow=M.data[p].j;//对应在N中的行

				//M-->N,分析N额all列
				if(brow<N.mu) t=N.rpos[brow+1];
				else t=N.tu+1;

				for(q=N.rpos[brow];q<t;q++)
				{
					ccol=N.data[q].j; //列号
					ctemp[ccol]+=M.data[p].e*N.data[q].e; //存一行
				}
			}

			//压缩存储
			for(ccol=1;ccol<=Q.nu;ccol++)
			{
				if(ctemp[ccol]){
					//算一个地址存一个
					if(++Q.tu > MAXSIZE) return ERROR;
					Q.data[Q.tu]=(arow,ccol,ctemp[ccol]);
				}
			}
		
		}
	}
	return OK;
}
