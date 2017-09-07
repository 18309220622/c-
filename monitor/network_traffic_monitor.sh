#!/bin/bash

PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin:/usr/local/sbin;
export PATH

#流量监控
function traffic_monitor {
# 系统版本
OS_NAME=$(cat /etc/issue | grep "release")

# 网口名称
eth=$1
#判断网卡存在与否,不存在则退出，可在目录/sys/class/net下查看有三个网口：eth0,lo,pan0
if [ ! -d /sys/class/net/$eth  ];then
    echo -e "\E[35m" 'Network-Interface Not Found' $(tput sgr0)
    NetInterface=`ls /sys/class/net`
    echo -ne 'You system have network-interface:' 
    echo -e "\E[1;35m" ${NetInterface} $(tput sgr0)
    exit 5
fi

while [ : ] 
do
    #初始状态
    STATUS="normal"
    # 获取当前时刻网口接收与发送的流量
    ReceiveCur=$(cat /proc/net/dev | grep $eth | awk '{print $2}')    #获取到Receive字段中的bytes
    TransmitCur=$(cat /proc/net/dev | grep $eth | awk '{print $10}')   #获取到Transmit字段中的bytes
   
    # 获取1秒后网口接收与发送的流量
    sleep 1
    ReceiveNext=$(cat /proc/net/dev | grep $eth | awk '{print $2}')
    TransmitNext=$(cat /proc/net/dev | grep $eth | awk '{print $10}')
    
    clear
    # 获取这1秒钟实际的进出流量
    Receive=$((${ReceiveNext}-${ReceiveCur}))
    Transmit=$((${TransmitNext}-${TransmitCur}))
    
    # 判断接收流量如果小于1024，则显示B(Bytes)数量级
    if [[ $Receive -lt 1024  ]];then
        Receive="${Receive}B/s"
        STATUS="normal"
    elif [[ $Receive -ge 1048576  ]];then      # 1024*1024，大于1024*1024则显示MB数量级
        Receive=$(echo $Receive | awk '{print $1/1048576 'MB/s'}')
        STATUS="fluently"
    else
        # 判断接收流量如果大于等于1024且小于1048576数量级则显示KB数量级
        Receive=$(echo $Receive | awk '{print $1/1024 'KB/s'}')
        STATUS="good"
    fi


    # 判断发送流量的数量级
    if [[ $Transmit -lt 1024  ]];then
        Transmit="${Transmit}B/s"
    elif [[ $Transmit -ge 1048576  ]];then
        Transmit=$(echo $Transmit | awk '{print $1/1048576 "MB/s"}')
    else
        Transmit=$(echo $Transmit | awk '{print $1/1024 "KB/s"}')
    fi

    # 打印信息
    echo -e "\E[1;35m" '***********************************'
    echo -e "\E[1;36m" 'Welcome to Traffic_Monitor stage'
    echo -e "\E[1;36m" 'Operator System Type:' ${OS_NAME}
    echo -e "Date: `date +%F`"
    echo -e "Time: `date +%k:%M:%S`"
    echo -e "Port: $1"
    echo -e "Status: $STATUS" $(tput sgr0)
    echo -e " \t Receive \tTransmit"
    echo "----------------------------------"
    # 打印实时流量
    echo -e "$eth \t "   " $Receive  \t $Transmit "
    echo "----------------------------------"
    # 退出信息
    echo -e "\E[1;35m" '***********************************' $(tput sgr0)
    echo "Press 'Ctrl+C' to exit!"
done
}

# 判断执行参数
if [[ -n "$1"  ]];then     #判断输入的参数字符串$1长度非0则为真
    # 执行函数
    traffic_monitor $1
else
    echo -e "None parameter,please add system netport after run the script! \nExample: 'sh traffic_monitor eth0'"
fi
