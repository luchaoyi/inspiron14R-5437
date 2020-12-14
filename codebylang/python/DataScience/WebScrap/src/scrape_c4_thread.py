#coding:utf8

import time 
import threading
import download from Downloader
SLEEP_TIME=1

def threaded_crawler(...,max_threads=10):
    crawl_queue=[seed_url]
    seen=set([seed_url])

    D=Downloader(...) #下载页面

    def process_queue():
        while True:
            try:
                url=crawl_queue.pop()
            except IndexError:
                break
            else:
                html=D(url)
                ...

    threads=[]
    while threads or crawl_queue:
        for thread in threads:
            if not thread.is_alive():
                threads.remove(thread)

        while len(threads)<max_threads and crawl_queue:

            thread=threading.Thread(target=process_queue) #创建线程,执行任务process_queue
            thread.setDaemon(True)
            thread.start() #启动

            threads.append(thread)
            time.sleep(SLEEP_TIME)


