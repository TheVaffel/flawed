#!/usr/bin/python

import sys
import subprocess
from termcolor import colored

files = sys.argv[1:]

if len(files) == 0:
    print('[flawed_run_tests.py] Need to specify at least one test file to run')
    exit(-1);


failed = []
for test in files:
    try:
        res = subprocess.run([test])
    except subprocess.CalledProcessError as e:
        failed.append(test)

    if res.returncode != 0:
        failed.append(test)
    print('')

flawed_prefix = colored('[flawed] ', 'blue')

if len(failed) == 0:
    success_txt = colored('All ' + str(len(files)) + ' test suites succeeded!', 'green')
    print(flawed_prefix + success_txt)
    exit(0)
else:
    su = 'file'
    if len(failed) != 1:
        su += 's'

    fail_txt = colored(str(len(failed)) + ' test ' + su + ' failed:', 'red')
    print(flawed_prefix + fail_txt)
    for fail in failed:
        fail = fail.split('/')[-1]
        ff = colored('\t' + fail, 'blue')
        print(flawed_prefix + ff)

    exit(1)
