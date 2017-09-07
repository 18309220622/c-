#!/bin/bash
setTermOp=$(tput sgr0)    #把终端经常执行的命令写入一个变量中，否则每次结尾处都得写上$(tput sgr0)来回归终端初始化状态的颜色
declare -A sharray        #设置关联数组，存储键值，脚本号码即键，文件名即值
i=0
numbers=""
for file in `ls -I "monitor_man.sh" ./`
do 
    echo -e "\e[1;34m" 'The Script:' $i '-->' ${setTermOp} ${file}
    sharray[$i]=${file}
    numbers="${numbers} | $i" 
    let i++
done
#echo ${numbers}

while true
do
    read -p "Please input a number[$numbers]:" execshell  #将输入的值传进去作为变量
    if [[ $execshell=^[0-2] ]] ;then
        if [[ $execshell -eq 1 ]];then
            sh ./${sharray[${execshell}]} eth0       #执行对应的脚本
        else
            sh ./${sharray[${execshell}]}
        fi
    else
        exit 0
    fi
done
