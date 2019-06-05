import socket
import pymysql
import time
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind(('10.2.64.172',55555))#设置作为接口的端口号
print("连接中")
sqlconnect=pymysql.connect(host='',user='',password='',db='')#设置数据库连接
server.listen(5)
conn,addr=server.accept()
while True:
    print("连接成功")
    while True:
        data = conn.recv(512)
        print("数据：",data.decode('ASCII'))
        data = str(data)#将接受到的数据分离
        people = str(data[2:4])
        up = str(data[4:6])
        down = str(data[6:8])
        No = str(data[8:10])
        station = str(data[10:12])
        print(people,up,down,No,station)
        cursor = sqlconnect.cursor()
        sql="INSERT INTO shuamatongde(people,up,down,No,station,day,time) VALUES("+people+","+up+","+down+","+No+","+station+","+time.strftime("%Y%m%d", time.localtime())+","+time.strftime("%H%M", time.localtime())+");"
        #将想要发送的数据写成SQL语句
        cursor.execute(sql)
        sqlconnect.commit()#将SQL语句发送
        
        cursor.execute
