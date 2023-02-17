import os
import sys

os.chdir(os.path.dirname(__file__) or '.')

exit_code = os.system(f"cmake -G \"Visual Studio 17 2022\" -S .. -B CMake-Win64-VS2022")

if exit_code != 0:
    sys.exit(exit_code)

for root, dirs, files in os.walk("CMake-Win64-VS2022"):
    for file in files:
        if file.endswith(".sln"):
            os.system(os.path.join(root, file))
            sys.exit(0)
