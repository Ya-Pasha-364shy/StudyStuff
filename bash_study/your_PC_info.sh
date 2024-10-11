
echo -e "Дата: \c"
date

echo -e "Имя учётной записи ПК: \c"
whoami

echo -e "Доменное имя ПК: \c"
hostname

echo "Процессор: "

echo -e "\t*\c"
lscpu | grep -i "Модель:"| head -1

echo -e "\t*\c"
lscpu | grep -i "Архитектура:" | head -1

echo -e "\t*Тактовая частота:\c"
grep -i "cpu MHz" /proc/cpuinfo  | head -1 | awk '{printf("\t\t %s\n",$4)}' 

echo -e "\t*Количество ядер:\c"
lscpu | grep -i "CPU(s):" | head -1 | awk '{printf("\t\t\t%s\n",$2)}'

echo -e "\t*Количество потоков на ядро:\c"
lscpu | grep -i "Потоков на ядро:" | awk '{printf("\t\t%s\n",$4)}' 


echo "Оперативная память:"

echo -e "\t*Всего:\c"
cat /proc/meminfo | grep -i "MemTotal" | awk '{printf("\t\t\t\t %s\n",$2)}' 

echo -e "\t*Доступно:\c"
cat /proc/meminfo | grep -i "MemAvailable"| awk '{printf("\t\t\t %s\n",$2)}'

echo -e "Жесткий диск:"

echo -e "\t*Всего - \c"
df -h | grep -E '/dev/sda4' | grep -v "Файл.система" | awk '{print($2)}'
echo -e "\t*Доступно - \c"
df -h | grep -E '/dev/sda4' | grep -v "Файл.система" | awk '{print($4)}'
echo -e "\t*Смонтировано в корневую директорию \\ - \c"
df -h | grep -E '/dev/sda2' | grep -v "Файл.система" | awk '{print($2)}'

echo -e "\t*SWAP всего - \c"
swapon -s  | grep -v "Имя файла" | awk '{print($3)}'

echo -e "\t*SWAP доступно - \c"
swapon -s  | grep -v "Имя файла" | awk '{print($3-$4)}'

echo "Сетевые интерфейсы"


#df -h | grep -i "" | head -1 


INT1=1

echo "_________________________________________________________________"

echo -e " № |\c"
for data in "Net" "ipv4" "MAC" "Speed"
do
	echo -e "\t$data\t|\c"
done
echo ""

for iname in $(ip a | awk '/state UP/{print $2}' | sed 's/://')
do
echo "_________________________________________________________________"
echo -e "$INT1. | \c"

echo -e "$iname |\c"

ifconfig $iname | grep -Ei "inet" | grep -Eiv "inet6" | awk '{printf($2)}'
echo -e " | \c"

ifconfig $iname | grep -i "inet" | grep -Ei "inet6" | awk '{printf($2)}'
echo -e " | \c"

iwconfig $iname | grep -i 'Bit' | awk '{printf($1$2$3 )}' | cut -f2 -d"="

INT=$(($INT1+1))

done

echo "_________________________________________________________________"

