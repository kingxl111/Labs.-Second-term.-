#! /bin/env bash

function merge 
{
    local f1="$1"
    local suff="$2"
    local conc_f="$3"
    local cur_file_size=$(wc -c "$conc_f"|awk '{print $1}')
    local ext=."${conc_f##*.}" #расширение текущего файла
    local input_file_size=$(wc -c "$f1"|awk '{print $1}')
    if [[ "$suff" == "$ext" ]] ; then
        if [[ "$cur_file_size" -lt "$input_file_size" ]] ; then
            cat "$conc_f"
        fi 
    fi
}

function get_pm
{
    local SUff=''
    local Path_to_cmp_file=''
    local CONF="$1"
    while IFS='=' read var val; do
        if [[ "$var" == "suff" ]]; then 
            SUff="$val"
        elif [[ "$var" == "pth_to_file" ]]; then 
            Path_to_cmp_file="$val"
        fi
    done < "$CONF" 
    SUff=$(echo "$SUff" | sed s/'"'//g)
    Path_to_cmp_file=$(echo "$Path_to_cmp_file" | sed s/'"'//g)
    echo "$SUff":"$Path_to_cmp_file"
}

function esc
{
    $(rm "$result")
    echo "error!"
}

is_c=0 #parameters from config.txt
is_l=0 #print the number of lines in result
is_o=0 #save the result to file
is_s=0

MN="manual_RU.txt"
MN_eng="manual.txt"
config="config.txt"

count=0 #size of array of input_files

while [[ $# > 0 ]]; do
{
    prm="$1"
    if [[ "$prm" == "-l" ]]; then
        is_l=1
        shift
    elif [[ "$prm" == "-f" ]]; then
        is_f=1
        shift
    elif [[ "$prm" == "-c" ]]; then
        is_c=1
        shift
    elif [[ "$prm" == "--help" ]]; then
        cat $MN
        shift
        break
    elif [[ "$prm" == "-s" ]]; then 
        shift
        suf="$1"
        shift
    elif [[ -f "$prm" ]]; then
        break
    else 
        echo "unknown parameter"
        exit 1
    fi
} done

if [[ $is_c != "1" ]]; then
    cmp_file="$1"
    shift
fi

while [[ $# > 0 ]]; do
{
    prm="$1"
    if [[ -f "$prm" ]]; then
        arr[$count]="$1"
        count=$((count + 1))
        shift
    elif [[ "$prm" == "-o" ]]; then
        shift
        is_o=1
        new_file_name="$1"
        break
    else
        exit 1
    fi
    trap esc ERR
} done

result="$(mktemp)" #tmp file that will be used as result

if [[ $is_c == 1 ]]; then
    suf=$(get_pm "$config"|awk --field-separator ":" '{print $1}' )
    cmp_file=$(get_pm "$config"|awk --field-separator ":" '{print $2}')
    trap esc ERR
fi

#echo "suf: $suf"
#echo "cmp_file: $cmp_file"

for i in "${arr[*]}"; do
    #echo "$i"
    merge "$cmp_file" "$suf" "$i" >> "$result"
    trap esc ERR
done

if [[ $is_l == 1 ]]; then
    l=$(wc -l "$result"|awk '{print $1}')
    echo "Total lines: $l" >> "$result"
    if [[ $is_o == 1 ]]; then
        touch "$new_file_name"
        cat "$result" >> "$new_file_name"
    else
        cat "$result"
    fi
    trap esc ERR
else 
    if [[ $is_o == 1 ]]; then
        touch "$new_file_name"
        cat "$result" >> "$new_file_name"
    else 
        cat "$result"
    fi 
fi

if [[ -e "$result" ]]; then 
    rm "$result"
fi
