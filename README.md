# Newer Super Mario All-Stars Revived - Source Code

Newer Super Mario All-Stars Revived is a New Super Mario Bros. Wii mod which aims to be a Super Mario All-Stars remaster, featuring a modern take on gameplay and extra additions to the game.

## Building

### Premises

- The guides below assume a certain level of savviness. Don't know how to do something? Look it up.
- Don't like how the folder structure is laid out? Edit the scripts to match your own.
- The Windows build scripts are currently untested and may not work at all.

### Requirements

- [CodeWarrior for MPC55xx/MPC56xx v2.10 Special Edition](https://www.nxp.com/lgfiles/devsuites/PowerPC/CW55xx_v2_10_SE.exe)
- [Kamek](https://github.com/Lord-Giganticus/Kamek/releases) (pick the one you need according to your OS)

### Installation - Windows

* Clone the GitHub repo to a folder of choice;
* Install `.NET 5.0` or higher if not already present, as it is required by Kamek;
* Add Kamek to your `PATH` variable (restarting your device may be necessary in order for the change to be detected);
* Run the CodeWarrior installer:
    - Choose whether to unpack to a temporary location, accept the Terms and pick a destination folder if you don't like the default one;
    - In the next screen pick `Custom`;
    - In the following screen, you can turn everything off (except `Command Line Tools`, as it is required) by setting the checkboxes;
    - Continue the installation until the end.
* Go to the cloned GitHub repo and make a folder named `cw`;
* Go to the CodeWarrior installation directory and copy the contents of the `Command Line Tools` folder to the `cw` folder;
* If not present, also copy the `license.dat` and `lmgr11.dll` files in said folder;
* Run `build.bat` to build the mod's code or loader. Check the notes below as well.

### Installation - Mac

I'm not covering this. Figure it out yourself.

### Installation - Linux

* Clone the GitHub repo to a folder of choice;
* CodeWarrior is a Windows application, therefore `wine` needs to be installed in order to run it;
* Kamek requires `dotnet` to be installed, so get that as well;
* Add Kamek to your `PATH` variable (sourcing may be necessary in order for the change to be detected);
* Do NOT run the CodeWarrior installer in WINE, as the installer will fail;
* Due to the above, you'll need to extract the needed files manually. To do so, first make sure the `p7zip` and `cabextract` packages are installed;
* Unpack the exe, then unpack `Data1.cab` in a folder of choice;
* As you can see, many files have random gibberish in their name. Here is a list of the important files (and their correct names between parentheses):
    - `lmgr11.dll` **(required)**
    - `_44CD8EA541F44E56801091477F3DC9AA` (license.dat) **(required)**
    - `_4C8ADA37887647F5955B4FB0F716277F` (mwcceppc.exe) **(required)**
    - `_C63F22BC0503480DAFDCAFC394185CBA` (mwasmeppc.exe) **(required)**
    - `lmgr8c.dll` **(optional)**
    - `_112A80A88B6147C590AE2CD9AE3F354F` (mwcceppc.txt) **(optional)**
    - `_312B4591741B497CB5EB342A632170BE` (mwldeppc.txt) **(optional)**
    - `_39217B1AFC714B7083E6CB5CBB10FC83` (mwasmeppc.txt) **(optional)**
    - `_4901FAD667D24E13BCF700F695CDD6D7` (mwldeppc.exe) **(optional)**
    - `_6F672001C92D4DF8B1893652C3B19743` (CLT_Usage_Notes.txt) **(optional)**
    - `_87844F06D94541B3B62E7A69C029A35D` (CLT_EABI_PPC_Tools_Notes.txt) **(optional)**
* Once you have gathered the files, make a folder named `cw` next to `game` and place them there;
* Run `build.sh` to build the mod's code or loader.

### Notes

* The scripts automatically place the compiled binaries into the default Dolphin folders for the respective OSes. Edit them to match your own folder structure or remove them altogether if you don't like that;
* The `game` build script accepts a list of regions (separated by ";" on Windows and by " " on Mac/Linux) to compile the code to. If no regions are given, the code will be compiled for every region. The list is as follows:
    - P1 = EU v1;
    - P2 = EU v2;
    - E1 = US v1;
    - E2 = US v2;
    - J1 = JP v1;
    - J2 = JP v2;
    - K = KR;
    - W = TW;

## Codebase

- The codebase uses C++ and PowerPC Assembly. C++ is preferred for full function replacements and for any kind of complex logic;
- No assumption about the use of registers by C++ code is made other than the ABI. If necessary, assembly wrappers are employed to restore/backup registers;
- The headers attempt to keep a consistent naming scheme and respect the original game's names, definitions and structures. However, all class members are marked as public for ease of use;
- As code is progressively added/updated, bugs may accidentally be introduced due to incompetence. In such case, please open an issue on the matter.

## Programming Resources

### Coding

- [Compiler conventions and more](http://wiki.tockdom.com/wiki/Compiler) (for Mario Kart Wii but applies to New Super Mario Bros. Wii as well)
- [Custom Sprite Guide](https://docs.google.com/document/d/1-KQhmawgy0da8ijdzL6d7zrlMRBX3_UOm-oShqFvuYc) (by Asu-chan)
- [IBM PPC 750CL Manual](https://fail0verflow.com/media/files/ppc_750cl.pdf)
- [Various Assembly Tutorials and Techniques](https://mkwii.com/forumdisplay.php?fid=50) (for Mario Kart Wii but applies to New Super Mario Bros. Wii as well)

### Documentation
- [Incomplete PAL v1 Symbol Map](https://cdn.discordapp.com/attachments/880441593549688884/930223706754670703/nsmbw_P1_ghidra.map) (by Ninji, RoadrunnerWMC, RootCubed, Grop and _tZ, [here](https://gist.github.com/RootCubed/8f8102fe6cf4ed79a45f1dfe23020a06) is a demangler/remangler for it written in Python)
- [Mario Kart Wii Decompilation](https://github.com/riidefi/mkw) (included since several libraries used in Mario Kart Wii are shared with New Super Mario Bros. Wii. Code by riidefi et al.)
- [Misc Structures](https://github.com/CLF78/NSMBW-Documentation) (by me)
- [Newer Super Mario Bros Wii Structures](https://github.com/Newer-Team/NewerSMBW/tree/no-translations/Kamek/include) (by the Newer Team)
