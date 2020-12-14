package pool

//使用有缓冲的通道实现资源池,来管理可以在任意数量的goroutine之间共享及独立使用的资源.种模式在需要共享一组静态资源的情况(如共享数据库连接或者内存缓冲区)下非 常有用。如果goroutine需要从池里得到这些资源中的一个,它可以从池里申请,使用完后归还到资源池里

import (
"errors"
"log"
"io"
"sync"
)

// Pool 管理一组可以安全地在多个 goroutine 间
// 共享的资源。被管理的资源必须实现 io.Closer 接口

type Pool struct {
	m sync.Mutex
	resources chan io.Closer  //chan中放资源
	factory func()(io.Closer,error) //生成资源
	closed bool
}


var ErrPoolClosed = errors.New("Pool has been closed")

func New(fn func()(io.Closer,error),size uint) (*Pool,error){
	if size<=0{
		return nil,errors.New("Size value too small.")
	}

	return &Pool{
		factory:fn,
		resources:make(chan io.Closer,size),//有缓冲区的chan中放着资源
	},nil
}

func (p *Pool) Acquire() (io.Closer,error){
	select{
	//取资源
	case r,ok:=<-p.resources:
		log.Println("Acquire:","Shared Resource")
		if !ok{
		return nil,ErrPoolClosed}
		return r,nil

	//没有资源,生成新的
	default:
		log.Println("Acquire:","New Resource")
		return p.factory()
	}
}


func (p *Pool) Release(r io.Closer){
	p.m.Lock()
	defer p.m.Unlock()

	//如果pool已经关闭则销毁这个资源
	if p.closed{
		r.Close()
		return 
	}
	select{
		//将资源尝试加入队列
	case p.resources<-r:
		log.Println("Release:","In Queue")
	default:
		log.Println("Release:","Closing")
		r.Close()
	}
}


func(p *Pool) Close(){
	p.m.Lock()
	defer p.m.Unlock()

	if p.closed{
		return 
	}
	p.closed=true

	//先关闭chan防止死锁
	close(p.resources)
	for r:=range p.resources{
		r.Close()
	}
}
