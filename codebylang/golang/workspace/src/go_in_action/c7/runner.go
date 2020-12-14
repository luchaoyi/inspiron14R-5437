package runner

import (
	"errors"
	"os"
	"os/signal"
	"time"
)

//在给定时间内执行一组任务，时间到则结束任务，不管一组任务是否执行完
//操作系统发送中断信号时结束任务

type Runner struct{
	interrupt chan os.Signal
	complete chan error
	timeout <-chan time.Time  //只接受信号的chan

	tasks []func(int) //一组任务函数
}


var ErrTimeout = errors.New("received timeout")
var ErrInterrupt = errors.New("received interrupt")


func New(d time.Duration) *Runner{
	return &Runner{
		interrupt:make(chan os.Signal,1),
		complete: make (chan error),
		timeout:time.After(d),
	}
}

//为Runner添加任务
//func(int) int为任务ID
func (r *Runner) Add(tasks ...func(int)){
	r.tasks = append(r.tasks,tasks...)
}


func (r *Runner) Start() error{

	signal.Notify(r.interrupt,os.Interrupt) //将所有os.Interrupt通知给r.interrupt 
	
	//在另一个goroutine执行r.run()
	go func(){
		r.complete <- r.run()
	}()

	//监听chan，成功完成或超时
	select {
	case err:=<-r.complete:
		return err 
	case <-r.timeout:
		return ErrTimeout
	}
}

func (r *Runner) run() error {
	for id,task :=range r.tasks{
		
		//检测中断
		if r.gotInterrupt(){
			return ErrInterrupt
		}

		//执行任务
		task(id)
	}
	return nil
}


func (r *Runner) gotInterrupt() bool {
	select{
	case <-r.interrupt:
		signal.Stop(r.interrupt) // 停止接收后续的任何信号
		return true
	default:
		return false
	}
}

