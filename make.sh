bpath="${1}/pmang"
mpath="${1}/mangen"

gcc "${1}/tools/manual-gen.c" "${1}/lib/errmgr.c" -o $mpath
$mpath
gcc "${1}/pmang.c" "${1}/lib/errmgr.c" "${1}/lib/proj_file.c" -O3 -o $bpath
rm $mpath