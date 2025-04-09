# Input is processed line by line.
# Each line is split into fields based on whitespace.
# The first field is $1, the second is $2, and so on.

# Each rule should be on a new line.
$1 == "banana" { print }
$2 > 4 { print $2 }