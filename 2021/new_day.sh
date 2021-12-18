#!/bin/sh

base_dir="$(dirname "$0")"

days="$(fd '^day[0-9]+$' "$base_dir")"
last_day_path="$(tail -n1 <(echo "$days"))"
last_day="$(echo "$last_day_path" | rev | cut -c '1 2' | rev)"

next_day="$(expr 1 + "${last_day:-0}")"
[ "$next_day" -le "9" ] && next_day="0$next_day"

next_day_path="$base_dir/src/day$next_day"

stat "$next_day_path" &>/dev/null && {
    echo "$next_day already exists. Skipping.."
    exit 1
}

echo "Creating day $next_day at $next_day_path"
mkdir -pv $next_day_path

days="$(fd '^day[0-9]+$' "$base_dir")"
days_name="$(basename "$days")"

echo "Copying templates"
sed "s/\#DAY\#/$days_name/" templates/main.c > "$next_day_path/main.c"
touch "$next_day_path/sample.txt" "$next_day_path/inputs.txt"

echo "Updating Makefile"
cp -v "$base_dir/Makefile" "$base_dir/.Makefile"
cp -v "$base_dir/templates/Makefile" "$base_dir/Makefile"

sed -i "s/\# MAKE ALL DAYS$/$days_name/g" "$base_dir/Makefile"
for day in $days_name; do
    printf '
.PHONY: %s
%s:
\t$(CC) $(CFLAGS) -DPARTONE -o build/$@.1.out %s
\t$(CC) $(CFLAGS) -DPARTTWO -o build/$@.2.out %s
' "$day" "$day" "$next_day_path/main.c" "$next_day_path/main.c" >> "$base_dir/Makefile";
done

diff -u "$base_dir/.Makefile" "$base_dir/Makefile" | diff-so-fancy
