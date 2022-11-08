#! /usr/bin/env bash

# $1 Start Range for Slides
# $2 End Range for Slides
# $3 Week

for n in {$1..$2}
    echo "\![Slides $n](week-$n.jpg)" >> "content/week$3/slides/README.md"
done
