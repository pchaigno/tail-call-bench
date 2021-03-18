#!/bin/bash
set -e

nb_tc=$1
repeat=$2
overheads=()

clang -O2 -Wall -target bpf -I/usr/include/x86_64-linux-gnu -c -o kern.o kern.c
sudo sh -c 'rm /sys/fs/bpf/action_prog* /sys/fs/bpf/map_progs 2>/dev/null' || true
sleep 0.1
sudo bpftool prog loadall kern.o /sys/fs/bpf/
map_id=$(sudo bpftool map show -j | jq '.[] | select( .type == "prog_array" and .owner_prog_type == "sched_act" ) | .id')
sudo bpftool map pin id $map_id /sys/fs/bpf/map_progs
# echo -n "[ "
for (( i=0; i<=$nb_tc; i++ )); do
	# echo -n "$i, "
	for (( j=1; j<=$i; j++ )); do
		sudo bpftool map update pinned /sys/fs/bpf/map_progs key $i 0 0 0 value pinned "/sys/fs/bpf/action_prog$i"
	done
	overheads+=( $(sudo bpftool prog run pinned /sys/fs/bpf/action_prog0 data_in data.bin repeat $repeat | grep -oP "(?<=: )\d+(?=ns)") )
done
# echo "]"

echo -n "[ "
for k in ${overheads[@]}; do
	echo -n "$k, "
done
echo "]"
