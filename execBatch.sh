#!/usr/bin/env bash

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$(pwd)"

MAX_PROCS=4
EXEC="./GA"
NUM_EXECS=30
GA_CONF="gaConf1.gaconf"
REPORTS_PATH="reports/"
STDCOUT_FILE="coutLogs/stdcout"
PROBLEM_LIST="$(find . -name "*.ttp")"

IFS=$'\n' arr_problem_list=($PROBLEM_LIST)

for (( i=0; i<${#arr_problem_list[@]}; )); do
    for (( j=0; j<$MAX_PROCS; ++j )); do
        ttp_name=$(basename ${arr_problem_list[i]})
        $EXEC ${arr_problem_list[i]} $GA_CONF $NUM_EXECS $REPORTS_PATH "${STDCOUT_FILE}__${ttp_name}.log" &

        i=$i+1
        if [[ i -eq ${#arr_problem_list[@]} ]]; then
            break
        fi
    done

    for job in `jobs -p`
    do
        wait $job
    done
done

wait

# GA instances/kroA100-ttp/kroA100_n990_uncorr_10.ttp gaConf1.gaconf 30 reports/ stdcout__kroA100_n990_uncorr_10.ttp.log
