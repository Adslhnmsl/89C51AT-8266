import socket
import pymysql
import time
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind(('10.2.64.172',55555))#������Ϊ�ӿڵĶ˿ں�
print("������")
sqlconnect=pymysql.connect(host='',user='',password='',db='')#�������ݿ�����
server.listen(5)
conn,addr=server.accept()
while True:
    print("���ӳɹ�")
    while True:
        data = conn.recv(512)
        print("���ݣ�",data.decode('ASCII'))
        data = str(data)#�����ܵ������ݷ���
        people = str(data[2:4])
        up = str(data[4:6])
        down = str(data[6:8])
        No = str(data[8:10])
        station = str(data[10:12])
        print(people,up,down,No,station)
        cursor = sqlconnect.cursor()
        sql="INSERT INTO shuamatongde(people,up,down,No,station,day,time) VALUES("+people+","+up+","+down+","+No+","+station+","+time.strftime("%Y%m%d", time.localtime())+","+time.strftime("%H%M", time.localtime())+");"
        #����Ҫ���͵�����д��SQL���
        cursor.execute(sql)
        sqlconnect.commit()#��SQL��䷢��
        
        cursor.execute
