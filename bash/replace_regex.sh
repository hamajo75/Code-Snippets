#!/bin/sh

# g - global replacement
# escape (), ""

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