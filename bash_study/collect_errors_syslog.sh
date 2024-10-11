#!/bin/bash

touch errors.log
sudo grep -a syslogd /var/log/*.log --color=auto > errors.log
exit 0
