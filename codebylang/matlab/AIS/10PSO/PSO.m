clc
clear

load data

% P 
% C
% R

%--------------------------------------
%% 初始参数
objnum=size(P,1); %类中物品个数
Dim=5;
xSize=50;

x=rand(xSize,Dim);
x=ceil(x*objnum);

v=zeros(xSize,Dim);


%初始化

gbest=x(1,:); %粒子群最优位置

xbest=x; %每一个粒子个体最优解


%--------------------------------------
% fitness
for i=1:xSize
	for j=1:Dim
		px(i)=px(i)+P(x(i,j),j); %价值
		rx(i)=rx(i)+R(x(i,j),j); %体积
		cx(i)=cx(i)+C(x(i,j),j); %质量
	end
end

%--------------------------------------
pxbest=px; rxbest=rx; cxbest=cx;



%--------------------------------------
%群体最优来自非劣解 随机选择一个
index=randi(size(fljx,1)1,1); %1*1
gbest=fljx(index,:);

%-------------------------------------- 



%更新种群
for i=1:xSize
	v(i,:) = w*v(i,:) + c1*rand*(xbest(i,:)-x(i,:))+c2*rand*(gbest-x(i,:));
	x(i,:) = x(i,:)+v(i,:);

	%修正避免越界

	x(i,:) = rem(x(i,:),objnum) / double(objnum);

	index1 = find(x(i,:)<=0)
	
	if length(index1) ~=0
		x(i,index1) = rand(size(index1));
	end

	x(i,:)=ceil(4*x(i,:));

end

%--------------------------------------
%更新个体粒子 

for i=1:xSize
	%比较最优值处于支配地位的为当前最优
end

%--------------------------------------
%非劣解筛选

%新一代粒子非劣解
%旧非劣解
%合并
%剔除因合并而不满足的粒子
%即对合并后的非劣解筛选







