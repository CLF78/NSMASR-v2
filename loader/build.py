#!/usr/bin/env python3

# Build script for code loader.
# Original: https://github.com/RoadrunnerWMC/NSMBW-Updated/blob/efdfea0b4ff29366b19d49b39fcf4e7ea148981c/code/build_code.py

from pathlib import Path
import subprocess
import sys

# Hook address
LOAD_ADDR = 0x800046E4

# Compilation folders
SRC_DIR = Path(__file__).parent
ROOT_DIR = SRC_DIR.parent
KAMEK = 'Kamek' # Kamek assumes the program is on PATH!
EXCLUDE_FILE = Path(SRC_DIR, 'excludes.txt')
SYMBOL_MAP = Path(SRC_DIR, 'externals-nsmbw.txt')
OUTPUT_DIR = Path(SRC_DIR, 'build')
CODEWARRIOR = Path(ROOT_DIR, 'cw', 'mwcceppc.exe')
INCLUDE_DIR = Path(ROOT_DIR, 'include')
OUTPUT_BIN_DIR = Path(ROOT_DIR, 'assets', 'game')

# Add wine if not on Windows
CC = [] if sys.platform == 'win32' else ['wine']
CC.append(CODEWARRIOR)

# Compilation flags
CFLAGS = [
    '-i', '.',
    '-I-',
    '-i', INCLUDE_DIR,
    '-Cpp_exceptions', 'off',
    '-enum', 'int',
    '-fp', 'fmadd',
    '-gccext', 'on',
    '-msext', 'on',
    '-nostdinc',
    '-O4',
    '-once',
    '-pragma', '"cpp_extensions on"',
    '-pragma', '"cpp1x on"',
    '-pragma', '"gprfloatcopy on"',
    '-pragma', '"no_static_dtors on"',
    '-rostr',
    '-RTTI', 'off',
    '-schedule', 'on',
    '-sdata', '0',
    '-sdata2', '0',
    '-use_lmw_stmw', 'on']

# Linking flags
KAMEK_FLAGS = [
    f'-static={hex(LOAD_ADDR)}',
    f'-externals={SYMBOL_MAP}',
    f'-output-code={Path(OUTPUT_BIN_DIR, "Loader.bin")}',
    f'-output-riiv={Path(OUTPUT_DIR, "Loader.xml")}']


# Print helper function so output isn't all over the place when redirecting it
def printFlush(*args, **kwargs):
	kwargs['flush'] = True
	print(*args, **kwargs)


# Make output folder
OUTPUT_BIN_DIR.mkdir(exist_ok=True)

# Look for source files
CPP_FILES = set(SRC_DIR.rglob('*.cpp'))

# Filter out excluded files according to the list
if EXCLUDE_FILE.is_file():
    with EXCLUDE_FILE.open() as f:
        ex = set(map(lambda x: Path(SRC_DIR, x), f.read().splitlines()))
        CPP_FILES -= ex

# Compile each CPP file, exit on failure
O_FILES = []
for fp in CPP_FILES:
    printFlush('Compiling', fp.name, end='...\n')

    # Make its destination path since CW isn't able to for some reason
    destpath = Path(OUTPUT_DIR, fp.relative_to(SRC_DIR)).with_suffix('.o')
    destpath.parent.mkdir(parents=True, exist_ok=True)

    # Run CW, exit on failure
    out = subprocess.run([*CC, *CFLAGS, '-c', '-o', destpath, fp])
    if out.returncode != 0:
        exit()

    # Else append successful result
    O_FILES.append(destpath)

# Link, exit on failure
if O_FILES:
    out = subprocess.run([KAMEK, *O_FILES, *KAMEK_FLAGS])
    if out.returncode == 0:
        printFlush('Linked successfully!')
