#!/bin/sh

root=`dirname "${0}"`

find "${root}/../" '(' -name 'cmake*' \
            -or -name 'CMakeCache*' \
            -or -name 'CMakeFiles' \
            -or -name 'Makefile' \
            -or -name '*.o' \
            -or -name '.*.swp' ')' -exec echo ' * Removing `' '{}' '`' \; -exec rm -rf '{}' \;
