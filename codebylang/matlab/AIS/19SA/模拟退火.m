
退火过程：
1） 加温。增强热运动 <--> T=T0
2） 等温。平衡状态  <--> Metropolis抽样过程
3） 冷却。热运动减弱，系统能量下降 <-->控制参数下降 T=q*T q->[0,1]

能量就是目标函数，最优解即能量最小时
Metropolis准则以一定概率接受恶化解跳出局部最优




tic

%温度
T0 = 1000;
Tend= 1e-3;
q=0.9;

L=200;


count=0;

while T0>Tend
	
	count=count+1;%迭代计数

	%等温过程
	for k=1:L

		S2=NewAnswer(S1); %随机扰动产生新解
		%% Metropolis准则判断是否接受新解

		%路线和长度
		[S1,R] = Metropolis(S1,S2,D,T0);

		%记录所有产生且被接受的新解
		temp(k,:)=[S1,R];

	end 

	[d0,index] = min(temp(:,end));
	...
	%记录最优值

	%-------------------------------
	T0=q*T0;%降温
end

toc





function [S,R]=Metropolis(S1,S2,D,T)
%{
	df=f(S2) - f(S1)

	df < 0 更优 接受概率 ==1
	否则
		P=exp(-df/T)


%}


...

...

dC= R1-R2;

if dC<0
	S=S2;
	R=R2;
	%温度越高越活跃，接受概率越大
elseif exp(-dC/T) >=rand
	S=S2;
	R=R2;
else
	S=S1;
	R=R1;
end














