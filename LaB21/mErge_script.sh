#! /bin/env bash


function merge 
{
    local f1="$1"
    local suff="$2"
    local conc_f="$3"
    local cur_file_size=$(wc -c "$conc_f"|awk '{print $1}')
    local ext=.${conc_f##*.} #расширение текущего файла
    local input_file_size=$(wc -c "$f1"|awk '{print $1}')
    if [[ "$suff" == "$ext" ]] ; then
        if [[ "$cur_file_size" -lt "$input_file_size" ]] ; then
            is_succes=1
            cat "$conc_f"
        else 
            #echo "The size of $conc_f doesn't satisfy the condition" 
            echo "-1" 
        fi
    else
        #echo "The suffix of $conc_f doesn't satisfy the condition"
        echo "-1"  
    fi
}

function get_pm
{
    local SUff=''
    local Path_to_cmp_file=''
    local CONF="$1"
    while IFS='=' read var val; do
        #echo "$var" "$val"
        if [[ "$var" == "suff" ]]; then 
            SUff="$val"
        elif [[ "$var" == "pth_to_file" ]]; then 
            Path_to_cmp_file="$val"
        fi
    done < "$CONF"
    #<(sed 's/=/ /g' "$CONF")  
    
    #echo $SUff
    #echo $Path_to_cmp_file
    SUff=$(echo "$SUff" | sed s/'"'//g)
    #echo "$SUff"
    Path_to_cmp_file=$(echo "$Path_to_cmp_file" | sed s/'"'//g)
    #Path_to_cmp_file=$(echo "$Path_to_cmp_file"|sed s/^/'"'/g|sed s/$/'"'/g)
    echo "$SUff":"$Path_to_cmp_file"
}

function die
{
    # if [[ -f RESULT.txt ]]; then
    #     rm RESULT.txt
    # fi
    
    exit 1
}

is_f=0 #print names of files, that has been merged
is_c=0 #parameters from config.txt
is_l=0 #print the number of lines in result
is_o=0 #save the result to file
is_help=0 #key --help

is_keys_done=0 #All keys has been taken
is_suf=0 #has suffics been taken?
is_file=0 #has script taken a file?

lines_c=0

MN="manual_RU.txt"
MN_eng="manual.txt"

if [[ -n "$1" ]]; then
    touch RESULT.txt
    counter="$#"
    parameters_num=$counter
    while [[ "$counter" > 0 ]]; do
        prm="$1"
        if [[ "$prm" == "--help" ]]; then
            if [[ $is_c == 0 ]] && [[ $is_f == 0 ]] && [[ $is_help == 0 ]] && [[ $is_l == 0 ]]; then 
                is_help=1
                shift
            else
                echo "ERROR: Key --help must be alone"
                die
            fi
        elif [[ $prm == "-l" ]]; then
            if [[ $is_help == 0 ]]; then
                is_l=$((is_l+1))
                shift
            else 
                echo "ERROR: If a key --help is used, it should be passed to the script as the only parameter"
                die
            fi
        elif [[ "$prm" == "-f" ]]; then
            if [[ $is_help == 0 ]]; then
                is_f=$((is_f+1))
                shift
            else 
                echo "ERROR: If a key --help is used, it should be passed to the script as the only parameter"
                die
            fi
        elif [[ "$prm" == "-c" ]]; then 
            if [[ $is_help == 0 ]]; then
                is_c=$((is_c+1))
                shift
            else 
                echo "ERROR: If a key --help is used, it should be passed to the script as the only parameter"
                die
            fi
        elif [[ "$prm" == "-o" ]]; then
            echo "ERROR: invalid key -o location. It have to follow all files and after it locates new file name"
            die
        elif [[ -f "$prm" ]]; then
            if [[ $is_suf == 1 ]]; then 
                echo "ERROR: invalid input format. Suffics follows input file, not the opposite!"
                die
            fi
            if [[ $is_c == 1 ]]; then 
                break
            fi 
            if [[ $is_file == 1 ]] && [[ $is_suf == 0 ]]; then 
                echo "ERROR: there isn't suffix in input data"
                die
            fi
            FILE="$prm"
            is_file=1
            is_keys_done=1
            shift
            counter=$((counter - 1))
            break
        
        else 
            echo "ERROR: Unknown parametr: $prm"
            die
        fi
        counter=$((counter - 1))
    done
    if [[ $is_c -gt 1 ]] || [[ $is_f -gt 1 ]] || [[ $is_l -gt 1 ]]; then
        echo "Incorrect input format: double using of parameters    "
        die 
    fi
    if [[ "$1" == ".txt" ]] || [[ "$1" == ".in" ]] || [[ "$1" == ".cpp" ]]; then
        if [[ $is_file == 1 ]] && [[ $is_c == 0 ]]; then 
            is_suf=1
            SUFF="$1"
            shift
            counter=$((counter - 1))
        elif [[ $is_c == 1 ]]; then 
            echo "ERROR: you shouldn't passing the suffix using the -c key, which symbolizes taking parameters such as the suffix and the path to the file to be used for comparison" 
            echo "Incorrect input format "
            die
        else
            echo "ERROR: invalid input format. Suffics follows input file, not the opposite!"
            die
        fi
    fi
    if [[ $is_help == 1 ]] && [[ $counter == 0 ]]; then
        cat "$MN"
    else
        if [[ $is_c == 1 ]]; then 
            if [[ $counter > 0 ]]; then 
                while [[ $counter > 0 ]]; do 
                    File="$1"
                    if [[ "$File" == "--help" ]]; then
                        echo "ERROR: Key --help must be alone"
                        die
                    fi
                    if [[ $is_o == 1 ]]; then
                        NEW_FILE="$File"
                    elif [[ -f "$File" ]]; then 
                        #cat <(get_pm "config.txt")
                        #awk '{print $1}' < <(get_pm "config.txt")
                        suff="$(awk -F ':' '{print $1}' < <(get_pm "config.txt"))"
                        path_to_cmp_file="$(awk -F ':' '{print $2}' < <(get_pm "config.txt"))"
                        if [[ $(merge "$path_to_cmp_file" "$suff" "$File") != "-1" ]]; then
                            merge "$path_to_cmp_file" "$suff" "$File" >> RESULT.txt
                            if [[ $is_f == 1 ]]; then
                                echo "FILENAME THAT HAS BEEN MERGED: $File---------------------------------------------" >> RESULT.txt
                            fi    
                        fi
                        shift
                    else 
                        if [[ "$File" == "-o" ]] && [[ "$is_o" == "0" ]] && [[ "$counter" == "2" ]]; then
                            is_o=1
                            shift
                        else
                            echo "ERROR: Incorrect input format"
                            die
                        fi
                    fi
                    counter=$((counter - 1))
                done
            else 
                echo "ERROR: No input files"
                die
            fi
        elif [[ $is_c == 0 ]]; then 
            if [[ $is_file == 1 ]]; then 
                if [[ $is_suf == 0 ]]; then
                    echo "ERROR: No suffix in input data"
                    die
                else
                    if [[ $counter > 0 ]]; then 
                        while [[ $counter > 0 ]]; do 
                            if [[ "$File" == "--help" ]]; then
                                echo "ERROR: Key --help must be alone"
                                die
                            fi
                            File="$1"
                            if [[ $is_o == 1 ]]; then 
                                NEW_FILE=$File
                                shift
                            elif [[ -f "$File" ]]; then 
                                if [[ $(merge "$FILE" "$SUFF" "$File") != "-1" ]]; then
                                    merge "$FILE" "$SUFF" "$File" >> RESULT.txt
                                    if [[ $is_f == 1 ]]; then
                                        echo "FILENAME THAT HAS BEEN MERGED: $File---------------------------------------------" >> RESULT.txt
                                    fi    
                                fi
                                shift
                            else 
                                if [[ $File == "-o" ]] && [[ $counter == 1 ]]; then 
                                    echo "ERROR: Incorrect input format"
                                    die
                                elif [[ $File == "-o" ]] && [[ $is_o == 0 ]]; then
                                    is_o=1
                                    shift
                                else
                                    echo "ERROR: Incorrect input format"
                                    die
                                fi
                            fi
                            counter=$((counter - 1))
                        done
                    else
                        echo "ERROR: No input files after suffix"
                        die
                    fi
                fi
            else 
                echo "ERROR: No input comparing file"
                die
            fi
        else 
            echo "ERROR: Repeated use of the key" #-c
            die
        fi
    fi
    if [[ $is_o == 1 ]]; then
        touch "$NEW_FILE"
        cat RESULT.txt > "$NEW_FILE"
        if [[ $is_l == 1 ]]; then
            lines_n=$(wc -l RESULT.txt|awk '{print $1}')
            echo "Lines: $lines_n" >> "$NEW_FILE"
        fi
        rm RESULT.txt
    
    else
        if [[ $is_l == 1 ]]; then
            lines_n=$(wc -l RESULT.txt|awk '{print $1}')
            echo "Lines: $lines_n" >> RESULT.txt
        fi
    fi
    if [[ -f RESULT.txt ]]; then
        sz=$(wc -c RESULT.txt|awk '{print $1}')
        if [[ $sz == 0 ]]; then
            rm RESULT.txt
        fi
    fi
else
    echo "ERROR: No parameters found"
    die
fi