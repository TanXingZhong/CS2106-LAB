#!/bin/bash

# Check if we have enough arguments
if [[ $# -ne 1 ]]; then
  echo "Usage: ./process_jobs.sh <filename>"
  exit 1
fi
fail=0
success=0
total_runtime=0
rm -f jobs/summary_report.txt
for i in jobs/*; do
  rm -f $i/*.out
  rm -f $i/log.txt
  log_file="$i/log.txt"
  c_files=($i/*.c)
  in_files=($i/*.in)
  echo "Processing student job in $i" >> "$log_file"
  gcc ${c_files[@]} -o "$i/$1" 2>> "$log_file"
  if [[ $? -ne 0 ]]; then
    ((fail++))
    echo "Compilation failed for $i" >> "$log_file"
    echo "Execution time for $i: 0 seconds" >> "$log_file"
    echo -e "Execution compiled with errors in $i \n" >> "$log_file"
    continue
  else
  echo "Compilation successful for $i" >> "$log_file"
  for s in "${in_files[@]}"; do
    ((success++))
    firstString=$s
    secondString="out"
    OUTPUT="${s/in/"out"}" 
    start_time=$(date +%s.%N)
    ./"$i/$1" < "$s" > "$OUTPUT"
    end_time=$(date +%s.%N)
    execution_time=$(echo "scale=2;$end_time - $start_time" | bc | xargs printf "%.2f")
    echo "Execution time for $i: ${execution_time} seconds" >> "$log_file"
    total_runtime=$(echo "scale=2;$total_runtime + $execution_time" | bc | xargs printf "%.2f")
    #echo "Execution time for $s: $EXECUTION_TIME seconds" >> "$log_file"
    echo -e "Execution completed without errors in $i\n" >> "$log_file"
  done
  fi
done
  sys_file="jobs/summary_report.txt"
  echo "Summary Report" > "$sys_file"
  echo "Total jobs processed: $((success+fail))" >> "$sys_file"
  echo "Successful compilations: $success" >> "$sys_file"
  echo "Failed compilations: $fail" >> "$sys_file"
  echo "Total runtime of all jobs: ${total_runtime} seconds" >> "$sys_file"
  
  cat "jobs/summary_report.txt"

