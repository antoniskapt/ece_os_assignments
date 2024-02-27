# cleanup.fish
#
# Kapetanios Antonios 10417
# November 2023
#
# 049 - OS
# hw assignment 2
# ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# Make sure to source the file `cleanup.fish`.
# source path/to/cleanup.fish
# ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

# Description: Function to cleanup files that have not been accessed for more than a specific amount of days.
# Usage: cleanup [OPTIONS]
#   Options:
#       --target_directory PATH/TO/DIRECTORY    Specify the parent directory to be searched.
#       --days_inactive INTEGER                 Specify the minimum number of days of inactivity that
#       --recursive                             Search all the subdirectories.
#       --excluded_files_dirs TERM1!TERM2!..    Filenames and or directories containing any of the
#                                               specified terms will be excluded. Patterns are
#                                               seperated by !
#       --sort_type SORT                        Sorts the files by size. SORT can be either asc or desc.
#       --confirmation                          Confirm the deletion of each file.
#       --dry_run                               Prints the files to be deleted to the standard output
#                                               but does not perform the actual deletion. It ovverides
#                                               --confirmation.
function cleanup -d "Function to cleanup files that have not been accessed for more than a specific amount of days."
	# set default values
	set target_directory /home
	set days_inactive 60
	set recursive false
	set dry_run false
	set excluded_files_dirs ""
	set sort_type asc
	set confirmation false

	set counter 1
	# Parse arguments using flags
	while test $counter -le (count $argv)
		switch $argv[$counter]
			case --help
				echo "Function to cleanup files that have not been accessed for more than a specific amount of days."
				echo ""
				echo "Usage: cleanup [OPTIONS]"
				echo "    Options:"
				echo "        --target_directory PATH/TO/DIRECTORY    Specify the parent directory to be searched."
				echo "        --days_inactive INTEGER                 Specify the minimum number of days of inactivity."
				echo "        --recursive                             Search all the subdirectories."
				echo "        --excluded_files_dirs TERM1!TERM2!...   Filenames and or directories to be excluded."
				echo "        --sort_type SORT                        Sort files by size. SORT: asc or desc."
				echo "        --confirmation                          Confirm the deletion of each file."
				echo "        --dry_run                               Print files to be deleted without deletion. It"
				echo "                                                overides --confirmation."
				echo "        --help                                  Prints this menu to the standard output. It"
				echo "                                                overides all other options."
				return 0
			case --target_directory
				set target_directory $argv[(math $counter + 1)]
				if not test -d $target_directory
					echo -e "$target_directory is not a valid directory.\n"
					return 1
				end
				set counter (math $counter + 1)
			case --days_inactive
				set days_inactive $argv[(math $counter + 1)]
				set counter (math $counter + 1)
			case --recursive
				set recursive true
			case --dry_run
				set dry_run true
			case --excluded_files_dirs
				set excluded_files_dirs $argv[(math $counter + 1)]
				set counter (math $counter + 1)
			case --sort_type
				set sort_type $argv[(math $counter + 1)]
				if not test $sort_type = asc -o $sort_type = desc
					echo -e "sort_type must be either 'asc' or 'desc'.\n"
					return 1
				end
				set counter (math $counter + 1)
			case --confirmation
				set confirmation true
			case '*'
				echo "Unknown flag: $argv[$counter]"
				return 1
		end
		set counter (math $counter + 1)
	end

	# internal flags
	set sort_flag n
	if [ $sort_type = desc ]
		set sort_flag rn
	end

	set res ''
	# delete the first empty entry
	if test (count $res) -gt 0
		set res (string match -v $res[1] $res)
	end

	if [ $recursive = true ]
		for file in (find $target_directory -type f -atime +$days_inactive | sort -$sort_flag)
			if test -n "$file"
				set -a res $file
			end
		end
	else
		for file in (find $target_directory -maxdepth 1 -type f -atime +$days_inactive | sort -$sort_flag)
			if test -n "$file"
				set -a res $file
			end
		end
	end

	set x ''
	# delete the first empty entry
	if test (count $x) -gt 0
		set x (string match -v $x[1] $x)
	end
	if [ -n "$excluded_files_dirs" ]
		set excluded_files_dirs (string split "!" "$excluded_files_dirs")
		for item in $res
			set add_item true
			for excluded in $excluded_files_dirs
				if string match -q "*$excluded*" $item
					set add_item false
					break
				end
			end

			if $add_item
				set -a x $item
			end
		end
		set res $x
		set -e x
	else
		echo "No files or directories to be excluded were specified."
	end

	# Dry run mode prints the files to
	# the standard output and terminates.
	set i 1
	if [ $dry_run = true ]
		echo "Dry run mode. The following files have been found."
		for file in $res
			echo -e $i\)\t\t(stat -c %x $file)\t\t$file
			set i (math $i+1)
		end
		return 2
	end

	# Delete files
	for file in $res
		if [ $confirmation = true ]
			echo "Delete $file? (yes/no): "
			read -l response

			# Check for valid user input
			if test "$response" = yes
				rm -i $file
				if test $status -eq 0
					echo "Deleted $file"
				else
					echo "Deletion failed or was canceled for $file"
				end
			else
				echo "Deletion canceled for $file"
			end
			echo ""
		else
			echo "Deleting $file."
			rm -f $file
		end
	end

	set -e res
	return 0
end
