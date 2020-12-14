#awk默认变量都为0.不定义直接用
#模式 动作
{
	#NR代表当前行，每行匹配一次模式，被匹配多少次，执行多少次
	#NF代表当前行字段数
for (i=1;i<NF;i++)
	{
		n++
		sum=sum + $i
	}
	
}

END {
	print "SUM:" ,sum 
	print "NUM:" ,n
	print "AVG:" sum/n
}

