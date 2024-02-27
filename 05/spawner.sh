# Bash script
#
# 049 - Operating Systems
# Quiz 5
#
# Kapetanios Antonios, 10417
#
# January 2024

#!/bin/bash
spawner() {

	# Check number of arguments
	if [ $# -ne 3 ]; then
		return 2
	else
		memoryInKB=$1
		timeoutInSec=$2
		binaryName=$3

		# Check if binary exists
		if [ ! -f $binaryName ]; then
			return 3
		# Check if binary has execute permissions
		elif [ ! -x $binaryName ]; then
			return 4
		else
			# Run the binary with a timeout and memory limit
			output=$(timeout $timeoutInSec sh -c "ulimit -v $memoryInKB; ./$binaryName" 2>&1)
		exit_code=$?
		echo $exit_code
		if [ $exit_code -eq 124 ]; then
			# timeout
			return 5
		elif [ $exit_code -eq 137 ] || [ $exit_code -eq 139 ]; then
			# memory limit
			return 1
		else
			return 0
		fi
		fi
	fi
}

# Call the spawner function with all arguments given to the script
spawner "$@"
