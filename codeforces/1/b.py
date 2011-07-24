import re
nTests = int(raw_input())

def get_columnt_by_string(s):
    ret = 0
    number_of_words = 26
    for _ in range(1, len(s)):
        ret += number_of_words
        number_of_words *= 26
    return ret + 1 + str_to_int(s)

def get_column_by_int(col):
    nElems = 26
    nLetters = 1
    rem = col
    while rem > nElems:
        rem -= nElems
        nElems *= 26
        nLetters += 1
    return int_to_str(rem - 1, nLetters)

def int_to_str(num, length):
    ret = ''
    while num > 0:
        ret = chr(ord('A') + (num % 26)) + ret
        num /= 26
    if len(ret) < length:
        ret = 'A' * (length - len(ret)) + ret
    return ret

def str_to_int(s):
    ret = 0
    for ch in s:
        ret *= 26
        ret += ord(ch) - ord('A')
    return ret

def first_method(row, col):
    return 'R%dC%d' % (row, col)

def second_method(row, col):
    return '%s%d' % (get_column_by_int(col), row)

for _ in range(nTests):
    line = raw_input()
    if re.match(r'R\d+C\d+', line) is None:
        row = int(re.search(r'\d+', line).group())
        col_string = re.search(r'\D+', line).group()
        col = get_columnt_by_string(col_string)
        print first_method(row, col)
    else:
        empty, row, col = re.split(r'^R|C', line)
        row, col = map(int, (row, col))
        print second_method(row, col)
