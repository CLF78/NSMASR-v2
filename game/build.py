#!/usr/bin/env python3

# Build script for game code.
# Original: https://github.com/RoadrunnerWMC/NSMBW-Updated/blob/master/code/build_code.py

from pathlib import Path
import subprocess
import sys

# Region list
DEFAULT_REGION_LIST = ['P1', 'P2', 'E1', 'E2', 'J1', 'J2', 'K', 'W']
REGION_LIST = []

# Compilation folders
SRC_DIR = Path(__file__).parent
ROOT_DIR = SRC_DIR.parent
KAMEK = 'Kamek' # Kamek assumes the program is on PATH!
EXCLUDE_FILE = Path(SRC_DIR, 'excludes.txt')
SYMBOL_MAP = Path(SRC_DIR, 'externals-nsmbw.txt')
PORT_MAP = Path(SRC_DIR, 'versions-nsmbw.txt')
OUTPUT_DIR = Path(SRC_DIR, 'build')
CODEWARRIOR = Path(ROOT_DIR, 'cw', 'mwcceppc.exe')
INCLUDE_DIR = Path(ROOT_DIR, 'include')
OUTPUT_BIN_DIR = Path(ROOT_DIR, 'assets', 'game', 'Code')

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
    '-O4,s',
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
    '-dynamic',
    f'-externals={SYMBOL_MAP}',
    f'-versions={PORT_MAP}',
    f'-output-kamek={Path(OUTPUT_BIN_DIR, "code$KV$.bin")}']


# Print helper function so output isn't all over the place when redirecting it
def printFlush(*args, **kwargs):
	kwargs['flush'] = True
	print(*args, **kwargs)

# Parse arguments
for arg in sys.argv[1:]:
    if arg == '--help' or arg == '-h':
        printFlush('build.py [LIST OF REGIONS]\nAccepted values (separated by space, case insensitive): P1, P2, E1, E2, J1, J2, K, W, ALL')
        exit()
    elif arg.upper() == 'ALL':
        REGION_LIST = DEFAULT_REGION_LIST
    elif arg.upper() not in DEFAULT_REGION_LIST:
        printFlush('Invalid argument', arg)
    else:
        REGION_LIST.append(arg.upper())

# If the resulting list is empty, bail
if not REGION_LIST:
    printFlush('No valid regions provided!')
    exit()

# Make output folder
OUTPUT_BIN_DIR.mkdir(exist_ok=True)

# Look for source files
CPP_FILES = set(SRC_DIR.rglob('*.cpp'))

# Filter out excluded files according to the list
if EXCLUDE_FILE.is_file():
    with EXCLUDE_FILE.open() as f:
        ex = set(map(lambda x: Path(SRC_DIR, x), f.read().splitlines()))
        CPP_FILES -= ex

# Compile the code for each region
for region in REGION_LIST:
    printFlush('Compiling region', region, end='...\n')
    O_FILES = []

    # Compile each CPP file, exit on failure
    for fp in CPP_FILES:
        printFlush('Compiling', fp.name, end='...\n')

        # Make its destination path since CW isn't able to for some reason
        destpath = Path(OUTPUT_DIR, fp.relative_to(SRC_DIR)).with_suffix('.o')
        destpath.parent.mkdir(parents=True, exist_ok=True)

        # Run CW, exit on failure
        out = subprocess.run([*CC, *CFLAGS, f'-DREGION_{region}', '-c', '-o', destpath, fp])
        if out.returncode != 0:
            exit()

        # Else append successful result
        O_FILES.append(destpath)

    # Link, exit on failure
    if O_FILES:
        out = subprocess.run([KAMEK, *O_FILES, f'-select-version={region}', *KAMEK_FLAGS])
        if out.returncode != 0:
            break
        printFlush('Linked successfully!')
