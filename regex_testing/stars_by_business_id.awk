#!/usr/bin/awk -f

BEGIN{
    FS=";"
}
$3 == business_id {sum += $4; count++}
END {
    if(count != 0)
        print sum/count
}
