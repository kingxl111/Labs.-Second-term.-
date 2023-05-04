#! /bin/env bash

suff=".txt"
pth_to_files="/home/vadim/2 семестр/Labors/Lab21/my_l21Files"
#echo $pth
#cat "$pth"/my_file8.txt


#cat "$input_file"
#wc -c file.txt

echo "Введите имя файла:"
read in_file
input_file="$pth_to_files/$in_file"

if [[ -f "$input_file" ]] ; then
    echo "Введите суффикс подходящих файлов в формате .suff: "
    read suff

    input_file_size=$(wc -c "$input_file"|awk '{print $1}')

    #echo $input_file_size
    is_succes=0
    touch Result.txt
    for f in "$pth_to_files"/* ; do
        cur_file_size=$(wc -c "$f"|awk '{print $1}')
        ext=.${f##*.} #расширение текущего файла
        if [[ $suff == $ext ]] ; then
            if [[ $cur_file_size < $input_file_size ]] ; then
                is_succes=1
                cat "$f" >> Result.txt
            fi
        fi

    done

    if [[ $is_succes -eq 0 ]] ; then 
        rm Result.txt
        echo "Нет подходящих файлов"
    else
        echo "Программа завершила работу успешно"
    fi

else
    echo "Такого файла не существует!"
fi