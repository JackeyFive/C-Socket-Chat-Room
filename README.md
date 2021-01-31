# C-Socket-Chat-Room
基于Linux C socket的聊天室

server主线程获取套接字资源监听8000端口，等待client连接。
client获取套接字连接到server。
server和client均创建子线程负责对套接字写出，主线程负责读入。
