clc
clear all
close all
tic
figure(1); hold on;

fishnum = 100;

MAXGEN = 50;
% visual found number;
try_number = 50;
visual=2.5 ;

step=0.3;
delta = 0.618

lb_ub=[-10,10,2];

%start
X=AF_init(fishnum,lb_ub);%init
Xinit=X;
LBUB=[];

for i=1:size(lb_ub,1)
	LBUB=[LBUB;repmat(lb_ub(i,1:2),lb_ub(i,3),1)];
end

gen=1;

BestY=-1*ones(1,MAXGEN);
BestX=-1*ones(2,MAXGEN);

besty=-100;

Y=AF_foodconsistence(X);

while gen<=MAXGEN
	
	for i=1:fishnum
		[Xi1,Yi1] = AF_swarm(X,i,visual,step,delta,try_number,LBUB,Y);
		[Xi2,Yi2] = AF_follow(X,i,visual,step,delta,try_number,LBUB,Y);
		
		if Yi1>Yi2
			X(:,i)=Xi1;
			Y(1,i)=Yi1;
		else
			X(:,i)=Xi2;
			Y(1,i)=Yi2;
		end
	end
	%Y X record one step active
	[Ymax,index]=max(Y);
	

	figure(1);
	%plot all gen max exchange 
	plot(X(1,index),X(2,index),'.','color',[gen/MAXGEN,0,0]);
	
	if Ymax>besty
		%record best solution
		besty=Ymax;
		bestx=X(:,index);
		%
		BestY(gen)=Ymax;
		[BestX(:,gen)]=X(:,index);
	else
		BestY(gen)=BestY(gen-1);
		[BestX(:,gen)]=BestX(:,gen-1);
	end
	gen = gen + 1;
	
end

plot(bestx(1),bestx(2),'ro','MarkerSize',100)

xlabel('x')

ylabel('y')

figure

plot(1:MAXGEN,BestY)

xlabel('gen')

ylabel('f(X)')


disp(['X:',num2str(bestx','%1.5f')])

disp(['Y:',num2str(besty,'%1.5f')])


figure 
plot(Xinit(1,:),Xinit(2,:),'.');


figure
plot(X(1,:),X(2,:),'.');


toc






