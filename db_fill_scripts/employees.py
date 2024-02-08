import psycopg2 as pc
import itertools
from psycopg2.extras import Json
import random
import time
import io 

def strTimeProp(start, end, format, prop):
    """Get a time at a proportion of a range of two formatted times.

    start and end should be strings specifying times formated in the
    given format (strftime-style), giving an interval [start, end].
    prop specifies how a proportion of the interval to be taken after
    start.  The returned time will be in the specified format.
    """

    stime = time.mktime(time.strptime(start, format))
    etime = time.mktime(time.strptime(end, format))

    ptime = stime + prop * (etime - stime)

    return time.strftime(format, time.localtime(ptime))


def randomDate(start, end, prop):
    return strTimeProp(start, end, '%m/%d/%Y', prop)

try:
    # пытаемся подключиться к базе данных
    conn = pc.connect(dbname='realtor', user='postgres', password='ralif', host='localhost', port='5433')
except:
    # в случае сбоя подключения будет выведено сообщение в STDOUT
    print('Can`t establish connection to database')

cursor = conn.cursor()

alphabet="АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЭЮЯ"
nums="0123456789"
alph="abcdefghijklmnopuvwxyz"
a = itertools.cycle(itertools.combinations_with_replacement(alphabet, 3))
nn = itertools.cycle(itertools.combinations_with_replacement(nums, 9))
alph=itertools.cycle(itertools.combinations_with_replacement(alph, 4))

ser = itertools.cycle(itertools.combinations_with_replacement(nums, 4))
num = itertools.cycle(itertools.combinations_with_replacement(nums, 6))
n = 0

#with open('streets.txt') as f:
#    f
streets = (street.replace('\n', '') for street in io.open('streets.txt', encoding='utf-8'))
streets = itertools.cycle(streets)

districts = (district.replace('\n', '') for district in io.open('districts.txt', encoding='utf-8'))
districts = itertools.cycle(districts)

jobs = ['accountant', 'manager', 'realtor', 'cleaner', 'operator', 'courier', 'trainee']

while n < 60:
    name = '{} {}'.format(''.join(next(a)), ''.join(next(a)))
    phone = '7'.join(next(nn))
    mail = ''.join(next(alph)) + '@'.join(next(alph))
    job = random.choice(jobs)
    passport = Json({'series' : ''.join(next(ser)), 'num' : ''.join(next(num)), 'date' : randomDate("1/1/2008", "9/1/2023", random.random())})
    cursor.execute("INSERT INTO employees (full_name, job, phone_number, e_mail, passport_data) VALUES (%s, %s, %s, %s, %s)", (name, job, phone, mail, passport))

    n+=1

conn.commit()
cursor.close()  