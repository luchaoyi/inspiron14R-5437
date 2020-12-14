//work 包的目的是展示如何使用无缓冲的通道来创建一个 goroutine 池
// work 包管理一个 goroutine 池来完成工作

package work 

import "sync"

type Worker interface {
	Task()
}






type Pool struct {
	work chan Worker
	wg sync.WaitGroup
}


func New(maxGoroutines int) *Pool{
	p:=Pool{
		work:make(chan Worker),
	}
	p.wg.Add(maxGoroutines)
	for i:=0;i<maxGoroutines;i++{
		go func(){
			//无缓冲每次一个任务被一个Goroutine执行
		for w:=range p.work{
			w.Task()
		}
		p.wg.Done()
	}()

	}
	return &p
}


//Run 提交到工作池
func (p *Pool) Run(w Worker){
	p.work<-w
}

func (p *Pool) Shutdown(){
	close(p.work)
	p.wg.Wait()
}
