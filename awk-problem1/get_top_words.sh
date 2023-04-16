#/usr/bin/bash

# sort the stop words and store these into temp directory
#cat ./stopwords| tr -d '\r'| sort > /tmp/stop-words-sorted
# tr -d '\r' removes invisible CR present in DOS text files

#declare -A stop_words
#stop_words=$(cat ./stopwords)
#for stop_word in $stop_words ;
#  do
#    echo $stop_word
#  done

# tokenize the input, one token per line
cat sample.txt| tr -d ',.;:!?"\r'| tr '[:space:]' '\n'|grep -v '^\s*$'|tr '[:upper:]' '[:lower:]'| sort | uniq -c| sort -bnr> /tmp/input-sorted-unique-counts
# tr -d ',.;:!?"\r' - discard these chars
# tr '[:space:]' '\n' - replace these chars with \n
# grep -v '^\s*$' - drop empty lines
# tr '[:upper:]' '[:lower:]' - convert to lower case
# sort - sort the lines
# uniq -c - print count uniques
# sort -bnr - sorts in numeric reverse order while ignoring whitespace


k=3

# https://www.xmodulo.com/key-value-dictionary-bash.html
declare -A occurences
# Set space as the delimiter
IFS=' '

i=0
while read line; do
    # Read the split words into an array based on space delimiter
    read -ra val_word <<< $line
    n="${val_word[0]}"
    word="${val_word[1]}"
    if grep -q -w $word ./stopwords ; then
        #echo "stopword: ${word}"
        :
    else
        #echo "adding ${word}"
        occurences["${word}"]="${n}"
        ((i++))
        if [[ "$i" == "$k" ]] ; then
            break
        fi
    fi
    #echo "i=${i}"

done < /tmp/input-sorted-unique-counts

#echo $occurences

for key in "${!occurences[@]}"; do
    #echo "== $key ${occurences[$key]}"
    echo "$key"
done

# Known problem:
#  1. words in with the same occurance are printed in the reverse sorted order
#  2. Clarification needed:
#       top 3 most used words - what to do if there are 4 words with the same
#       occurance rate?
