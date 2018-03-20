import threading
locka=threading.Lock()
lockb=threading.Lock()
lockc=threading.Lock()

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
