#include<stdio.h>
#include<math.h>

//gcc -shared -o check_prime.so -fPIC check_prime.c

int check_prime(int a)
{
	int c;
	for(c=2;c<=sqrt(a);c++)
	{
		if(a%c==0)
			return 0;
	}
	return 1;
}

//python ctypes:int ,string,c_float(c),c_double(d),c_char(e)
void type_demo(int a,char *b,float c,double d,char e){
	printf("%d,%s,%f,%f,%c\n",a,b,c,d,e);
}
