%sym syms 定义符号变量或表达式
>> syms a x
%含有符号变量运算得到符号类型
>> f=sin(a*x)
f =
sin(a*x)
%对x求导
>> dfx=diff(f,x)
dfx =
a*cos(a*x)
>> dfa=diff(f,a)
dfa =
x*cos(a*x)
%subs赋值给符号变量
>>subs(f,[a,x],[1/2,pi])
sin0_5pi =

     1
