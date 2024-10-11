#!/bin/bash

touch files.txt emails_sp.lst emails.lst;

# поиск всех файлов в каталоге /etc/ и его подкатологах
sudo find /etc/* -type "f" > files.txt

# открываем все файлы и ищем там все упоминания чьей-либо почты

while IFS= read -r line; do
	sudo cat $line | grep -i "[a-z\(.\)\{1,\}]\(@\)[.com|.gmail|.ru|.org]" >> emails_sp.lst
	
done<./files.txt

cat emails_sp.lst | sort | uniq > emails.lst
rm files.txt emails_sp.lst
echo "DONE"
exit 0
