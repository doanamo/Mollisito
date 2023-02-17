import os
import sys
import stat
import shutil

os.chdir(os.path.dirname(__file__) or '.')

def remove_read_only(action, name, excinfo):
    os.chmod(name, stat.S_IWRITE)
    os.remove(name)

def clone(url, branch, directory):
    if os.path.exists(directory):
        shutil.rmtree(directory, onerror=remove_read_only)

    clone_options = "--depth=1 --single-branch --config advice.detachedHead=false"
    exit_code = os.system(f"git clone {clone_options} --branch {branch} {url} {directory}")

    if exit_code != 0:
        sys.exit(exit_code)

    shutil.rmtree(os.path.join(directory, ".git"), onerror=remove_read_only)

argument = sys.argv[1]
if argument == "SDL":
    clone("https://github.com/libsdl-org/SDL.git", "release-2.26.3", "SDL")

exit_code = os.system(f"git add -f .")

if exit_code != 0:
    sys.exit(exit_code)
