#!/bin/bash

# Этот скрипт создает жесткую ссылку на переданный файл
# переносит его в скрытый каталог ~/.trash в домашнюю директорию
# заносит информацию об этом в скрытый файл в дом. дир. ~/.trash.log

DELETED_FILE=""
DELETED_FILE+="$1"

cd $HOME/.trash || mkdir $HOME/.trash; echo "[+] DIR $HOME/.trash was be created"

if [[ "$DELETED_FILE" == "" ]]; then
	echo "[-] Give file name which was be deleted !"; echo "Exiting.."
	exit 0
else
	echo "[+] File name was be deleted $DELETED_FILE is saved !"
fi

read -p "You are realy want to delete this file $DELETED_FILE ? [Y/N]:" ch;

if [[ "$ch" == "Y" || "$ch" == "y" ]]; then
        echo " "
elif [[ "$ch" == "N" || "$ch" == "n" ]]; then
        echo "Okey, Goodbye!";exit 0
else
        echo "Try again!"; echo "Exiting...";exit 1
fi

HARDLINK_NAME="${DELETED_FILE}_deleted"

ln $DELETED_FILE $HARDLINK_NAME; mv $HARDLINK_NAME $HOME/.trash
rm $DELETED_FILE

echo "[+] File $DELETED_FILE was be deleted !"

echo "Link: <$HARDLINK_NAME> Deleted FILE: $DELETED_FILE" >> ~/.trash.log

exit 0
