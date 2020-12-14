//后缀表达式符号按先后顺运算
//中缀转后缀时需将优先级高的先输出
//利用栈记忆运算符然后将优先级高的优先输出

//因此在运算符优先级由高变低时因将栈中优先级高的运算符都出栈保证优先级高的先运算

//栈FILO所以在优先级低的运算符入栈前因将高优先级输出

/*

*/
int main()
{
    sqStack s;
    char c, e;

    InitStack( &s );

    printf("请输入中缀表达式，以#作为结束标志：");
    scanf("%c", &c);

    while( c != '#' )
    {
        while( c>='0' && c<='9' )
        {
            printf("%c", c);
            scanf("%c", &c);
            if( c<'0' || c>'9' )
            {
                printf(" ");
            }
        }

        if( ')' == c )
        {
            Pop(&s, &e);
            while( '(' != e )
            {
                printf("%c ", e);
                Pop(&s, &e);
            }
        }
        
        else if( '+'==c || '-'==c )
        {
            if( !StackLen(s) )
            {
                Push(&s, c);
            }
            else
            {
                do
                {
                    Pop(&s, &e);//出栈顶
                    if( '(' == e )
                    {
                        Push(&s, e);
                    }
                    else//当为+-*/时出栈*/优先级变化所以出栈先运算
                    //+-无所谓交换率或者说先入栈的+-先运算一起出来吧
                    {
                        printf("%c ", e);
                    }
                }while( StackLen(s) && '('!=e );
                Push(&s, c);
            }
        }
        else if( '*'==c || '/'==c || '('==c )
        {
            Push(&s, c);
        }
        else if( '#'== c )
        {
            break;
        }
        else
        {
            printf("\n出错：输入格式错误！\n");
            return -1;
        }

        scanf("%c", &c);
    }

    while( StackLen(s) )
    {
        Pop(&s, &e);
        printf("%c ", e);
    }

    return 0;
}
