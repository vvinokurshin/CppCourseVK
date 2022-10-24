import sys

COLOR_DEFAULT = '\033[0m'
COLOR_RED = '\033[31m'
COLOR_GREEN = '\033[32m'

filename = sys.argv[1]

with open(filename, 'r') as f:
    strings = f.readlines()

test_filename = strings[5].split(' ')[2][:-1]
lines = strings[13].split(' ')
funcs = strings[14].split(' ')
percent_lines, info_lines = float(lines[3][:-1]), ' '.join(lines[4:])[:-1]
percent_funcs, info_funcs = float(funcs[3][:-1]), ' '.join(funcs[4:])[:-1]

msg = ''

if percent_lines < 70:
    msg += f'\nInsufficient coverage of code lines: '
    msg += f'{COLOR_RED}{percent_lines}% of 100% {info_lines}{COLOR_DEFAULT}'

if percent_funcs < 70:
    msg += f'\nInsufficient coverage of functions: '
    msg += f'{COLOR_RED}{percent_funcs}% of 100% {info_funcs}{COLOR_DEFAULT}'

if msg == '':
    print(f'\nСhecking the coverage {test_filename}: {COLOR_GREEN}PASSED{COLOR_DEFAULT}')
    exit(0)

print(f'\nСhecking the coverage {test_filename}: {COLOR_RED}FAILED{COLOR_DEFAULT}' + msg)
exit(1)