#!/usr/bin/env python
# coding:utf-8
'''
#=============================================================================
#     FileName: get_load_test.py
#         Desc: HTTP get 压力测试
#       Author: Daniel
#        Email: daneustc@gmail.com
#     HomePage: http://ustcdane.github.io/
#      Version: 0.0.1
#   LastChange: 2016-01-06 09:57:32
#      History:
#=============================================================================
'''

import time
import urllib
import urllib2
import httplib
import threading
from Queue import Queue
from time import sleep
import sys

import traceback


# 性能测试页面
URLS = [line for line in open("urls", "r")]

# 配置:压力测试
THREAD_NUM = 10            # 并发线程总数
ONE_WORKER_NUM = 5000       # 每个线程的循环次数
LOOP_SLEEP = 0.001      # 每次请求时间间隔(秒)

# 出错数
ERROR_NUM = 0


#具体的处理函数，负责处理单个任务
def doWork(index, url):
    t = threading.currentThread()
    #print "["+t.name+" "+str(index)+"] "+PERF_TEST_URL

    try:
        req = urllib2.Request(url)
        response = urllib2.urlopen(req, timeout=2)
        html = response.read()
        response.close()#关闭连接,防止过度占用服务器链接资源
    except urllib2.URLError, e:
        print "["+t.name+" "+str(index)+"] "
        print e
        global ERROR_NUM
        ERROR_NUM += 1


#具体的处理函数，负责处理单个get任务
def doWork_get(index, url):
    t = threading.currentThread()
    #print "["+t.name+" "+str(index)+"] "+PERF_TEST_URL
    httpClient = None
    try:
		#请求的服务器host，不能带http://开头
                #httpClient.request('GET', '/test?input=like&context=she')
		httpClient = httplib.HTTPConnection(url, timeout=2)
		#params = urllib.urlencode({'input':'like', 'context':'she'})
		#httpClient.request('GET', '/test?' + params)
		params = [urllib.urlencode({'input':'like', 'context':'she'}),
				urllib.urlencode({'input':'love', 'context':'he'}),
				urllib.urlencode({'input':'age', 'context':'my'})]
		httpClient.request('GET', '/test?' + params[index%3])
                #response是HTTPResponse对象
		response = httpClient.getresponse()
		print response.reason
		#print response.status
		print "["+t.name+" "+str(index)+"] ", response.read()
		#print response.read().decode('utf8').encode('gb18030')
    except Exception, e:
        print "["+t.name+" "+str(index)+"] "
        print e
       # traceback.print_exc()
        global ERROR_NUM
        ERROR_NUM += 1
    #finally:#关闭http链接
    if httpClient:
		httpClient.close()

#这个是工作进程，负责不断从队列取数据并处理
def working():
    t = threading.currentThread()
    print "["+t.name+"] Sub Thread Begin"

    i = 0
    while i < ONE_WORKER_NUM:
        i += 1
        doWork_get(i, URLS[i % len(URLS)])
        sleep(LOOP_SLEEP)

    print "["+t.name+"] Sub Thread End"


def main():
    #doWork(0)
    #return
    
    t1 = time.time()

    Threads = []

	# 创建线程
    for i in range(THREAD_NUM):
        t = threading.Thread(target=working, name="T"+str(i))
        t.setDaemon(True)
        Threads.append(t)

    for t in Threads:
        t.start()

    for t in Threads:
        t.join()

    print "main thread end"

    t2 = time.time()
    print "========================================"
    #print "URL:", PERF_TEST_URL
    print u"任务总量:", THREAD_NUM, "*", ONE_WORKER_NUM, "=", THREAD_NUM*ONE_WORKER_NUM
    print u"总耗时(秒):", t2-t1
    print u"每次请求耗时(秒):", (t2-t1) / (THREAD_NUM*ONE_WORKER_NUM)
    print u"每秒承载请求数:", 1 / ((t2-t1) / (THREAD_NUM*ONE_WORKER_NUM))
    print u"错误数量:", ERROR_NUM

if __name__ == "__main__": 
    main()
