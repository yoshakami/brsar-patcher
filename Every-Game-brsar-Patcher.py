# algorithm made and found by yosh, simply drag and drop your brsar on this python script, or type all of this in a terminal -> "[DND] brsar patcher.py" "my file.brsar"
import sys
import os


def patch_brsar(file):
    brstm_max_size = b"\x7f\xff\xff\xff"  # above is negative values (so sounds won't play) as it's a signed hex float
    cursor = patched_num = 0
    max_offset = 0x1f7b00  # Super Smash Bros Brawl farest entry
    with open(file, "r+b") as brsar:
        if os.path.getsize(file) > 500000000:
            max_offset = 0x6d9500  # Dragon Ball Z Budokai Tenkaichi 2 has a 1 GB brsar with entries really far
        while cursor < max_offset:
            cursor += 1
            brsar.seek(cursor)
            brstm = brsar.read(6)  # reads 6 bytes and look if it's .brstm
            if brstm == b'.brstm':
                cursor_save = cursor
                patched_num += 1
                while brstm != b"\xff\xff\xff\xff":
                    cursor -= 1
                    brsar.seek(cursor)
                    brstm = brsar.read(4)
                cursor -= 8  # always FF FF FF FF eight bytes after the brstm max size
                brsar.seek(cursor)  # seek to the brstm max size offset
                brsar.write(brstm_max_size)  # write 7F FF FF FF which is 2 GB
                cursor = cursor_save
        return f"patched {patched_num} brstm to their max size! (2GB)"


if len(sys.argv) < 2:  # if the brsar is not given
    input("please add your filename as argument when launching this script\nit's exactly what you make when doing drag and drop\npress enter to quit...\n")
    exit()  # exits the program
print('Finding brstm links, please wait...\n remember that you can still do something else while this script runs :)')
print(patch_brsar(sys.argv[1]))
input("Press Enter to exit...")
