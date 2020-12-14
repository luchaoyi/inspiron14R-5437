//RLE压缩 ，[长度][data]
//假设字节:以长度最高位为标志为 1 则表示重复数据 length>=128 则length=length-128 or length=length&0x80 
//后面是length个重复data 若length<128,则表示length个不重复data.
//127是能表示最大length超过则重新计数
//另一种编码方式,对于重复字段使用高两位为一作标志，不重复不做标志，与data数据冲突采用字符填充
//如果data恰好是高两位为一则填充0xc1
int Rle_encode(char* inbuf,int inSize,char* outbuf,int outSize)
{

	char *incur=inbuf;
	char *outcur=outbuf;
	while(incur<inbuf+inSize)
	{
		
		char length=0;dd
		//下一个和当前相同则生成重复长度
		if(*incur==*(incur+1))
		{
			length=getLength(incur,1);
			*outcur++=length|0x80; //最高位置1 
			*outcur++=*incur;
			*incur+=length;//移动incur
		}
		//不相同，不重复长度
		else
		{
			length=getLength(incur,0);
			*outcur++=length;
			for(int i=1;i<=length;i++)
			{
				*outcur++=*incur++;
			}
		}
	}
}

int getLength(char *cur,bool repflag)
{
	int length=1;
	if(repflag==1)
	{
		for(;*cur==*(cur+1)&&length<127;length++,cur++);
	}
	else
	{

		for(;*cur!=*(cur+1)&&length<127;length++,cur++);
	}
	return length;
}
