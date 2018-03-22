#_*_coding:utf-8_*_
import threading
locka=threading.Lock() # 同步锁a
lockb=threading.Lock() # 同步锁a
lockc=threading.Lock() # 同步锁a

# .acquire() 请求锁 等待这个锁 请求成功后才能继续向下运行 
# .release() 释放锁 被释放之后才能被请求

def printa():
    for _ in range(10):
        lockc.acquire()
        print('A',end = '')
        locka.release()

def printb():
    for _ in range(10):
        locka.acquire()
        print('B',end = '')
        lockb.release()

def printc():
    for _ in range(10):
        lockb.acquire()
        print('C',end = '')
        lockc.release()

def run():
    locka.acquire()
    lockb.acquire()
    tc = threading.Thread(target=printc)
    tb = threading.Thread(target=printb)
    ta = threading.Thread(target=printa)
    ta.start()
    tb.start()
    tc.start()

if __name__ == '__main__':
    run()
