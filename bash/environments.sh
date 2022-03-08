#!/bin/bash

# start cmd in new environment with special settings

env -C /home/jha/Development/Viza/mee066-esw-intercom-apps/build_target -i bash --norc --noprofile
source /usr/local/oecore-x86_64/environment-setup-cortexa7t2hf-neon-vfpv4-me-linux-gnueabi            # this doesn't work

# printenv       see all variables