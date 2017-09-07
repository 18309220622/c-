#!/bin/bash
set -u
ping_fun()
{
    d_network=192.168.1
    echo -n "input the network(default $d_network):"
    read network
    : ${network:=$d_network}
    echo "network:$network"
    d_hostip_beg=1
    d_hostip_end=254
    echo -n "input the hostip(default $d_hostip_beg $d_hostip_end):"
    read hostip_beg hostip_end
    : ${hostip_beg:=$d_hostip_beg}
    : ${hostip_end:=$d_hostip_end}
    echo "hostip_beg:$hostip_beg"
    echo "hostip_end:$hostip_end"
    count=3
    for ((hostip=$hostip_beg;hostip<=$hostip_end;hostip++));do
        host=$network.$hostip
        echo "开始ping检测$host"
        ping -c $count $host &>/dev/null
        if [ $? = 0  ];then
            echo "$host is up"
        else
            sleep 3
            ping -c $count $host &>/dev/null
            if [ $? = 0  ];then
                echo "$host is up"
            else
                echo "$host is down"
            fi
        fi
    done
    #echo "执行完毕"
    exit 0

}
main()
{
    echo "----开始执行ping程序----"
    ping_fun

}
main
exit 0




















#function auto_login_ssh()
#{
#    #设置为永不超时
#    #spawn的功能是给ssh运行进程加个壳，用来传递交互指令的
#    #expect "password:"是判断上次输出结果里是否包含“password:”的字符串，如果有则立即返回，否则就一直等待
#    #interact表示执行完成后把控制权交给控制台，保持交互状态
#    
#    　　
#    expect -c "set timeout -1;   
#            spawn -noecho ssh -o StrictHostKeyCheck=no $2 ${@:3};
#            expect "password:";
#            send -- $1r;
#            interact;";
#}
#auto_login_ssh password user@host
#StrictHostKeyCheck=no
