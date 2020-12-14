


void move(int n,char x,char y,char z)
{
    if(1 == n)
    {
        printf("%c->%c\n",x,z);
    }
    else{
        move(n-1, x, z, y);				// 将 n-1 个盘子从 x 借助 z 移到 y 上
		printf("%c->%c\n", x, z);		// 将 第 n 个盘子从 x 移到 z 上
		move(n-1, y, x, z);				// 将 n-1 个盘子从 y 借助 x 移到 z 上

    }

}

int main()
{
    int n ;
    scanf("%d",&n);

    move(n,'x','y','z');
}
