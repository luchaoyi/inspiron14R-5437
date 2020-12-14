function y=fun(x)
	y=sin( sqrt(x(1).^2+x(2).^2) )./sqrt(x(1).^2+x(2).^2)+exp((cos(2*pi*x(1))+cos(2*pi*x(2)))/2)-2.71289;
end
