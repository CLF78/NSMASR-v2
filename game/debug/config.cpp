#include <kamek.h>
#include <egg/core/eggHeap.h>
#include <fBase/dBase/dScene/dScStage.h>
#include <m/mHeap/mHeap.h>
#include <nw4r/db/mapfile.h>
#include <nw4r/ut/CharStrmReader.h>
#include <rvl/dvd/dvd.h>
#include <rvl/os/OS.h>
#include <stdlib/stdlib.h>
#include <stdlib/string.h>
#include "debug/config.h"

#define clamp(n, lower, upper) n <= lower ? lower : n >= upper ? upper : n

const ConfigKey keys[] = {
    {ConfigKey::LaunchType, "LaunchType"},
    {ConfigKey::SaveNumber, "SaveNumber"},
    {ConfigKey::PlayerCount, "PlayerCount"},
    {ConfigKey::PowerUp, "PowerUp"},
    {ConfigKey::HasStar, "HasStar"},
    {ConfigKey::World, "World"},
    {ConfigKey::Level, "Level"},
    {ConfigKey::Area, "Area"},
    {ConfigKey::Entrance, "Entrance"},
    {ConfigKey::GameMode, "GameMode"},
    {ConfigKey::DrawHitboxes, "DrawHitboxes"},
    {ConfigKey::DrawColliders, "DrawColliders"},
    {ConfigKey::DrawSensors, "DrawSensors"},
    {ConfigKey::DrawRideableColliders, "DrawRideableColliders"},
    {ConfigKey::MapNode, "MapNode"},
    {ConfigKey::MovieId, "MovieId"},
};

static dConfigManager_c instance;

dConfigManager_c::dConfigManager_c() {

    // Initialize the values to a sane default
    this->launchType = LaunchType::Normal;

    this->saveNo = -1;
    this->playerCount = 1;
    this->world = 0;
    this->powerUp = Powerup::None;
    this->star = false;

    this->level = 0;
    this->area = 0;
    this->entrance = 0xFF;
    this->gameMode = LaunchGameMode::Normal;
    this->collisionDebugFlags = ColliderDisplayFlags::None;

    this->mapNode = 0xFF;

    this->movieId = 1;
}

void dConfigManager_c::parseConfigLine(char* key, char* param, int paramSize) {

    // Initialize variables
    int decodedParam = 0;
    bool isNumeric = true;

    // If the first two characters are "0x", assume it's a hex number
    bool isHex = (strstr(param, "0x") == param);
    if (isHex) {
        param += 2;
        paramSize -= 2;
    }

    // Check if the value is numeric and convert all uppercase characters to lowercase
    for (int i = 0; i < paramSize; i++) {
        u8 currChar = param[i];
        if (currChar < '0' || currChar > '9') {
            isNumeric = false;
            if (currChar >= 'A' && currChar <= 'Z')
                param[i] = currChar - 0x20;
        }
    }

    // If the value is numeric, convert it
    if (isNumeric) {
        if (isHex)
            decodedParam = nw4r::db::XStrToU32_((const u8*)param);
        else
            decodedParam = atoi(param);

    // If the value is not numeric, check for booleans
    } else if (strcmp(param, "true") == 0)
        decodedParam = 1;

    // Parse the key
    int keyId = -1;
    for (int i = 0; i < sizeof(keys) / sizeof(ConfigKey); i++) {
        if (strcmp(key, keys[i].keyName) == 0) {
            keyId = keys[i].keyId;
            break;
        }
    }

    // Act depending on the key we found
    switch(keyId) {
        case ConfigKey::LaunchType:
            this->launchType = decodedParam & 3;
            break;

        case ConfigKey::SaveNumber:
            this->saveNo = (decodedParam + 1) & 3;
            break;

        case ConfigKey::PlayerCount:
            this->playerCount = (decodedParam - 1) & 3;
            break;

        case ConfigKey::PowerUp:
            this->powerUp = clamp(decodedParam, 0, 6);
            break;

        case ConfigKey::HasStar:
            this->star = decodedParam & 1;
            break;

        case ConfigKey::World:
            this->world = clamp(decodedParam - 1, 0, 9);
            break;

        case ConfigKey::Level:
            this->level = clamp(decodedParam - 1, 0, 99);
            break;

        case ConfigKey::Area:
            this->area = (decodedParam - 1) & 3;
            break;

        case ConfigKey::Entrance:
            this->entrance = (decodedParam - 1) & 0xFF;
            break;

        case ConfigKey::GameMode:
            this->gameMode = clamp(decodedParam, 0, 5);
            break;

        case ConfigKey::DrawHitboxes:
            this->collisionDebugFlags |= ((decodedParam & 1) << ColliderDisplayFlags::Hitboxes);
            break;

        case ConfigKey::DrawColliders:
            this->collisionDebugFlags |= ((decodedParam & 1) << ColliderDisplayFlags::Colliders);
            break;

        case ConfigKey::DrawSensors:
            this->collisionDebugFlags |= ((decodedParam & 1) << ColliderDisplayFlags::Sensors);
            break;

        case ConfigKey::DrawRideableColliders:
            this->collisionDebugFlags |= ((decodedParam & 1) << ColliderDisplayFlags::RideableColliders);
            break;

        case ConfigKey::MapNode:
            this->mapNode = decodedParam & 0xFF;
            break;

        case ConfigKey::MovieId:
            this->movieId = clamp(decodedParam, 1, 3);
            break;

        default:
    }
}

void dConfigManager_c::parseConfig(nw4r::ut::CharStrmReader* reader, void* bufferEnd) {

    // Initialize variables
    bool isComment = false;
    bool isParam = false;
    char keyBuffer[64];
    char paramBuffer[64];
    int keyBufferSize = 0;
    int paramBufferSize = 0;

    // Clear the buffer
    memset(keyBuffer, 0, sizeof(keyBuffer));
    memset(paramBuffer, 0, sizeof(paramBuffer));

    // Set the file read function (needed by the hex to u32 function later)
    nw4r::db::GetCharPtr_ = &nw4r::db::GetCharOnMem_;

    // Read one character at a time until the file ends
    do {
        wchar_t nextChar = reader->Next();

        // Ignore all non-ASCII characters, i cannot be arsed
        if (nextChar >= 0x80)
            continue;
        u8 currChar = nextChar & 0x7F;

        // Ignore whitespace characters
        if (currChar == ' ' || currChar == '\t' || currChar == '\r')
            continue;

        // If a newline is reached, clear the variables
        if (currChar == '\n') {

            // Only parse lines with a proper key and param
            if (keyBufferSize != 0 && paramBufferSize != 0)
                this->parseConfigLine(keyBuffer, paramBuffer, paramBufferSize);

            // Reset variables
            memset(keyBuffer, 0, keyBufferSize);
            memset(paramBuffer, 0, paramBufferSize);
            keyBufferSize = 0;
            paramBufferSize = 0;
            isComment = false;
            isParam = false;

        // Ignore any comment character on the rest of this line
        } else if (!isComment) {

            // Mark characters after a # as a comment
            if (currChar == '#')
                isComment = true;

            // Mark characters after a = as the param
            else if (currChar == '=')
                isParam = true;

            // Store character in the key buffer unless it's full
            else if (!isParam) {
                if (keyBufferSize < sizeof(keyBuffer)) {
                    keyBuffer[keyBufferSize] = currChar;
                    keyBufferSize++;
                }
            }

            // Store character in the param buffer unless it's full
            else if (paramBufferSize < sizeof(paramBuffer)) {
                paramBuffer[paramBufferSize] = currChar;
                paramBufferSize++;
            }
        }

    } while (reader->GetCurrentPos() < bufferEnd);
}

void dConfigManager_c::loadConfig() {

    // Locate the file
    int entrynum = DVDConvertPathToEntrynum(CONFIG_PATH);
    if (entrynum == -1) {
        OSReport("Debug config not found, bailing!\n");
        return;
    }

    // Try to load it
    DVDFileInfo dvdHandle;
    bool fileLoaded = DVDFastOpen(entrynum, &dvdHandle);
    if (!fileLoaded) {
        OSReport("Debug config not loaded, bailing!\n");
        return;
    }

    // Allocate the necessary space
    size_t size = OSRoundUp32B(dvdHandle.length);
    void* buffer = EGG::Heap::alloc(size, 0x20, mHeap::g_archiveHeap);
    if (buffer == NULL) {
        OSReport("Failed to allocate buffer, bailing!\n");
        return;
    }

    // Read the file
    s32 length = DVDReadPrio(&dvdHandle, buffer, size, 0, 2);
    if (length > 0) {

        // Initialize the stream reader, assume the file uses UTF-8
        nw4r::ut::CharStrmReader reader;
        reader.Set(buffer);
        reader.readFunc = &nw4r::ut::CharStrmReader::ReadNextCharUTF8;

        // Parse the file
        this->parseConfig(&reader, (void*)((u32)buffer + dvdHandle.length));
    }

    // Close the file, free the buffer and return
    DVDClose(&dvdHandle);
    EGG::Heap::free(buffer, NULL);
}

// Config loader hook
kmBranchDefCpp(0x8015D850, NULL, void, void) {

    // Load the config data
    instance.loadConfig();

    // TODO actual logic

    // original call
    dScStage_c::goToTitleScreen(false, false);
}
