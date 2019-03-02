#!/usr/bin/env python

import argparse
import json
import subprocess
import sys
import textwrap

try:
    from urllib.parse import urlencode
except ImportError:
    from urllib import urlencode


def valid_style(str):
    str = str.strip()
    formats = ['A', 'P', 'C', 'M', 'N', 'W']

    if str in formats:
        return str
    else:
        msg = 'not a valid style: "{0}"'.format(str)
        raise argparse.ArgumentTypeError(msg)


parser = argparse.ArgumentParser(
    formatter_class=argparse.RawDescriptionHelpFormatter,
    description=textwrap.dedent('''\
    format a title based on 1 of 6 industry standard style guides:

      A: Associated Press Stylebook
      P: Publication Manual of the American Psychological Association
      C: Chicago Manual of Style (default)
      M: MLA Handbook
      N: The New York Times Manual of Style and Usage
      W: Wikipedia Manual of Style
    '''))

parser.add_argument('--style', default='C', type=valid_style,
                    help='choose one: A, P, C (default), M, N or W')

opts = {}
if not sys.stdin.isatty():
    opts = {
        'default': sys.stdin.read().split(),
        'nargs': '?'
    }

parser.add_argument('title', default=opts.get('default', None),
                    metavar='words', type=str, nargs=opts.get('nargs', '+'),
                    help='1 or more words (the title) you want to convert')

args = parser.parse_args()


def trim(title):
    return ' '.join(title).strip()


def squish(title):
    return ' '.join(title.split())


def replace_chars(str):
    str = str.decode('utf-8')

    # Replace "fancy" double and single quotes.
    str = str.replace(u'\u201c', '"')
    str = str.replace(u'\u201d', '"')
    str = str.replace(u'\u2018', "'")
    return str.replace(u'\u2019', "'")


def style_enabled(style):
    return 'true' if args.style == style else 'false'


data = urlencode({
    'title': squish(trim(args.title)),
    'styleA': style_enabled('A'),
    'styleP': style_enabled('P'),
    'styleC': style_enabled('C'),
    'styleM': style_enabled('M'),
    'styleN': style_enabled('N'),
    'styleW': style_enabled('W'),
    'preserveAllCaps': 'true'
})

cmd = ('curl -s -A "tcc" -H "X-Requested-With: XMLHttpRequest" --data "{0}" '
       'https://titlecaseconverter.com/cgi-bin/tcc.pl'.format(data))

body = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True)
body_json = json.loads(body)[0]

result = ''

for key, value in body_json.items():
    if key == 'title':
        for k in value:
            joint = replace_chars(k['joint'].encode('utf-8'))
            word = replace_chars(k['word'].encode('utf-8'))
            result += '{0}{1}'.format(joint, word)

print(result)
