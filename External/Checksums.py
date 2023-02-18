import os
import sys
import time
import glob
import hashlib

os.chdir(os.path.dirname(__file__) or '.')

output_dir = sys.argv[1]
os.makedirs(output_dir, exist_ok=True)

for dir in os.listdir("."):
    if not os.path.isdir(dir):
        continue

    filepaths = glob.glob("**", root_dir=dir, recursive=True, include_hidden=True)

    checksum = hashlib.sha1()
    for filepath in filepaths:
        fullpath = os.path.join(dir, filepath)
        modtime = str(time.ctime(os.path.getmtime(fullpath)))
        checksum.update(filepath.encode())
        checksum.update(modtime.encode())

    checksum_text = checksum.hexdigest()
    checksum_filepath = os.path.join(output_dir, f"{dir}.txt")
    if os.path.exists(checksum_filepath):
        with open(checksum_filepath, "r") as file:
            if checksum_text == file.read():
                continue

    file = open(checksum_filepath, "w")
    file.write(checksum_text)
