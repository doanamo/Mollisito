import os
import sys
import time
import glob
import hashlib

input_dir = sys.argv[1]
output_file = sys.argv[2]

filepaths = glob.glob("**", root_dir=input_dir, recursive=True, include_hidden=True)

checksum = hashlib.sha1()
for filepath in filepaths:
    fullpath = os.path.join(input_dir, filepath)
    modtime = str(time.ctime(os.path.getmtime(fullpath)))
    checksum.update(filepath.encode())
    checksum.update(modtime.encode())

checksum_text = checksum.hexdigest()
if os.path.exists(output_file):
    with open(output_file, "r") as file:
        if checksum_text == file.read():
            sys.exit(0)

file = open(output_file, "w")
file.write(checksum_text)
