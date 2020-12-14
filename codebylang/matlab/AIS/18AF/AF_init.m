function X=AF_init(Nfish,lb_ub)

%Nfish number of fish
%lb_ub [lb1,ub1,number1;]; example : x1,x2->[lb1,ub1] number =2
%lb_ub Contain Solution of the dimension
%there Solution is a Column vector
X=[];
row=size(lb_ub);

	for i=1:row
		lb=lb_ub(i,1);
		ub=lb_ub(i,2);
		nr=lb_ub(i,3);
		
		for j=1:nr
			X(end+1,:)=lb+(ub-lb)*rand(1,Nfish);
		end
	end
end