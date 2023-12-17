#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
MAGENTA="\033[0;35m"
CYAN="\033[0;36m"
WHITE="\033[0;37m"
NC="\033[0m"

pname="GET NEXT LINE"
puser="VZURERA-"

start=$(date +%s%N)
clear
printf "\n$YELLOW\t$pname\t\t\t$MAGENTA $puser\n$NC"
printf "$YELLOW───────────────────────────────────────────────────────────────$CYAN\n\n"

norma=$(norminette .)
if [[ $norma == *"Error"* ]]; then
	printf " Norminette: $RED\tKO$NC\n"
else
    printf " Norminette: $GREEN\tOK$NC\n"
fi

printf "$NC\n"
BUFFER_SIZES=(1 5 500 2000 1000000)
# cp ./gnl_tester/test.c test.c
echo "" > ~/francinette/tests/get_next_line/gnlTester/files/1byte
echo "f" > ~/francinette/tests/get_next_line/gnlTester/files/2byte
max_length=0
for size in "${BUFFER_SIZES[@]}"; do
    current_length=${#size}
    if (( current_length > max_length )); then max_length=$current_length; fi
done

for size in "${BUFFER_SIZES[@]}"
do
    padding=$(( max_length - ${#size} ))
    printf "BUFFER_SIZE = %-${max_length}s" "$size"
    if gcc -Wall -Wextra -Werror -g -DBUFFER_SIZE=$size gnl_test.c get_next_line.c get_next_line_utils.c -o test >/dev/null 2>&1; then
        ./test
    else
		printf "\t$RED NO COMPILE$NC\n"
    fi
done
printf "$CYAN\n"

memoryinfo=$(valgrind -s ./test 2>&1 | awk '/HEAP SUMMARY/,/ERROR SUMMARY/' | sed 's/^==[0-9]*==//')

if [[ $memoryinfo == *"All heap blocks were freed -- no leaks are possible"* ]]; then
    printf "\t\t\t$GREEN NO MEMORY LEAKS\n"
else
    printf "$CYAN$memoryinfo\n"
	printf "\n\t\t\t$RED MEMORY LEAKS\n"
fi

# rm -f ./test.c
rm -f ./test

printf "$YELLOW───────────────────────────────────────────────────────────────$NC\n"
end=$(date +%s%N)
printf "{$CYAN}The test took $(awk -v d=$((end-start)) 'BEGIN {printf "%.2f", d / 1000000000}') seconds\n\n$NC"

while true; do
    read -p "Would you like to run the tests for Francinette (Paco)? [Y/n]: " response
    response=$(echo "$response" | tr '[:upper:]' '[:lower:]')
    if [ -z "$response" ]; then response="yes"; fi
    case "$response" in
        yes | y)
            printf "\n"
            ~/francinette/tester.sh --ignore-norm
            read -p "Would you like to run the tests for Francinette (Paco) in strict mode? [Y/n]: " response
            response=$(echo "$response" | tr '[:upper:]' '[:lower:]')
            if [ -z "$response" ]; then response="yes"; fi
            case "$response" in
                yes | y)
                    printf "\n"
                    ~/francinette/tester.sh --ignore-norm -s
                    printf "\n$YELLOW Remember that time-out failures in this project are normal\nand are caused by the way Francinette handles malloc assignments\n\n\n$NC"
                    break
                    ;;
                no | n)
                    exit
                    ;;
                *)
                    printf "Invalid response. Please answer 'yes' or 'no'"
                    ;;
            esac
            break
            ;;
        no | n)
            exit
            ;;
        *)
            printf "Invalid response. Please answer 'yes' or 'no'"
            ;;
    esac
done