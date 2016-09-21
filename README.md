# libev-sample
本例主要演示libevent在socket异步编程中的应用。在一些对性能要求较高的网络应用程序中，为了防止程序阻塞在socket I/O操作上造成程序性能的下降，需要使用异步编程，即程序准备好读写的函数(或接口)并向系统注册，然后在需要的时候只向系统提交读写的请求之后就继续做自己的事情，实际的读写操作由系统在合适的时候调用我们程序注册的接口进行。

服务端编译：gcc -o eventserver eventserver.c -levent
客户端编译：g++ -c tcpclient tcpclient.c
