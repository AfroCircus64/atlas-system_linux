#!/usr/bin/python3
"""script that finds and replaces a string in the heap of a running process"""

import sys


def arg_parser():
    """Parse cmd line args"""

    if len(sys.argv) < 3:
        print("Usage: read_write_heap.py pid s_string r_string")
        exit(1)
    
    pid = sys.argv[1]
    s_string = sys.argv[2]

    if len(sys.argv) == 4:
        r_string = sys.argv[3]
    else:
        r_string = ""

    
    return pid, s_string, r_string



def get_address(pid):
    """Gets the memory address"""

    map_file = "/proc/{}/maps".format(pid)

    try:
        with open(map_file) as file:
            for line in file:
                if "[heap]" in line:
                    range = line.split()[0]

                    start, end = range.split('-')

                    start = int(start, 16)

                    end = int(end, 16)

                    return start, end

    except FileNotFoundError:
        print("/proc/{}/maps: not found".format(pid))
        exit(1)



def replace_str(
                pid,
                h_start,
                h_end,
                s_string,
                r_string):
    """Replaces s_string with r_string"""

    mem_file = "/proc/{}/mem".format(pid)

    if len(r_string) > len(s_string):
        print("Error: Strings are different lengths")
        exit(1)

    try:
        with open(mem_file, 'rb+') as file:
            file.seek(h_start)

            h_size = h_end - h_start

            h_read = file.read(h_size)

            s_bytes = s_string.encode('ascii')
            w_bytes = r_string.encode('ascii')

            res = h_read.find(s_bytes)

            if res == -1:
                print("{} not found in heap".format(s_string))
                exit(1)
            
            file.seek(h_start + res)
            file.write(w_bytes)
    except PermissionError:
        print("{}: Permission Denied".format(mem_file))
        exit(1)
    except FileNotFoundError:
        print("Process: {} not found".format(pid))
        exit(1)
    except Exception as e:
        print("Error: {}".format(e))
        exit(1)


if __name__ == "__main__":
    """Entry point"""
    pid, s_string, r_string = arg_parser()
    h_start, h_end = get_address(pid)
    replace_str(
                pid,
                h_start,
                h_end,
                s_string,
                r_string)
