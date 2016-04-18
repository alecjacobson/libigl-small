#!/bin/bash
# Usage:
#   cd $LIBIGL/include/igl
#   make -C [your_project] 2>&1 | ../../scripts/autoexplicit.sh


# process input line by line
while read line; do
  if ! echo "$line" | grep -q "^\".*\", referenced from:$"
  then 
    # undefined symbol line not found
    continue
  fi
  symbol=`echo "$line" | sed -e "s/^\"\(.*\)\", referenced from:$/\1/"`
  #echo "symbol = $symbol"
  filename=`echo "$symbol" | perl -pe "s#.*?igl::([A-z0-9_:]*).*$'$'#\1#"`
  filename=`echo "$filename" | sed -e "s/::/\//g"`
  #echo "filename = $filename"
  cpp="$LIBIGL/include/igl/$filename.cpp"
  # append .cpp and check that file exists
  if [ ! -e "$cpp" ]
  then
    echo "Warning: $cpp does not exist, skipping ..."
    continue
  fi

  if ! grep -q "^\/\/ Explicit template specialization*$" "$cpp"
  then
    echo "Warning: skipping $cpp because it does not match ^\/\/ Explicit template specialization*$ "
    continue;
  fi

  before=`sed '/^\/\/ Explicit template specialization$/q' "$cpp"`;
  #echo "before = $before"
  after=`sed '1,/^\/\/ Explicit template specialization$/d' $cpp`;
  #echo "after = $after"
  explicit="template $symbol;"
  #echo "$explicit"
  if grep -F "$explicit" "$cpp"
  then
    echo "Error: $cpp already contains $explicit"
    echo "       Recompile igl static lib, recompile your project, and try again."
    continue
  fi
  echo "$before" > "$cpp"
  echo "// generated by autoexplicit.sh" >> "$cpp"
  echo "$explicit" >> "$cpp"
  echo "$after" >> "$cpp"

done
