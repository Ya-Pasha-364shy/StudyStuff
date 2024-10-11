#!/bin/bash

touch full.log
sudo grep -E 'OK|WARNING' /var/log/*.log --color=auto > full.log

for i in OK Error; do
	if [ "$i" == "OK" ]; then
		sed -i "s/$i/Information:/" ./full.log
       	elif [ "$i" == "Error" ]; then
		sed -i "s/$i/Warning:/" ./full.log
	fi
done	

cat full.log; rm full.log
echo "DONE"
exit 0
