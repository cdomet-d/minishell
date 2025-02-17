#!/bin/bash

# Set output directory
output_dir="scripts/output"
mkdir -p "$output_dir"

# Determine the directory to search
if [ $# == 1 ]; then
	dir="$1"
else
	dir="."
fi

# Function to extract and format functions
extract_functions() {
	local dir="$1"
	local prevdir=""

	find "$dir" -type f -name "*.c" | while read -r file; do
		if [ -f "$file" ]; then
			dirname=$(dirname "$file")
			dirname=$(basename "$dirname")
			filename=$(basename "$file")
			functions=$(grep -oE '[a-z].*	.*[a-z].*\([^)]*\)' "$file" | grep -v "static" | tr "\n" ";" | sed 's/;/;\n/g')
			if [ -n "$functions" ]; then
				if [ "$dirname" != "$prevdir" ]; then
					printf "%.30s\n" "// $dirname ------------------------------------"
					prevdir="$dirname"
					echo
				fi
				echo "/* $filename */"
				echo "$functions"
				echo
			fi
		fi
	done
}

# Extract functions and save to output file
extract_functions "$dir" >"$output_dir/fncts"

echo "Function extraction complete. Output saved to $output_dir/fncts"
