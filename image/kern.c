#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

struct bpf_map_def SEC("maps") progs = {
	.type = BPF_MAP_TYPE_PROG_ARRAY,
	.key_size = sizeof(__u32),
	.value_size = sizeof(__u32),
	.max_entries = 35,
};

struct bpf_map_def SEC("maps") count = {
	.type = BPF_MAP_TYPE_ARRAY,
	.key_size = sizeof(__u32),
	.value_size = sizeof(__u32),
	.max_entries = 2,
};

#define PROG(X) SEC("action/prog" #X)			\
int bpf_prog ## X(void *ctx) {			\
	bpf_tail_call(ctx, &progs, X+1);	\
	return 0;				\
}

SEC("action/prog33")
int bpf_prog33(void *ctx) {
	__u32 zero = 0;
	__u32 one = 1;
	bpf_map_update_elem(&count, &zero, &one, 0);
	bpf_tail_call(ctx, &progs, 34);
	return 0;
}

SEC("action/prog34")
int bpf_prog34(void *ctx) {
        __u32 one = 1;
        bpf_map_update_elem(&count, &one, &one, 0);
	return 0;
}

PROG(0)
PROG(1)
PROG(2)
PROG(3)
PROG(4)
PROG(5)
PROG(6)
PROG(7)
PROG(8)
PROG(9)
PROG(10)
PROG(11)
PROG(12)
PROG(13)
PROG(14)
PROG(15)
PROG(16)
PROG(17)
PROG(18)
PROG(19)
PROG(20)
PROG(21)
PROG(22)
PROG(23)
PROG(24)
PROG(25)
PROG(26)
PROG(27)
PROG(28)
PROG(29)
PROG(30)
PROG(31)
PROG(32)
