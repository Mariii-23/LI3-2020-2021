BEGIN {
    FS=";";
}
$9 ~ /(^|[^a-zA-Z0-9])[oO][iI]([^a-zA-Z0-9]|$)/ {print $1}
