# Newer Super Mario All-Stars Revived
Newer Super Mario All-Stars Revived is a New Super Mario Bros. Wii mod which aims to be a Super Mario All-Stars remaster, featuring a modern take on gameplay and extra additions to the game.

## Building Source Code

### Premises
* The guides below assume a certain level of savviness. Don't know how to do something? Look it up.
* Don't like how the folder structure is laid out? Change it.

### Requirements
- [CodeWarrior for MPC55xx/MPC56xx v2.10 Special Edition](https://cache.nxp.com/lgfiles/devsuites/PowerPC/CW55xx_v2_10_SE.exe)
- [Kamek](https://github.com/Treeki/Kamek/releases) (pick according to your OS)

### Installation - Windows
* Clone the GitHub repo to a folder of choice;
* Install `.NET 5.0` or higher if not already present, as it is required by Kamek;
* Add Kamek to your `PATH` variable (restarting your device may be necessary in order for the change to be detected);
    - If this isn't possible, then edit the build scripts to match Kamek's path.
* Run the CodeWarrior installer;
    - Only the `Command Line Tools` component is needed for compilation; you can set this in the custom install configuration.
* Go to the cloned GitHub repo and make a folder named `cw`;
* Go to the CodeWarrior installation directory and copy the contents of the `PowerPC_EABI_Tools\Command_Line_Tools` folder to the `cw` folder;
* Copy `license.dat` and `lmgr11.dll` to the `cw` folder as well;
* Run `build.py` to build the mod's code or loader. Make sure to check the [notes](#Notes) section.

### Installation - Mac
I'm not covering this. Figure it out yourself.

### Installation - Linux
* Clone the GitHub repo to a folder of choice;
* CodeWarrior is a Windows application, therefore `wine` needs to be installed in order to run it;
* Kamek requires `dotnet` to be installed, so get that as well;
* Add Kamek to your `PATH` variable (sourcing may be necessary in order for the change to be detected);
* Do NOT run the CodeWarrior installer in WINE, as the installer will fail;
* Due to the above, you'll need to extract the needed files manually. To do so, first make sure the `cabextract` package is installed;
* Place the CodeWarrior installer in the same folder as `extractCW.sh`, then run the script;
* Run `build.py` to build the mod's code or loader.

### Notes
* The scripts automatically place the compiled binaries into the `assets/game` folder. Change them if you don't like it;
* The `game` build script accepts a list of regions to compile the code to. If no regions are given, the code will be compiled for every region. The list is as follows:
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
- As code is progressively added/updated, bugs may accidentally be introduced due to incompetence.

## Resources

*NOTE: Do not use this repository to ask modding questions! They will be left unanswered.*

### Generic Modding
- [NSMBW Modding Database](https://horizon.miraheze.org/wiki/Main_Page)
- [NSMBW Hacking Depot](https://discord.gg/nXgyHrMyjA) (Discord Server)

### Coding
- [Compiler conventions and more](http://wiki.tockdom.com/wiki/Compiler) (for Mario Kart Wii but applies to New Super Mario Bros. Wii as well)
- [Custom Sprite Guide](https://docs.google.com/document/d/1-KQhmawgy0da8ijdzL6d7zrlMRBX3_UOm-oShqFvuYc) (by Asu-chan)
- [IBM PPC 750CL Manual](https://fail0verflow.com/media/files/ppc_750cl.pdf)
- [Various Assembly Tutorials and Techniques](https://mkwii.com/forumdisplay.php?fid=50) (for Mario Kart Wii but applies to New Super Mario Bros. Wii as well)

### Programming Documentation
- [Incomplete PAL v1 Symbol Map](https://cdn.discordapp.com/attachments/880441593549688884/930223706754670703/nsmbw_P1_ghidra.map) (by Ninji, RoadrunnerWMC, RootCubed, Grop and _tZ, [here](https://gist.github.com/RootCubed/8f8102fe6cf4ed79a45f1dfe23020a06) is a demangler/remangler for it written in Python)
- [Mario Kart Wii Decompilation](https://github.com/riidefi/mkw) (included since several libraries used in Mario Kart Wii are shared with New Super Mario Bros. Wii. Code by riidefi et al.)
- [Misc Structures](https://github.com/CLF78/NSMBW-Documentation) (by me, outdated)
- [Newer Super Mario Bros Wii Structures](https://github.com/Newer-Team/NewerSMBW/tree/no-translations/Kamek/include) (by the Newer Team)
