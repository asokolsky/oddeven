#!/usr/bin/env bash
# Exit on error. Append "|| true" if you expect an error.
set -o errexit
# Exit on error inside any functions or subshells.
set -o errtrace
# Do not allow use of undefined vars. Use ${VAR:-} to use an undefined VAR
set -o nounset
# Catch the error in case mysqldump fails (but gzip succeeds) in `mysqldump |gzip`
set -o pipefail
# Turn on traces, useful while debugging but commented out by default
#set -o xtrace

EXE=./histogram
# during comparison ignore trailing white space(s)
CMP="diff --ignore-trailing-space -u"

# compare expected output with actual
${CMP} ./tests/test01.out.txt <(${EXE} < ./tests/test01.inp.txt)
if [ $? -eq 0 ]; then
  echo "OK"
else
  echo "Failed: $RETURN"
fi

# compare expected output with actual
${CMP} ./tests/test10.out.txt <(${EXE} < ./tests/test10.inp.txt)
if [ $? -eq 0 ]; then
  echo "OK"
else
  echo "Failed: $RETURN"
fi

# compare expected output with actual
${CMP} ./tests/test11.out.txt <(${EXE} < ./tests/test11.inp.txt)
if [ $? -eq 0 ]; then
  echo "OK"
else
  echo "Failed: $RETURN"
fi

# compare expected output with actual
${CMP} ./tests/test51.out.txt <(${EXE} < ./tests/test51.inp.txt)
if [ $? -eq 0 ]; then
  echo "OK"
else
  echo "Failed: $RETURN"
fi