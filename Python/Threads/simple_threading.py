from threading import Thread
from time import sleep

def MyThreadedFun():
  while True:
    print("thread fun")
    sleep(1)

if __name__ == '__main__':
  my_thread = Thread(target=MyThreadedFun)
  #my_thread.setDaemon(True) # application will wait for the thread to finish
  my_thread.start()
  print("juhu")