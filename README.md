![alt text](https://i.imgur.com/YUaJEut.png)
![alt text](https://i.imgur.com/CIKsOMi.png)

## About
Многопоточный сканер портов, с точностью nmap-а, брутфорсом самых популярных протоколов и сканированием DNS.
Был сделан с вдохновением от ![nesca3](https://github.com/pantyusha/nesca) & ![nmap](https://github.com/nmap/nmap).  

Может сканировать методами: `SYN` `FIN` `XMAS` `FIN` `NULL` `WINDOW` `ACK` `MAIMON`.  
Может выполнять пинг методами: `SYN` `ACK` `ICMPECHO` `ICMPINFO` `ICMPTIMESTAMP`.  
Может брутфорсить: `RVI` `HIKVISION` `BASICAUTH` `FTP` `SSH` `SMTP` `RTSP`.

**PS:** Перечислять все возможности тут я не буду. Прочитать о том что умеет nesca4 и как это разрабатывалось читайте в **resources/do_not_read.txt**

## Installation
**Я не заливаю код который не компилируется!
Если не выходит, значит у вас что-то не так с системой.**

**Debian 11:**  
```
    sudo apt-get install libcurl4-openssl-dev
    sudo apt install g++ make git cmake libssh-dev
    git clone https://github.com/oldteamhost/nesca4
    cd nesca4
    cmake .
    make -j12
```
**Arch 2023:**  
```
    sudo pacman -S curl cmake
    git clone https://github.com/oldteamhost/nesca4
    cd nesca4
    cmake .
    make -j12
```
## 20230722
- Обновлён дизайн, лог, цвета.
- Конфиг для колосхем.

## 20230721
- Исправлена segmentation error при сканирование портов.
- Казырная работа с группами, их постепенное увелечение.
- Добавлены таймеры, и увеличена скорость.
- Исправлены ошибки DNS resolv.
- Сильно улучшены группы.
- Новые аргументы.

## 20230720
- Добавлены алгоритмы обработки, теперь используеться "Strategy Pattern".
- Расчёты теперь происходят по формулам.
- Обновлены цвета, теперь всё оригинальные из nesca3.
- Потоки в брутфорсе теперь тоже через пул.
- Брутфорс ускорен в 2 раза.
- Теперь кастомные цвета указываються в html формате.
- Исправлены бесконечные циклы, при брутфорсе.

## 20230719
- Наконец то добавлен пул потоков.
- Переписаны все потоки.
- Сильно увеличена скорость работы вообще всего.
- Исправлены все ошибки из-за потоков.

## 20230718
- Исправлены ошибки с памятью при сканирование.
- Исправлен таймаут при сканирование.
- Улучшен packet-trace, но только для сканирования.
- Сильно улучшено сканирование.
- Увеличена скорость.

## 20230716
- Исправлен бесконечный цикл ICMP пинга.
- Почти весь код main файла улучшен.
- Добавлен top_negatives.txt.
- Улучшен брутфорс.
- Улучшено DNS сканирование.
- База определения побольше.

## 20230715
- Добавлен лист negatives с конфигом для них.
- Обновлён do_not_read.txt
- Увеличена скорость обработки.
- Исправлен http request.
- Да и вцелом баги.

## 20230705
- Добавлен брутфорс RVI камер.
- Исправлен HTTP запрос.
- Исправлены баги, я хз сколько их ещё фиксить.
- Устранение багов, добавление получение характеристики к HTTP портам.
- Наконец то, добавлено сканирование группами как в nmap.
- Улучшен вывод в HTML.
- Исправлен лог в txt.

## 20230704
- Добавлено и настроено оригинальное сохранение в html.
	- Страница с nesca3.
- Улучшен лог.
- Исправлены баги.

## 20230703
- Передрочено почти всё, убраны ненужные аргументы.
- Добавлено ACK, WINDOW, MAIMON сканирование.
- Исправлено FIN, XMAS, NULL сканирование.
- Улучшен пинг.
- Добавлено больше опций.

## 20230702
- Добавлен ICMP пинг на этот раз 100% рабочий.
	- ICMP ECHO классика.
	- ICMP INFO запрос на информацию.
	- IMCP TIMESTAMP запрос на время.
- Добавлены аргументы для работы с пингом.
- Добавлены аргументы для управления скоростью.

## 20230701
- Снова фиксы багов.
- Добавлены потоки для получения dns.
- Увеличена скорость.

## 20230629
- Испралены все зажержки и баги сканирования.
- Добавлен и успешно работает ACK ping.
- Снова улучшено всё.

## 20230626
- Испралены потоки.
- Исправлен лог.
    - Но пока выводит только когда просканировал все цели.
- Улучшены модули.
- И ваще уже чётко.

### 20230608 
- Сканирование полностью переписано.
- Пинг сканирование тоже.
- Улучшено всё.
- Улучшен дизайн.
- Но пока нету потоков.

### 20230531
- Испралена большая часть багов.
- Добавлено сканирование XMAS,FIN,NULL.
- Добавлено Ping сканирование.
    - 3 метода IMCP пинга.
    - Пинг TCP.
- Обновление дизайна.
- Почти готова к релизу.
- Добавлен брутфорс SMTP.

### 20230530
- Исправлены все функции.
- Улучшен код везде.

### 20230528
- FTP, SSH буртфорс переписан без libcurl + скорость.
- Исправлен бутфорс HTTP.
- Немного изменения по коду.

### OLDER
+ Добавлена многопоточность для сканирования портов.
+ Добавлены оригинальные цвета с nesca3.
+ Настроен вывод.
+ Исправлена случайная остановка во время сканирования.
+ Добавлены цвета для DNS сканирования.
+ Добавлен аргумент -no-color.
+ Оптимизированы цвета.
+ Добавлены цвета в help menu.
+ Добавлено сохранение в txt для сканирования портов.
+ Настроен debug для сканирования портов.
+ Добавлен брутфорс FTP.
+ Добавлены filter ports в debug.
+ Добавлен обход фаервола сканирования.
+ Добавлены аргументы ftp-brute-log и ftp-brute-verbose.
+ Добавлена поддержка импорта и сканирования ip диапазонов.
+ Добавлены новые аргументы: -host-test -tcp-ping -response-code -gen-count -gen-ipv4 -gen-ipv6.
+ Добавлены новые разделы testing и generation.
+ Добавлен брутфорс ssh AKA sftp.
+ Добавлен аргумент -sftp-brute-known-hosts для проверки доверенных ключей.
+ Добавлен брутфорс RTSP.
+ Убраны ненужные брутфорс аргументы, добавлены более автономные.
+ Исправлено segmentation error при откючение RTSP.
+ Добавлены потоки для брутфорса FTP, SSH, RTSP.
+ Добавлен новый аргумент, -brute-timeout.
+ Исправлена максимальная задержка брутфорса в 25секунд.
+ Программа разделена по файлам, до этого весь код был в одном).
+ Добавлен аргумент -on-get-dns.
+ Добавлена два метода парсинга для абсолютных.
+ Добавлено распозвование и парсинг абсолютных путей.
+ Исправлены ошибки парсинга путей, и пердусмотрены любые моменты.
+ Добавлен новый аргумент -no-get-path>
+ Исправлен парсинг путей, переписаны все функции парсинга на regex.
+ Добавлен парсинг из content, content location, и window.location.href в js.
+ Добавлены 2 аргумента, -fix-get-path и -get-path-log
+ Добавлено сохранение redirect в txt и немного изменён дизайн вывода.
+ Весь вывод перенесён в отдельный класс.
+ Исправлены кривые цвета.
+ Добавлена возможность использывать кастомные цвета из конфига.
+ Добавлен аргумент -import-color для парсинга конфига.
+ Добавлена одна color scheme в стиле "retrowave".
+ Добавлена поточность дял брутфорсов.
+ Добавлен брутфорс axis камер aka http basic auth.
+ Добавлено распознование http брутфорса.
+ Добвлены http title для брутфорса.
+ Переписан вывод полностью, убран говнокод.
+ Добавлено определение описание ftp сервера.
+ Добавлены новые шаблоны портов http,https,sftp,ftp
+ Убран брутфорс RTSP, он был не рабочий, и сделать его я пока не знаю как.
+ Кое как сделан брутфорс RTSP на сколько рабочий не знаю.
+ Добавлен брутфорс hikvision камер.
+ Сделан чёткий make файл.
+ Убрано ненужное сообщение при брутфорсе hikvision.
+ Исправлен вывод http title.
+ Исправлена утечка памяти.
+ Теперь для главных потоков используеться future вместо threads.
+ Добавлено отключение получения описания ftp после 15 секунд неудачного подключения.
+ Наконец исправлена ошибка с segmentation error при получение путей.
+ Добавлен новый аргумент в тестрирование -redirect.
+ Добавлен новый аргумент в тестрирование -http-request.
+ Добавлена возможность указывать диапазон портов, типа 0-65535.
+ Убран говнокод из main файла.
+ Переписана функция по сканированию портов.
+ Проект перешёл на cmake.
+ Наконец то написано syn сканирования вместо tcp.
+ За счёт syn сканирования, теперь есть обход фаерволов.
+ Увеличена аннонимность, за счёт неполного подлкючения.
+ Увеличена скорость.
+ Настроена кроссплотформленность.
+ Исправлено syn сканирования повышена точность.
+ Добавлены новые аргументы -sss-timeout, -ssr-timeout
+ Добавлен debug для syn сканирования -syn-db, syn-debug.
+ Добавлен icmp ping.
+ Добавлены новые аргументы для icmp ping.
+ Улучшен icmp ping.
+ Переписан вывод.
+ Сохранение в txt вновь рабочее.
+ Улучшем код в main файле, и его читабельность.
+ Добавлено куча всего, слишком много измененей.

export LD_LIBRARY_PATH=lib/platform/linux
