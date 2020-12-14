//25Mhz下640*480
//vga显示hsync,vsync
//25Mhz下根据规范计算出640*480图片需要800个像素点周期,一行需要32us
//hsync=sp+bp+hv(显示区域)+FP=96+48+640+16=800 
//一行32us*480行=15.360ms
//根据vga显示规范计算vsync,显示480行需要512行的时间
//vsync=sp+bp+vv+fp=2+29+480+10=512;512*32us=16.672ms f=1/16.672ms=60hz(刷新频率)
//25Mhz对于640*480图片可以保证60hz刷新频率

module vga_640x480(
input wire clk,
input wire clr,
//产生行场同步信号
output reg hsync,
output reg vsync,
output reg[9:0] hc,
output reg[9:0] vc,
//在可显示的640*480区域计算得到当前绘制像素
output reg vidon //在可显示区域vidon==1 
);


parameter hpixels=10'd800;
parameter vlines=10'd512;
parameter  hbp=10'd144  //96+40=144开始显示
parameter  hfp=10'd784  //结束显示
parameter vbp=10'd31   //开始行
parameter vfp=10'd511     //结束行

reg vincrese_flag=0;//行满时vincrese_flag==1,==>vc++


//行计数
always@(posedge clk or posedge rst)
begin
	if(clr==1)
		hc<=0;
	else
	begin
		//>=在软件中与==都是一条指令，而电路设计>=需要更多电路
		if(hc==hpixels-1)
		begin
			hc<=0;
			vincrese_flag<=1;
		end
		else
		begin
			hc<=hc+1;
			vincrese_flag<=0;
		end

	end
end 

//列计数
always@(posedge clk or posedge rst)
begin
	if(clr==1)
		vc<=0;
	else
	begin
		if(vincrese_flag==1)
		begin
			if(vc==vlines-1)
				vc<=0;
			else
				vc<=vc+1;
		end
	end
end 

//行同步信号
always@(*)
	if (hc<96)
		hsync<=0;
	else
		hsync<=1;
always@(*)
	if (vc<2)
		vsync<=0;
	else
		vcsync<=1;

always@(*)
	//加括号产生四个与在与两级级联，不加括号产生5级级联
	if((hc>hbpi)&&(hc<hfp)&&(vc>vbp)&&(vc<vfp))
		vidon<=1;
	else
		vidon<=0;
endmodule
