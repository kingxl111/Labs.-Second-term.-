#! bin/bash

#сортируем все файлы по id
sort -t ':' -k 1,1 marks >> marks2
sort -t ':' -k 1,1 stud >> stud2
sort -t ':' -k 1,1 grp >> grp2
sort -t ':' -k 1,1 subj >> subj2

#совмещаем оценки и студентов
join -t ':' -1 1 -2 1 marks2 stud2 > markstud.txt

#совмещаем оценки, студентов, группы
sort -t ':' -k 4,4 markstud.txt >> mssortg
join -t ':' -1 4 -2 1 mssortg grp2 > markstudgrp

#совмещаем оценки, студентов, группы, предметы
sort -t ':' -k 2,2 markstudgrp >> msgsortp
join -t ':' -1 2 -2 1 msgsortp subj2 >> markstudgrpsubj

cat markstudgrpsubj
#оставляем только двойки второго факультета 
awk -F  ':' '$6==4' markstudgrpsubj | awk -F  ':' '$3==4' >> mstgs22

#обрезаем, оставляем только оценки и предметы 
cut -d ':' -f 3,8 mstgs22 >> marksubj

#сортируем, оставляем с подсчитанными двойками по предметам, по убыванию количества двоек, а потом выводим топ 3 предмета
sort marksubj | uniq -c | sort -nr | head -n 3 > ans

#выводим ответ
cat ans