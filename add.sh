#!/bin/bash
read_dom () {
    local IFS=\>
    read -d \< ENTITY CONTENT
}

[ $# -ne 1 ] && {
    echo "add.sh requires 1 parameter only (problem ID)"
    exit 1
}
BASE_URL="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id="
PROBLEM_ID="$1"

curl -s "$BASE_URL$PROBLEM_ID" > tmp.xml

TITLE=""
COUNTER=0
AFTER_H2="FALSE"
INPUT="TRUE"
IGNORE_FIRST="TRUE"
while read_dom
do
    if [ "$ENTITY" = "title" ]
    then
        TITLE=`echo "$CONTENT" | sed "s/ | Aizu Online Judge//g"`
        if [ "$TITLE" = " | Aizu Online Judge" ]
        then
            echo "Problem $PROBLEM_ID not found"
            rm -f tmp.xml
            exit 1
        fi
    elif [ "$ENTITY" = "H2" ]
    then
        if [ "$IGNORE_FIRST" = "TRUE" ]
        then
            IGNORE_FIRST="FALSE"
        else
            AFTER_H2="TRUE"
        fi
    elif [ "$AFTER_H2" = "TRUE" ] && [ "$ENTITY" = "pre" ]
    then
        if [ "$INPUT" = "TRUE" ]
        then
            COUNTER=$((COUNTER+1))
            echo "$CONTENT" | tail -n +2 | head -n -1 > "$COUNTER.data"
            INPUT="false"
        else
            echo "$CONTENT" | tail -n +2 | head -n -1 > "$COUNTER.result"
            INPUT="TRUE"
        fi
    elif [ "$ENTITY" != "/H2" ]
    then
        AFTER_H2="FALSE"
    fi
done < tmp.xml

mkdir "$TITLE"
mv *.result *.data "$TITLE"
echo -e "#include <iostream>\n#include <vector>\n\nusing namespace std;\n\nint main () {\n}" > "$TITLE/main.cpp"

rm tmp.xml
# TITLE=`echo "$DATA" | grep "<title>" | sed "s/<title>\(.*\) | Aizu Online Judge<\/title>/\1/g"`
