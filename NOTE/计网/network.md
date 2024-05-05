# DHCP
## 数据发送过程
* DHCP客户端-->DHCP服务器 客户端广播DHCP Discover消息--客户端发出发现DHCP服务器
* DHCP客户端<--DHCP服务器 服务器提供地址租约 offer--DHCP服务器告诉客户端可提供IP
* DHCP客户端-->DHCP服务器 客户端选择并请求地址租用 Request--客户端告诉DHCP服务器我需要IP
* DHCP客户端<--DHCP服务器 服务器确认将地址租用给客户端 ACK消息--服务器提供IP