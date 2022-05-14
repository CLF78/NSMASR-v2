# Original script: https://github.com/RoadrunnerWMC/NSMBW-Updated/blob/master/code/build_code.py
from pathlib import Path
import subprocess
import sys

# Set up paths
KAMEK = 'Kamek'
EXCLUDE_LIST = Path('excludes.txt')
SYMBOL_MAP = Path('externals-nsmbw.txt')
OUTPUT_DIR = Path('build')
SRC_DIR = Path.cwd()
ROOT_DIR = SRC_DIR.parent
CODEWARRIOR = Path(ROOT_DIR, 'cw', 'mwcceppc.exe')
INCLUDE_DIR = Path(ROOT_DIR, 'include')
OUTPUT_BIN_DIR = Path(ROOT_DIR, 'assets', 'game')

# Look for source files
CPP_FILES = list(SRC_DIR.glob('**/*.cpp'))

# Filter out excluded files according to the list
if EXCLUDE_LIST.is_file():
    with EXCLUDE_LIST.open() as f:
        ex = f.read().splitlines()
    for file in CPP_FILES[:]:
        if str(file.relative_to(SRC_DIR)) in ex:
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
    '-O4',
    '-once',
    '-rostr',
    '-RTTI', 'off',
    '-sdata', '0',
    '-sdata2', '0',
    '-use_lmw_stmw', 'on']

# Set up linking flags
KAMEK_FLAGS = [
    '-static=0x800046E4',
    '-externals=' + str(SYMBOL_MAP),
    '-output-code=' + str(Path(OUTPUT_BIN_DIR, 'Loader.bin')),
    '-output-riiv=' + str(Path(OUTPUT_DIR, 'Loader.xml'))]

# Compile each CPP file, exit on failure
O_FILES = []
for fp in CPP_FILES:
    print(f'Compiling {fp.name}...', flush=True)
    destpath = Path(OUTPUT_DIR, fp.relative_to(SRC_DIR)).with_suffix('.o')
    destpath.parent.mkdir(parents=True, exist_ok=True)
    out = subprocess.run(CC + CFLAGS + ['-c', '-o', str(destpath), str(fp)])
    if out.returncode != 0:
        exit()
    O_FILES.append(str(destpath))

# Link, exit on failure
if O_FILES:
    out = subprocess.run([str(KAMEK), *O_FILES] + KAMEK_FLAGS)
    if out.returncode == 0:
        print('Linked successfully!', flush=True)
