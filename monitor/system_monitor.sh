#!/bin/bash
if [[ $# -eq 0 ]]
then
    setTerminal=$(tput sgr0)
    
    #1.检查操作系统的类型
    os=$(uname -o)
    echo -e "\E[1;33m" 'Operator System Type:' ${setTerminal} ${os} 

    #2.检查操作系统的版本和名字
    os_name=$(cat /etc/issue | grep "release")
    echo -e "\E[1;33m" 'OS Release Version and Name:' ${setTerminal} ${os_name}
    
    #3.检查CPU的子令集，是32位还是64位
    architecture=$(uname -m)
    echo -e "\E[1;33m" 'architecture:' ${setTerminal} ${architecture}
    
    #4.获取操作系统的内核版本
    kernelRelease=$(uname -r)
    echo -e "\E[1;33m" 'OS kernelRelease:' ${setTerminal} ${kernelRelease}

    #5.获取主机名的两种方式
    #hostName=$(uname -n)
    #hostName= set | grep "HOSTNAME"
    echo -e "\e[1;33m hostname is: \e[0m" ${HOSTNAME} 

    #6.查看内网IP地址的两种方式
    InternalIP=$(hostname -I)
    echo -e "\E[1;33m" 'Internal IP:' ${setTerminal} ${InternalIP}
   # InternalIP=$(ifconfig | grep "inet addr" | cut -f 2 -d ":" | cut -f 1 -d " ")

    #7.查看外（公）网IP
    ExternalIP=$(curl -s http://ipecho.net/plain)
    echo -e "\E[1;33m" 'External IP:' ${setTerminal} ${ExternalIP}

    #8.检测DNS
    nameservers=$(cat /etc/resolv.conf | egrep "^nameserver " | awk '{print $NF}')
    echo -e "\E[1;33m" 'check DNS:' ${setTerminal} ${nameservers}

    #9.检测是否连通网络
    ping -c 2 baidu.com &>/dev/null && echo -e "\E[1;33m"'Internet:Connected' ${setTerminal} || echo -e "\E[1;33m" 'Internet:Disconnected' ${setTerminal}    #ping两次

    #10.检查当前登录用户数
    who>/tmp/who
    echo -e "\E[1;33m" 'Logged in Users:' ${setTerminal} && cat /tmp/who
    rm -f /tmp/who      #避免下次的文件还是之前的而导致信息有误

    echo -e "\E[1;34m" '############################################'
    #计算系统使用内存，这里已经将字节数转化为了kb单位
    system_mem_used=$(awk '/MemTotal/{total=$2}/MemFree/{free=$2}END{print (total-free)/1024}' /proc/meminfo)
    echo -e "\E[1;33m" 'system memmory used:' $setTerminal $system_mem_used

    #计算应用使用内存，注意Cached中包含两部分，一是Cached,二是SwapCached,这里要除掉SwapCached那一部分
    applicate_mem_used=$(awk '/MemTotal/{total=$2}/MemFree/{free=$2}/^Cached/{cache=$2}/Buffers/{buffers=$2}END{print (total-free-cache-buffers)/1024}' /proc/meminfo)
    echo -e "\E[1;33m" 'applicate memmory used:' $setTerminal $applicate_mem_used

    loadaverage=`top -n 1 -b | grep "load average:" |awk '{print $12 $13 $14}'`
    echo -e "\E[1;33m" 'load average:' ${setTerminal} ${loadaverage}
   
   #经验证$()不能正确的输出负载信息，可能跟平台有关，于是选择反引号（反引号所有平台都支持）
   #经过过滤输出的第12 13 14个域里的内容表示最近1分钟，5分钟，15分钟系统的平均负载

    diskaverage=$(df -h| egrep -v 'Filesystem|tmpfs' | awk '{print $1 "  " $5}')
    echo -e "\E[1;33m" 'diskaverage:' ${setTerminal} ${diskaverage}

fi
