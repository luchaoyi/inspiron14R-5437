function f(x,y,varargin)
%f(1,2,3,4,5)
%x=1,y=2
%除了x，y剩余的参数被打包到了varargin中
%but nargin=5
	nargin
	varargin
end
