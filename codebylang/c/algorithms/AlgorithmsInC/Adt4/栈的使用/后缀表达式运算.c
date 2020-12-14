#include<ctype.h>
int main()
{
	for(i=0;i<N;i++)
	{
		if(isdigit(a[i]))//数字ASCII 48-57 A:65 a:97
		{
			push(a[i]-48);
		}
		else
		{
			switch (a[i]):
			case "+":	push(pop()+pop());break;
			case "*":	push(pop()*pop());break;
			case "-":
			case "/": //除法判断
			//...//
		}
	
	}
}
