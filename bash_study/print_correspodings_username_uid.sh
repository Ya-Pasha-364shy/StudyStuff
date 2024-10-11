#!/bin/bash

touch data.txt output.txt

sudo cat /etc/passwd > data.txt

# обрезаем часть
while IFS= read -r line; do
	echo $line | awk '{print $1}'  >> output.txt
done<./data.txt
rm data.txt

# определяем имя пользователя и его UID
while IFS= read -r line; do
	var1=${line%:x*}
	spam=${line#*x:}
	var2=${spam%:*}
	
	var2=`echo $var2 | sed 's/\(\:\(.\)\{1,\}\)//'`
	
	echo "USER'S NAME: $var1 UID: $var2"
done<./output.txt


rm output.txt
exit 0
