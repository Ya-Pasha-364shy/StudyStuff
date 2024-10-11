#!/bin/bash

touch scripts.txt output.txt

# Сохраняем в файл scripts.txt все файлы, дискришон которых POSIX shell script..
sudo file /bin/* | grep -i "POSIX" > scripts.txt

# отделяем не нужное, сохраняя список скриптов в файл.
while IFS= read -r line; do
	echo $line | awk '{print $1}' | sed "s/://" >> output.txt
done<./scripts.txt

# Преимущественно встречается интерпретатор #!/bin/sh
# посмотрим сколько раз..
counter=0

while IFS= read -r line; do
	INR=`sudo cat $line | head -n1 | tail -n1 | sed "s/\n//" | sed "s/ //"`
	if [[ $INR == '#!/bin/sh' ]]; then
		counter=$(($counter + 1))
	fi
done<./output.txt       

cat output.txt | sort
echo "Премущественно используется интерпретатор #!/bin/sh, встречается: $counter РАЗ"

rm scripts.txt output.txt
exit 0

