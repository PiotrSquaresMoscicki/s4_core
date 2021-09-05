from pathlib import Path
import subprocess

hpp_files = list(Path(".").rglob("*.cpp"))
cpp_files = list(Path(".").rglob("*.cpp"))

command = "gcc -S -fverbose-asm"
for file in hpp_files:
    command += " " + file

for file in cpp_files:
    command += " " + file

print(command)
subprocess.run([command])
