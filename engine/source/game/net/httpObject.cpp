//-----------------------------------------------------------------------------
// Torque Shader Engine
// Copyright (C) GarageGames.com, Inc.
//-----------------------------------------------------------------------------

#include "game/net/httpObject.h"

#include "platform/platform.h"
#include "platform/event.h"
#include "core/fileStream.h"
#include "console/simBase.h"
#include "console/consoleInternal.h"

IMPLEMENT_CONOBJECT(HTTPObject);

//--------------------------------------

HTTPObject::HTTPObject()
{
    mHostName = 0;
    mPath = 0;
    mQuery = 0;
    mPost = 0;
    mBufferSave = 0;
}

HTTPObject::~HTTPObject()
{
    dFree(mHostName);
    dFree(mPath);
    dFree(mQuery);
    dFree(mPost);

    mHostName = 0;
    mPath = 0;
    mQuery = 0;
    mPost = 0;
    dFree(mBufferSave);
}

//--------------------------------------
//--------------------------------------
void HTTPObject::get(const char* host, const char* path, const char* query)
{
    if (mHostName)
        dFree(mHostName);
    if (mPath)
        dFree(mPath);
    if (mQuery)
        dFree(mQuery);
    if (mPost)
        dFree(mPost);
    if (mBufferSave)
        dFree(mBufferSave);

    mBufferSave = 0;
    mHostName = dStrdup(host);
    mPath = dStrdup(path);
    if (query)
        mQuery = dStrdup(query);
    else
        mQuery = NULL;
    mPost = NULL;

    connect(host);
}

void HTTPObject::post(const char* host, const char* path, const char* query, const char* post)
{
    if (mHostName)
        dFree(mHostName);
    if (mPath)
        dFree(mPath);
    if (mQuery)
        dFree(mQuery);
    if (mPost)
        dFree(mPost);
    if (mBufferSave)
        dFree(mBufferSave);

    mBufferSave = 0;
    mHostName = dStrdup(host);
    mPath = dStrdup(path);
    if (query && query[0])
        mQuery = dStrdup(query);
    else
        mQuery = NULL;
    mPost = dStrdup(post);
    connect(host);
}

static char getHex(char c)
{
    if (c <= 9)
        return c + '0';
    return c - 10 + 'A';
}

static S32 getHexVal(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'z')
        return c - 'a' + 10;
    return -1;
}

void HTTPObject::expandPath(char* dest, const char* path, U32 destSize)
{
    static bool asciiEscapeTableBuilt = false;
    static bool asciiEscapeTable[256];
    if (!asciiEscapeTableBuilt)
    {
        asciiEscapeTableBuilt = true;
        U32 i;
        for (i = 0; i <= ' '; i++)
            asciiEscapeTable[i] = true;
        for (; i <= 0x7F; i++)
            asciiEscapeTable[i] = false;
        for (; i <= 0xFF; i++)
            asciiEscapeTable[i] = true;
        asciiEscapeTable['\"'] = true;
        asciiEscapeTable['_'] = true;
        asciiEscapeTable['\''] = true;
        asciiEscapeTable['#'] = true;
        asciiEscapeTable['$'] = true;
        asciiEscapeTable['%'] = true;
        asciiEscapeTable['&'] = true;
        asciiEscapeTable['+'] = true;
        asciiEscapeTable['-'] = true;
        asciiEscapeTable['~'] = true;
    }

    U32 destIndex = 0;
    U32 srcIndex = 0;
    while (path[srcIndex] && destIndex < destSize - 3)
    {
        char c = path[srcIndex++];
        if (asciiEscapeTable[c])
        {
            dest[destIndex++] = '%';
            dest[destIndex++] = getHex((c >> 4) & 0xF);
            dest[destIndex++] = getHex(c & 0xF);
        }
        else
            dest[destIndex++] = c;
    }
    dest[destIndex] = 0;
}

//--------------------------------------
void HTTPObject::onConnected()
{
    Parent::onConnected();
    char expPath[8192];
    char buffer[8192];

    if (mQuery)
    {
        dSprintf(buffer, sizeof(buffer), "%s?%s", mPath, mQuery);
        expandPath(expPath, buffer, sizeof(expPath));
    }
    else
        expandPath(expPath, mPath, sizeof(expPath));

    char* pt = dStrchr(mHostName, ':');
    if (pt)
        *pt = 0;
    dSprintf(buffer, sizeof(buffer), "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", expPath, mHostName);
    if (pt)
        *pt = ':';

    send((U8*)buffer, dStrlen(buffer));
    mParseState = ParsingStatusLine;
    mChunkedEncoding = false;
}

void HTTPObject::onConnectFailed()
{
    dFree(mHostName);
    dFree(mPath);
    dFree(mQuery);
    mHostName = 0;
    mPath = 0;
    mQuery = 0;
    Parent::onConnectFailed();
}


void HTTPObject::onDisconnect()
{
    dFree(mHostName);
    dFree(mPath);
    dFree(mQuery);
    mHostName = 0;
    mPath = 0;
    mQuery = 0;
    Parent::onDisconnect();
}

bool HTTPObject::processLine(U8* line)
{
    if (mParseState == ParsingStatusLine)
    {
        mParseState = ParsingHeader;
    }
    else if (mParseState == ParsingHeader)
    {
        if (!dStricmp((char*)line, "transfer-encoding: chunked"))
            mChunkedEncoding = true;
        if (line[0] == 0)
        {
            if (mChunkedEncoding)
                mParseState = ParsingChunkHeader;
            else
                mParseState = ProcessingBody;
            return true;
        }
    }
    else if (mParseState == ParsingChunkHeader)
    {
        if (line[0]) // strip off the crlf if necessary
        {
            mChunkSize = 0;
            S32 hexVal;
            while ((hexVal = getHexVal(*line++)) != -1)
            {
                mChunkSize *= 16;
                mChunkSize += hexVal;
            }
            if (mBufferSave)
            {
                mBuffer = mBufferSave;
                mBufferSize = mBufferSaveSize;
                mBufferSave = 0;
            }
            if (mChunkSize)
                mParseState = ProcessingBody;
            else
            {
                mParseState = ProcessingDone;
                finishLastLine();
            }
        }
    }
    else
    {
        return Parent::processLine(line);
    }
    return true;
}

U32 HTTPObject::onDataReceive(U8* buffer, U32 bufferLen)
{
    U32 start = 0;
    parseLine(buffer, &start, bufferLen);
    return start;
}

//--------------------------------------
U32 HTTPObject::onReceive(U8* buffer, U32 bufferLen)
{
    if (mParseState == ProcessingBody)
    {
        if (mChunkedEncoding && bufferLen >= mChunkSize)
        {
            U32 ret = onDataReceive(buffer, mChunkSize);
            mChunkSize -= ret;
            if (mChunkSize == 0)
            {
                if (mBuffer)
                {
                    mBufferSaveSize = mBufferSize;
                    mBufferSave = mBuffer;
                    mBuffer = 0;
                    mBufferSize = 0;
                }
                mParseState = ParsingChunkHeader;
            }
            return ret;
        }
        else
        {
            U32 ret = onDataReceive(buffer, bufferLen);
            mChunkSize -= ret;
            return ret;
        }
    }
    else if (mParseState != ProcessingDone)
    {
        U32 start = 0;
        parseLine(buffer, &start, bufferLen);
        return start;
    }
    return bufferLen;
}

//--------------------------------------
ConsoleMethod(HTTPObject, get, void, 4, 5, "(TransportAddress addr, string requirstURI, string query=NULL)")
{
    object->get(argv[2], argv[3], argc == 4 ? NULL : argv[4]);
}

ConsoleMethod(HTTPObject, post, void, 6, 6, "(TransportAddress addr, string requestURI, string query, string post)")
{
    object->post(argv[2], argv[3], argv[4], argv[5]);
}