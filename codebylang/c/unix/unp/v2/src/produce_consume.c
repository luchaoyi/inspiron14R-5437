--单个生产者，单个消费者解决方案--
信号量nempty指示可用的存储空间,nempty=NBUFF
信号量nstore指示已填写的存储空间,nstore=0			
互斥信号量保护存储区的写操作,nmutex=1
buf[NBUFF]

produce(){
	sem_wait(nempty);

	sem_wait(nmutex); //临界区
	in->buf;
	sem_post(nmutex);

	sem_post(nstore);


}

consume(){
	sem_wait(nstore);
	
	sem_wait(nmutex);
	out->buf;
	sem_post(nmutex);

	sem_post(nempty);
}

--更多方案参加unpv2-c10--
--多缓冲区方案--
在多个缓存区之间循环

