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
    return strTimeProp(start, end, '%Y-%m-%d', prop)

try:
    # пытаемся подключиться к базе данных
    conn = pc.connect(dbname='realtor', user='postgres', password='ralif', host='localhost', port='5433')
except:
    # в случае сбоя подключения будет выведено сообщение в STDOUT
    print('Can`t establish connection to database')

cursor = conn.cursor()

id_owners = cursor.execute("select id from owners")
id_owners = list(cursor.fetchall())

id_clients = cursor.execute('select id from clients')
id_clients = list(cursor.fetchall())

id_employees = cursor.execute('select id from employees')
id_employees = list(cursor.fetchall())

id_immovables = cursor.execute('select id from immovables')
id_immovables = list(cursor.fetchall())

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
streets = [street.replace('\n', '') for street in io.open('streets.txt', encoding='utf-8')] + ['не указано']

districts = [district.replace('\n', '') for district in io.open('districts.txt', encoding='utf-8')] + ['не указано']

deal_descs = ['прошла успешно, обе стороны довольны', 'прошла гладко']

deal_types = ['покупка', 'аренда']
roofs = list(range(0, 45))
while n < 500:
    id_owner = random.choice(id_owners)
    id_client = random.choice(id_clients)
    id_employee = random.choice(id_employees)
    id_immovable = random.choice(id_immovables)
    trans_date = randomDate("2008-1-1", "2023-1-9", random.random())
    trans_amount = random.randrange(1, 5000)
    deal_desc = random.choice(deal_descs)

    type_immovable = random.randrange(1, 7)
    preferences = 'в хорошем состоянии, быстро, возможен торг'
    sql = "INSERT INTO deals (id_client, id_employee, id_immovable, trans_date, trans_amount, deal_desc, id_owner) VALUES (%s, %s, %s, %s, %s, %s, %s);"
    data = (id_client, id_employee, id_immovable, trans_date, trans_amount, deal_desc, id_owner)
    cursor.execute(sql, data)
    id_owners.remove(id_owner)

    n+=1

conn.commit()
cursor.close()  