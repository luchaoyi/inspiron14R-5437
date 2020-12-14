clc;
clear;
close all;

%%
tic
T0=1000;   % init T
Tend=1e-3;  % end T
L=500;     %Chain length
q=0.9;    %The cooling rate
%%


load CityPosition1;
D=Distanse(X);

N=size(D,1);
S1=randperm(N);%init Route;

%DrawPath(S1,X)
%pause(0.0001)

%disp('rand initialization:')
%OutputPath(S1);
%Rlength=PathLength(D,S1);
%disp(['length',num2str(Rlength)]);


%cooling

count=0; %The iteration counter


Time=ceil(double(solve(['1000*(0.9)^x=',num2str(Tend)])));
track=zeros(Time,N);
Obj=zeros(Time,1);

while T0>Tend
   
	count = count+1;

	for k=1:L 
		S2=NewAnswer(S1);
		%under the same temperature
		[S1,R] = Metropolis(S1,S2,D,T0);
		temp(k,:)=[S1,R]; %[S1,R] 1:end-1 is S1,end is R
    end
    
	[d0,index] = min(temp(:,end)); 
	
	%if better  Record else hold
	if count==1||d0<Obj(count-1)
		Obj(count)=d0;
	else
		Obj(count)=Obj(count-1);
	end

	track(count,:)=temp(index,1:end-1);
	
	T0=T0*q;%cooling
	
	%fprintf(1,'%d\n',count);
end


%% plot
figure
plot(1:count,Obj);
xlabel('X');
ylabel('Length');
DrawPath(track(end,:),X);

%show
S=track(end,:);
p=OutputPath(S);
disp(['Length',num2str(PathLength(D,S))]);
disp('-------------------------------------------------------------');
toc