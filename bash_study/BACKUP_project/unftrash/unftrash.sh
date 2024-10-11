#!/bin/bash
# Восстанавливаем данные из файла ~/.trash.log
# который был создан скриптом rmftrash.sh (смотри в директории rmftrash)
UPF=""
UPF+=$1

if [[ "$UPF" == "" ]]; then
	echo "[-] Give me filename was be restored!"; echo "Exiting.."; exit 1
else
	echo "[+] File name was be RESTORED: $UPF is saved !"
fi; touch pipe1.txt pipe2.txt
cat ~/.trash.log | sed "s/^Link: //" | sed "s/<//" | sed "s/>//" | sed "s/Deleted FILE.*//" > pipe1.txt

echo "[*] You want to restore file: $UPF"
echo -n "[+] The following matches were found in the log file:"; cat pipe1.txt | grep -i "$UPF" > pipe2.txt; cat pipe2.txt
read -p "[*] Do u want to restore this files? [Y/N]: " ch

if [[ "$ch" == "Y" || "$ch" == "y" ]]; then
	echo "[*] Lets start process of restoring!"
elif [[ "$ch" == "N" || "$ch" == "n" ]]; then
	echo "Okey, Goodbye!";exit 0
else
	echo "Try again!"; echo "Exiting...";exit 1
fi;rm pipe1.txt

while read line; do
	echo "[+] From ~/.trash.log was be find this deleted file: $line"
	echo "Restoring..."
	
	TO_RESTORED=`echo $line | sed "s/\/home\/k1rch\/.*\//\/home\/k1rch\/.trash\//"`
	SPAM=`echo "$line" | sed -e "s/$UPF/\.trash\/$UPF/"`
	real_valid_name=`echo "$SPAM" | sed "s/\/.trash//" | sed "s/_.*//"`
	HOME_DIR=`echo $TO_RESTORED | sed "s/\/\.trash//" | sed "s/_deleted//"`

	ln $TO_RESTORED $real_valid_name || ln $SPAM $real_valid_name || ln $TO_RESTORED $HOME_DIR
	rm $TO_RESTORED || rm $SPAM
	echo "[+] File $TO_RESTORED was be restored as $real_valid_name"

done<./pipe2.txt
rm pipe2.txt

echo "[+] Done"
exit 0
