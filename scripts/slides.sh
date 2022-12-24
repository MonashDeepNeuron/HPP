#! /usr/bin/env bash

# $1 Start Range for Slides
# $2 End Range for Slides
# $3 Part

SLIDES="content/part$3/slides"

mkdir -p "$SLIDES/imgs"

pdftoppm -png -f $1 -l $2 "$SLIDES/hpp_part$3.pdf" "$SLIDES/imgs/hpp_part$3"

echo "" > "$SLIDES/README.md"
echo -e "# Slides\n" > "$SLIDES/README.md"

for n in $(eval echo {$1..$2})
do
    echo -e "![Slides $n](/$SLIDES/imgs/hpp_part$3-$n.jpg)" >> "$SLIDES/README.md"
done
