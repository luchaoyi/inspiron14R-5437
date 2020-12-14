#!coding:utf8
#easygui包含了一些控件，使用后结束自身消息循环，并返回消息.
#easygui每一个控件本质上都是一个定义完整的窗口程序，包含设计好的事件响应，
#用户使用控件，得到的是控件事件循环结束后返回的信息。
import easygui as g
def create():
    "创建一个新账户，并记录到字典user内"
    name = g.enterbox(msg='请输入用户名：',default='')
    while 1:
        global user
        if name in user:
            name = g.enterbox(msg='此用户名已存在，请重新输入：',default='')
        else:
            break
    key = g.passwordbox(msg='请输入用户密码：',default='')
    user[name] = key
    g.msgbox('注册成功！')
    return

def log_in():
    "登陆账户，需要输入账户名及密码"
    name = g.enterbox(msg='请输入用户名：',default='')
    while 1:
        if user.get(name):
            break
        elif name == '':
            break
        else:          
            name = g.enterbox(msg='您输入的用户名不存在，请重新输入:',default='')
    if name == '':
        return
    key = g.passwordbox(msg='请输入用户密码：',default='')
    while 1:
        if user[name] == key:
            g.msgbox('欢迎进入系统，请点击OK键返回主菜单')
            break
        elif key == '':
            break
        else:
            key = g.enterbox(msg='您输入用户密码不正确，请重新输入:',default='')
    return


user = {}
while 1:
    command = g.buttonbox(msg='请选择',title='',choices=('新建用户','登录账号','退出程序'))
    if command == '新建用户':
        create()
    elif command == '登录账号':
        log_in()
    elif command == '退出程序':
        break
