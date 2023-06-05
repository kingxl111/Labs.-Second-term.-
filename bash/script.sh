#! /bin/bash

#Задача: вывести три предмета, по которым меньше всего четверок на 1 факультете

sort -t ':' -n -k 1,1 marks > marks_srt # по id студента
sort -t ':' -n -k 1,1 stud > stud_srt # по id студента 
sort -t ':' -n -k 1,1 grp > grp_srt #по id группы
sort -t ':' -n -k 1,1 subj > subj_srt #по id предмета 

#совмещаем оценки и студентов
join -t ':' -1 1 -2 1 marks_srt stud_srt > markstud_srt

# cat markstud_srt

#совмещаем оценки, студентов, группы
sort -t ':' -n -k 4,4 markstud_srt > mssortg

join -t ':' -1 4 -2 1 mssortg grp_srt > markstudgrp

# cat markstudgrp

#совмещаем оценки, студентов, группы, предметы
sort -t ':' -k 3,3 markstudgrp|head -n -1|cat > msgsortp


grep ".*:.*:.*:4:.*:1:.*" msgsortp > msgsortp4
# cat msgsortp4

subjs=$(awk -F ':' '{print $1}' subj|sort|head -n -1)
tmp=$(mktemp)
id=1
echo "id предмета:количество четверок" > $tmp
for sidx in $subjs; do
    cur_count=$(grep ".*:.*:$sidx:.*:.*:1:.*" msgsortp4|wc -l)
    echo "$id:$cur_count" >> $tmp
    id=$((id + 1))
done

# cat $tmp
# cat subj_srt
# cat $tmp
join -t ':' -1 1 -2 1 subj_srt $tmp > result
sort -t ':' -n -k 3,3 result > answer

head -4 answer|sed 's/:/ /g'|awk '{print $2}'|tail -3
