#!/usr/bin/env python3

import subprocess

def monitor_process():
    p = subprocess.Popen('yes', stdout=subprocess.PIPE)

    try:
        while True:
            line = p.stdout.readline()
            print(line.strip())

    except KeyboardInterrupt:
        print("Stopping process...")
        process.terminate()


if __name__ == "__main__":
    monitor_process()
