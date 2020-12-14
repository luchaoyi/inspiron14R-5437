import socket

s=socket.gethostbyname("www.sina.com")
print s
s=socket.getservbyname("https","tcp")
print s
s=socket.getservbyname("https","udp")
print s

print socket.htons(80)
s=socket.getservbyport(80,'tcp')
print s
print socket.getaddrinfo(None, "https")
