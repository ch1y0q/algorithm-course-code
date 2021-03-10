import requests
import argparse
import os
import re
import time
from rich.progress import track

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--PHPSESSID", type=str,
                        default='3is46un7amsftvguicchapbu5o')
    parser.add_argument("--dir", type=str, default=".")
    return parser.parse_args()


def get_from_submit(problem, PHPSESSID):
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
    url = 'http://47.99.179.148/submit.php?id='+problem
    data = {'lanselect': '0', 'submit': 'Submit',
            'source_code': code, 'from_submit': from_submit}
    # print(data)
    r = requests.post(url, data, cookies={'PHPSESSID': PHPSESSID})
    # print(r)


if __name__ == '__main__':
    # Get arguments
    args = parse_args()

    g = os.walk(args.dir)
    for path, dir_list, file_list in g:
        for file_name in track(file_list):
            if re.match('P[0-9]{4}.cpp', file_name):
                f = open(os.path.join(path, file_name), mode='r')
                s = ''  # init a list
                for ii in f:  # read each line of file
                    s += (ii)
                from_submit = get_from_submit(file_name[1:-4], args.PHPSESSID)
                submit(file_name[1:-4], s, args.PHPSESSID, from_submit)
                time.sleep(5)
                # break
