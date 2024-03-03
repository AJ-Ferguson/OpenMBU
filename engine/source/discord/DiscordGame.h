#ifndef _DISCORDGAME_H_
#define _DISCORDGAME_H_

#include <iostream>
#include <fstream>
#include <unordered_map>

#include "console/console.h"

//constexpr const char* AUTOSPLITTER_FILE_NAME = "autosplitter.txt";
constexpr U32 DISCORDSDK_BUF_SIZE = 512;

class DiscordGame
{
public:
    static void init();
    static void destroy();
    static DiscordGame* get();
    bool isActive() { return mActive; }
    //void sendData(const char* data);
    void update();
    const char* ProcessLevel(StringTableEntry guid);

    void setStatus(const char* status) 
    { 
        mStatus = status; 
        if (mStatus == nullptr) 
            mStatus = ""; 
        notifyParamsChange();

    }
    void setDetails(const char* details) 
    { 
        mDetails = details; 
        if (mDetails == nullptr) 
            mDetails = ""; 
        notifyParamsChange();
    }
    void setLevel(const char* guid) 
    {
        mGUID = guid; 
        if (mGUID == nullptr) 
            mGUID = ""; 
        notifyParamsChange();
    }
    void setSmallImageKey(const char* sImgKey) 
    {
        mImgSm = sImgKey; 
        if (mImgSm == nullptr) 
            mImgSm = "loading_icon"; 
        notifyParamsChange();
    }
    void notifyParamsChange() { mChanged = true; }
    //void setIcon(const char* icon, const char* iconText) { mIcon = icon; if (mIcon == nullptr) mIcon = ""; mIconText = iconText; if (mIconText == nullptr) mIconText = ""; }
private:
    DiscordGame();
    ~DiscordGame();
    static DiscordGame* smInstance;
    bool mActive;
    bool mChanged;
    std::unordered_map<const char*, const char*> mGuidLookup;
    const char* mStatus;
    const char* mDetails;
    const char* mGUID;
    const char* mImgSm;
    const char* mLargeImageKey;
    //const char* mIcon;
    //const char* mIconText;
};

#endif // _DISCORDGAME_H_