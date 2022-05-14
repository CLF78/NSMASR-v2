# Original script: https://github.com/RoadrunnerWMC/NSMBW-Updated/blob/master/code/build_code.py
from pathlib import Path
import subprocess
import sys

# Set up region list
DEFAULT_REGION_LIST = ['P1', 'P2', 'E1', 'E2', 'J1', 'J2', 'K', 'W']
REGION_LIST = []

# Parse arguments
for arg in sys.argv[1:]:
    if arg == '--help':
        print('build.py [LIST OF REGIONS]\nAccepted values (separated by space, case insensitive): P1, P2, E1, E2, J1, J2, K, W')
        exit()
    elif arg.upper() not in DEFAULT_REGION_LIST:
        print('Invalid argument', arg, flush=True)
    else:
        REGION_LIST.append(arg.upper())

# If the resulting list is empty, compile for all regions
if not REGION_LIST:
    REGION_LIST = DEFAULT_REGION_LIST

# Set up paths
KAMEK = 'Kamek'
EXCLUDE_LIST = Path('excludes.txt')
SYMBOL_MAP = Path('externals-nsmbw.txt')
PORT_MAP = Path('versions-nsmbw.txt')
OUTPUT_DIR = Path('build')
SRC_DIR = Path.cwd()
ROOT_DIR = SRC_DIR.parent
CODEWARRIOR = Path(ROOT_DIR, 'cw', 'mwcceppc.exe')
INCLUDE_DIR = Path(ROOT_DIR, 'include')
OUTPUT_BIN_DIR = Path(ROOT_DIR, 'assets', 'game', 'Code')

# Look for source files
CPP_FILES = list(SRC_DIR.glob('**/*.cpp'))

# Filter out excluded files according to the list
if EXCLUDE_LIST.is_file():
    with EXCLUDE_LIST.open() as f:
        ex = f.read().splitlines()
    for file in CPP_FILES[:]:
        if file.name in ex:
            CPP_FILES.remove(file)

# Add wine if not on Windows
CC = [str(CODEWARRIOR)]
if sys.platform != 'win32':
    CC = ['wine'] + CC

# Set up compilation flags
CFLAGS = [
    '-i', '.',
    '-I-',
    '-i', str(INCLUDE_DIR),
    '-Cpp_exceptions', 'off',
    '-enum', 'int',
    '-fp', 'fmadd',
    '-nostdinc',
    '-O4,s',
    '-once',
    '-rostr',
    '-RTTI', 'off',
    '-sdata', '0',
    '-sdata2', '0',
    '-use_lmw_stmw', 'on']

# Set up linking flags
KAMEK_FLAGS = [
    '-dynamic',
    '-externals=' + str(SYMBOL_MAP),
    '-versions=' + str(PORT_MAP),
    '-output-kamek=' + str(Path(OUTPUT_BIN_DIR, 'code$KV$.bin'))]

# Compile the code for each region
for region in REGION_LIST:
    print(f'Compiling region {region}...', flush=True)
    O_FILES = []

    # Compile each CPP file, exit on failure
    for fp in CPP_FILES:
        print(f'Compiling {fp.name}...', flush=True)
        destpath = Path(OUTPUT_DIR, fp.relative_to(SRC_DIR)).with_suffix('.o')
        destpath.parent.mkdir(parents=True, exist_ok=True)
        out = subprocess.run(CC + CFLAGS + [f'-DREGION_{region}', '-c', '-o', str(destpath), str(fp)])
        if out.returncode != 0:
            exit()
        O_FILES.append(str(destpath))

    # Link, exit on failure
    if O_FILES:
        out = subprocess.run([str(KAMEK), *O_FILES, f'-select-version={region}'] + KAMEK_FLAGS)
        if out.returncode != 0:
            break
        print('Linked successfully!', flush=True)
