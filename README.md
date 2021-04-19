# Benchmark Tools for BPF Tail Calls



This repository contains an Ansible playbook and the sources of a Docker image to execute BPF tail call benchmarks on remote servers. 
It measures the cost of tail call chains of varying lengths using [`kern.c`](image/kern.c) as the BPF program.
The Docker image is available at `docker.io/pchaigno/tail-calls:v1.0`.

Results produced by these tools are presented at https://pchaigno.github.io/ebpf/2021/03/22/cost-bpf-tail-calls.html.

## Requirements

The Ansible playbook was developed to work with [Packet](https://www.packet.com/)'s Ubuntu 20.04 and may not work with other distributions.
Only Ansible and the kernel debian packages are required on the machine used to run the playbook.


## Running the Benchmark

### Populate hosts.ini

You need to complete `hosts.ini` with the IP addresses of your benchmark servers, a string matching the kernel debian package to install, and the file where results should be written.
For example:
```
147.75.100.157 kernel=5.10.0-retpoline boot_order=0 output=results-5.10-retpoline.txt ansible_user=root ansible_python_interpreter=/usr/bin/python3
147.75.100.157 kernel=5.4.0-retpoline boot_order=2 output=results-5.4-retpoline.txt ansible_user=root ansible_python_interpreter=/usr/bin/python3
```

The `kernel` string will be used in the file glob `linux-*[kernel]*.deb` to select the debian packages to install.
`boot_order` should be set to `0` on kernels 5.5+ and `2` on others.

### Execute the Ansible Playbook

You can then execute `ansible-playbook`:
```shell
ansible-playbook -v -i hosts.ini -e nb_runs=100 -e nb_measures=10 -e result_dir=/home/paul/pchaigno.github.io playbook.yaml
```
The Ansible tasks are executed on all servers in parallel without waiting for other servers.

- `result_dir` is the directory where the `output` result files mentioned above will be saved.
- `nb_runs` corresponds to the number of time each BPF program will be executed in the kernel.
Only the mean of those `nb_runs` executions will be reported.
- `nb_measures` corresponds to the number of times `BPF_PROG_TEST_RUN` will be called.
With the above parameters, each tail call chain will run a thousand times and 10 means will be reported. 


## License

This project is under [MIT license](LICENSE).
