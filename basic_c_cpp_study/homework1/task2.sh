#!/bin/bash

# Description:
# 
# Напишите скрипт, который скопирует /opt/hw1/datasets.tar.gz в путь
# /opt/user2_for_user3/datasets.tar.gz и разрешите пользователю user3 его прочитать.
# Владельцем конечного файла должен быть user2.
# Учите права на директории/файлы в системе.

sudo cp /opt/hw1/datasets.tar.gz /opt/user2_for_user3/
sudo chmod 644 /opt/user2_for_user3/datasets.tar.gz
sudo chown -R user2:user2  /opt/user2_for_user3