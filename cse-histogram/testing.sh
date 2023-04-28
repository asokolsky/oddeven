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

for inp_file in ./tests/*.inp.txt; do
  #echo "$inp_file"
  out_file=`echo ${inp_file} | sed 's/inp/out/'`
  #echo "$out_file"

  # compare expected output with actual
  echo -n "Runninging: ${CMP} ${out_file} <(${EXE} < ${inp_file} ... "
  ${CMP} "${out_file}" <(${EXE} < "${inp_file}")
  ec=$?
  if [ $ec -eq 0 ]; then
    echo "OK"
  else
    echo "Failed: $ec"
  fi
done
