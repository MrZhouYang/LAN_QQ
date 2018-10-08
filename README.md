# LAN_QQ
LAN_QQ instant messaging system mainly uses Qt technology and QtCreator development tool in this article. Interface layout is modeled after Tencent QQ client.
As a kind of C++ GUI application development framework for cross-platform, Qt is very popular in the Linux. 
Qt technology has become increasingly mature, and also got great performance. 
In addition, the system also involves Socket, SQLite, MVC and other related theories and technologies.
The LAN instant messaging system mainly achieved registration, login, friend management, instant messaging, group chat, message management,
mail transfer, file transfer, shared space and so on. After a simple registration, users can log into the system. Users can add friends, 
groups and discussion groups to communicate with other online users. 
What's more, the server and clients will store message records in the files or databases by themselves, so users can manage local records and network records at any time. Of course, file and mail transfer also be realized in this system.
Besides that, Users and groups have their unique shared spaces, users can access friends' spaces, members of the group can access the space of the group, and share files with other users in the space.(The video module has been deleted.)

Please note that this project was developed by QT5. 

本系统主要想实现注册登录、好友管理、即时通信（文本、视频）、群组功能、消息管理、邮件收发、文件收发等功能。
用户通过简单的注册以后，便可以登录系统。随后进行好友、群以及讨论组的添加，就可以与其他在线的用户进行行即时通
信。对于消息记录，服务器以及客户端都会在各自文件或者数据库中进行相应的存储，用户可以随时进行本地消息以及网络消
息的管理。当然文件的收发也得到了很好的实现，并且也集成了简单邮件收发功能。