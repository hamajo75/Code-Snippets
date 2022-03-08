#!/bin/sh

# ------- sed ---------------------------------------
# Options
# -i                            - in place replacement

# Regular Expressions
# 's/RE/Substitution/gI'

# I                             - ignore case
# g                             - global replacement
# escape \(  \) for capturing groups
# escape \"  \" for literal ""
# capture groups: \1 \2 etc.

namespace=wcep::alarm_and_error_state
namespace=$namespace::MessageHeader

sed -i 's/#include "json.hpp"/#include "common\/message_framework\/json\/messages.h"/' $1

sed -i "s/$namespace MessageHeader;/messaging::json::MessageHeader MessageHeader;/" $1
sed -i "s/x.MessageHeader = j.at(\"messageHeader\").get<$namespace>/x.MessageHeader = j.at(\"messageHeader\").get<messaging::json::MessageHeader>/" $1

sed -i 's/namespace detail {//' $1
# remove last "}" in the file
sed -i '$ s/.$//' $1

# capture groups
echo "foobarbaz" | sed 's/^foo\(.*\)baz$/\1/'

# ------------ perl -------------------------------------------------------------------------------------
# sed can't handle '\n', for complicated stuff use perl
perl -0777 -i.original -pe 's/,\n.*\"enum\": \[(\n.*,)*\n.*\n.*\]//g' definitions.global.1.0.schema.json
# -0777            slurp whole file (performance)
# -pi -e           replace in place
# -i.original      backup the file
# -pe              output to stdout