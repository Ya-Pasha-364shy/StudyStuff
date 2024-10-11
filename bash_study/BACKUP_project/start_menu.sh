#!/bin/bash
# Choise whatever you want:

DIALOG=${DIALOG=dialog}
tempfile=`mktemp 2>/dev/null` || tempfile=/tmp/test$$
trap "rm -f $tempfile" 0 1 2 5 15

$DIALOG --clear --title "MAIN MENU" \
        --menu "Choise something of follow list:" 30 70 4 \
	"Remove a file (need full path):" "1 (remftrash)" \
	"Restore a file from trash (need file's name):" "2 (unftrash)" \
	"Make backup or refresh actual:"  "3 (makebackup)" \
	"Restore backup files now:"  "4 (restorebackup)" 2> $tempfile

retval=$?

choice=`cat $tempfile | sed "s/://g"`

case $retval in
  0)
    echo "[+] Starting process of +---$choice---+";;
  1)
    echo "Отказ от ввода."; exit 0;;
  255)
    echo "Нажата клавиша ESC."; exit 1;;
esac

result=1

if [[ "$choice" == "Remove a file (need full path)" ]]; then
	echo "Script ./remftrash/remftrash.sh was be started !"
	read -p "Need parameter: full path to file:" PARAM
	result=`bash ./remftrash/remftrash.sh $PARAM`
	
elif [[ "$choice" == "Restore a file from trash (need file's name)" ]]; then
	echo "Script ./unftrash/unftrash.sh was be started !"
	read -p "Need parameter: NAME OF THE RESTORING FILE:" PARAM
	result=`bash ./unftrash/unftrash.sh $PARAM`
        
elif [[ "$choice" == "Make backup or refresh actual" ]]; then
	echo "Script ./makebackup/makebackup.sh was be started"
	result=`bash ./makebackup/makebackup.sh`

elif [[ "$choice" == "Restore backup files now" ]]; then
	echo "Script ./restorebackup/restorebackup.sh was be started"
	result=`bash ./restorebackup/restorebackup.sh`
else
	echo "Invalid choice. Try again!"; echo "Exiting.."; exit 0;
fi


echo $result
if [[ $result == 0 ]]; then
	echo "Great ! Successfully Complete!"
fi
exit 0;
