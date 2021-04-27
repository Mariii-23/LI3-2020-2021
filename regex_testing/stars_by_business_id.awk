#!/usr/bin/awk -f

BEGIN{
    FS=";"
}
$3 == business_id {sum += $4; count++}
END {
    print sum/count
}
