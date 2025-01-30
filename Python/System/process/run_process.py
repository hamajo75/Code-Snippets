import subprocess

from typing import Tuple


def run_cmd(cmd: list) -> Tuple[int, str, str]:
    process_completed = subprocess.run(cmd, capture_output=True, text=True)
    code = process_completed.returncode
    stdout = process_completed.stdout.strip()
    stderr = process_completed.stderr.strip()
    return (code, stdout, stderr)


def start_process(cmd: list) -> subprocess.Popen:
    try:
        process = subprocess.Popen(
            cmd, stdout=subprocess.DEVNULL, stderr=subprocess.STDOUT
        )
        return process
    except subprocess.CalledProcessError as err:
        print(
            "Something went wrong while executing " + str(cmd) + ", Error: " + str(err)
        )
    return None
