clear all
clc

%load data
load citys_data.mat

n=size(citys,1);
D=zeros(n,n);

for i=1:n
   for j=i:n
        if i ~= j
            D(i,j) = sqrt(sum((citys(i,:) - citys(j,:)).^2));
            D(j,i)=D(i,j); %warn !!!
        else
            D(i,j) = 1e-4;     %!=0   becuse Eta=1./D
        end
   end   
end


%initialization parameters
m=50;	%A number of ants 31 
alpha=1;%Pheromone important degree
beta=5;
rho=0.1;
Q=1; %Pheromone more convergence faster

Eta=1./D; %1/Dij

Tau=ones(n,n);%Pheromone matrix initialization all 1

Table=zeros(m,n);%route record table

iter = 1;                            
iter_max = 200;  
                    
Route_best = zeros(iter_max,n);  %200*31  Route
  
Length_best = zeros(iter_max,1); %200*1	  length	 
Length_ave = zeros(iter_max,1);  %200*1



while iter<=iter_max
	
	start=zeros(m,1);
	
	%ant start city rand
	for i=1:m
		temp=randperm(n);
		start(i)=temp(1);
	end
	%m*n 
	Table(:,1)=start;
	
	citys_index=1:n;
	
	%every ant
	for i=1:m
		%every city
		for j=2:n
		
				tabu=Table(i,1:(j-1)); %visted
				allow_index=~ismember(citys_index,tabu);% return index is not value
				allow=citys_index(allow_index);%will viste
				
				P=allow;		
				
				% move probability---------------
				
				for k=1:length(allow)
					P(k)=Tau(tabu(end),allow(k))^alpha * Eta(tabu(end),allow(k))^beta;
				end
				P=P/sum(P);
				
				%-------------------------
				Pc=cumsum(P);
				
				target_index=find(Pc>=rand);
				%select only one 
				target = allow(target_index(1));
				
				%i ant -> j city
				Table(i,j)=target;	
		end
	end
	
	%one iteration end
	%caculate length
	
	Length = zeros(m,1);
	
	for i=1:m
		Route=Table(i,:);
		for j=1:(n-1)	
			Length(i) = Length(i) +D(Route(j),Route(j+1));
		end
		%ring
		Length(i) = Length(i) +D(Route(n),Route(1));
	end

	if iter ==1
		[min_Length,min_index]=min(Length);
		Length_best(iter)=min_Length;
		Length_ave(iter)=mean(Length);
		Route_best(iter,:)=Table(min_index,:);
	else
		[min_Length,min_index]=min(Length);
		%compare found min iter-1 gen
		Length_best(iter)=min(Length_best(iter-1),min_Length);
		
		Length_ave(iter)=mean(Length);
		
		if Length_best(iter)==min_Length
			Route_best(iter,:)=Table(min_index,:);
		else
			Route_best(iter,:)=Route_best((iter-1),:);
		end
    end
    
    
		%Pheromone update
		  Delta_Tau = zeros(n,n);
		  
		  for i = 1:m
			  for j = 1:(n - 1)
				  Delta_Tau(Table(i,j),Table(i,j+1)) = Delta_Tau(Table(i,j),Table(i,j+1)) + Q/Length(i);
              end
                  Delta_Tau(Table(i,n),Table(i,1)) = Delta_Tau(Table(i,n),Table(i,1)) + Q/Length(i);
		  end
			  Tau = (1-rho) * Tau + Delta_Tau;

			iter = iter + 1;
			Table = zeros(m,n);
    

end


%% show

[Shortest_Length,index] = min(Length_best);
Shortest_Route = Route_best(index,:);

disp(['min_length:' num2str(Shortest_Length)]);

disp(['best_route:' num2str([Shortest_Route Shortest_Route(1)])]);



%% plot



    figure(1)

    plot([citys(Shortest_Route,1);citys(Shortest_Route(1),1)],[citys(Shortest_Route,2);citys(Shortest_Route(1),2)],'o-');

    grid on

    for i = 1:size(citys,1)

        text(citys(i,1),citys(i,2),['   ' num2str(i)]);

    end

    text(citys(Shortest_Route(1),1),citys(Shortest_Route(1),2),'start');
    text(citys(Shortest_Route(end),1),citys(Shortest_Route(end),2),'end');
    xlabel('x')
    ylabel('y')
	title(' TSP ');
%%
figure(2)
plot(1:iter_max,Length_best,'b',1:iter_max,Length_ave,'r:')
legend('length_min','length_ave');
xlabel('iter')
ylabel('length')





    
