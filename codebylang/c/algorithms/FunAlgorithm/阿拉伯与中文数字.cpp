//阿拉伯-->中文数字零,  以10000为小节
//1.小节结尾0不用零;2.小节内两个非0数字使用一个零;3.小节千位是0,本小节前一小节(高位)没有数字则不用0,否则用0


const char *chnNumChar[CHN_NUM_CHAR_COUNT]={"零","一"，"二",...,"九"};
const char *chnUnitSection[]={"万","亿"，"万亿"};
const char *chnUnitChar[] = {"","十"，"百"，"千"};

void NumberToChines(int num,String chnStr)
{
	int sectionnumber=0; //存储没一个小节的数字
	String sectionchnstr=null;
	bool needzero=false; 
	int unitPos=0
		
	while(num>0)
	{
		//四位一处理 0-9999
		//1234 8765 3446 0435
		sectionnumber=num%10000;
		if(needzero)
		{
			//进入下一节处理前添加一个0
			chnStr.insert(0,chnNumChar[0]);
		}

		//处理小节
		SectionToChinese(sectionnumber,sectionchnstr);
		//加权位
		sectionchnstr+=(sectionnumber!=0?chnUnitSection[unitPos]:chnUnitSection[0]);
		//0-999千位0,则进入下一小节前补0
		
		chnStr.insert(0,sectionchnstr);
		needzero=(sectionnumber<1000&&sectionnumber>1);
		num=num/10000;
		unitPos++;
	}
}


void SectionToChinese(sectionnumber,sectionchnstr)
{
	int unitPos=0;
	int v;


	//20001000;两千万一千
	while(sectionnumber>0)
	{
		bool zero=true;
		v=sectionnumber%10
		//自己的实现
		if(v==0)
		{
			//初始==1末尾不补0
			//上次没补0,避免连续补0
			if(zero==false)
			{
				zero=true;
				sectionchnstr.insert(0,chnNumChar[0]);
			}

		}
		else
		{
			zero=false;

			//几十？几百？先权位
			sectionchnstr.insert(0,chnUnitChar[unitPos]);
			sectionchnstr.insert(0,chnNumChar[v]);
		}


		
		sectionnumber/=10;
		unitPos++;
	}
}

//中文-->阿拉伯，识别权位。十，百，千非节权位递进*10;遇到万，亿节权位，需处理一下,等节结束时，乘以节倍数,零不处理
//九千一百万 9100*10000 (9*1000+1*100)*10000 


