import requests
import argparse
import os
import re
import time


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--PHPSESSID", type=str,
                        default='nsvu4ufvhkfjv56r3h1jj786h4')
    parser.add_argument("--dir", type=str, default=".")
    return parser.parse_args()


def get_from_submit(problem, PHPSESSID):
    problem = str(problem)
    url = 'http://47.99.179.148/problem.php?id='+problem
    # print(url)
    r = requests.get(url, cookies={'PHPSESSID': PHPSESSID})
    search = re.search(
        '<input type=hidden name=from_submit value=([0-9]{1,4})>', r.text)
    if search:
        return search.group(1)
    else:
        print(r.text)
        raise Exception('No from_submit found on ' + url)


def submit(problem, code, PHPSESSID, from_submit):  # problem: dddd
    problem = str(problem)
    url = 'http://47.99.179.148/submit.php?id='+problem
    data = {'lanselect': '0', 'submit': 'Submit',
            'source_code': code, 'from_submit': from_submit}
    # print(data)
    r = requests.post(url, data, cookies={'PHPSESSID': PHPSESSID})
    print(r.text)


if __name__ == '__main__':
    # Get arguments
    args = parse_args()


    while 1:
        try:
            f = open(os.path.join(args.dir, 'P1044_sub.cpp'), mode='r')
            s = ''  # init a list
            for ii in f:  # read each line of file
                s += (ii)
            from_submit = get_from_submit(1044, args.PHPSESSID)
            submit(1044, s, args.PHPSESSID, from_submit)
        except:
            pass

        print('Submitted at '+time.strftime("%H:%M:%S", time.localtime()))
        time.sleep(15)
        # break
