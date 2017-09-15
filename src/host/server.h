/*++
Copyright (c) Microsoft Corporation

Module Name:
- server.h

Abstract:
- This module contains the internal structures and definitions used by the console server.

Author:
- Therese Stowell (ThereseS) 12-Nov-1990

Revision History:
--*/

#pragma once

#include "screenInfo.hpp"

#include "settings.hpp"
#include "inputBuffer.hpp"

#include "conimeinfo.h"
#include "..\terminal\adapter\MouseInput.hpp"
#include "VtIo.hpp"

#include "..\server\ProcessList.h"
#include "..\server\WaitQueue.h"

// Flags flags
#define CONSOLE_IS_ICONIC               0x00000001
#define CONSOLE_OUTPUT_SUSPENDED        0x00000002
#define CONSOLE_HAS_FOCUS               0x00000004
#define CONSOLE_IGNORE_NEXT_MOUSE_INPUT 0x00000008
#define CONSOLE_SELECTING               0x00000010
#define CONSOLE_SCROLLING               0x00000020
// unused (CONSOLE_DISABLE_CLOSE)       0x00000040
// unused (CONSOLE_USE_POLY_TEXT)       0x00000080
#define CONSOLE_NO_WINDOW               0x00000100
// unused (CONSOLE_VDM_REGISTERED)      0x00000200
#define CONSOLE_UPDATING_SCROLL_BARS    0x00000400
#define CONSOLE_QUICK_EDIT_MODE         0x00000800
#define CONSOLE_CONNECTED_TO_EMULATOR   0x00002000
// unused (CONSOLE_FULLSCREEN_NOPAINT)  0x00004000
#define CONSOLE_QUIT_POSTED             0x00008000
#define CONSOLE_AUTO_POSITION           0x00010000
#define CONSOLE_IGNORE_NEXT_KEYUP       0x00020000
// unused (CONSOLE_WOW_REGISTERED)      0x00040000
#define CONSOLE_HISTORY_NODUP           0x00100000
#define CONSOLE_SCROLLBAR_TRACKING      0x00200000
#define CONSOLE_SETTING_WINDOW_SIZE     0x00800000
// unused (CONSOLE_VDM_HIDDEN_WINDOW)   0x01000000
// unused (CONSOLE_OS2_REGISTERED)      0x02000000
// unused (CONSOLE_OS2_OEM_FORMAT)      0x04000000
// unused (CONSOLE_JUST_VDM_UNREGISTERED)  0x08000000
// unused (CONSOLE_FULLSCREEN_INITIALIZED) 0x10000000
#define CONSOLE_USE_PRIVATE_FLAGS       0x20000000
// unused (CONSOLE_TSF_ACTIVATED)       0x40000000
#define CONSOLE_INITIALIZED             0x80000000

#define CONSOLE_SUSPENDED (CONSOLE_OUTPUT_SUSPENDED)

class COOKED_READ_DATA;

class CONSOLE_INFORMATION : public Settings
{
public:
    CONSOLE_INFORMATION();
    ~CONSOLE_INFORMATION();

    ConsoleProcessList ProcessHandleList;
    InputBuffer* pInputBuffer;

    PSCREEN_INFORMATION CurrentScreenBuffer;
    PSCREEN_INFORMATION ScreenBuffers;  // singly linked list
    ConsoleWaitQueue OutputQueue;
    LIST_ENTRY CommandHistoryList;
    LIST_ENTRY ExeAliasList;
    UINT NumCommandHistories;

    LPWSTR OriginalTitle;
    LPWSTR Title;
    LPWSTR LinkTitle;   // Path to .lnk file, can be nullptr

    DWORD Flags;

    WORD PopupCount;

    // the following fields are used for ansi-unicode translation
    UINT CP;
    UINT OutputCP;

    ULONG CtrlFlags;    // indicates outstanding ctrl requests
    ULONG LimitingProcessId;

    CPINFO CPInfo;
    CPINFO OutputCPInfo;

    DWORD ReadConInpNumBytesUnicode;

    COOKED_READ_DATA* lpCookedReadData;

    ConsoleImeInfo ConsoleIme;

    Microsoft::Console::VirtualTerminal::MouseInput terminalMouseInput;

    void LockConsole();
    BOOL TryLockConsole();
    void UnlockConsole();
    bool IsConsoleLocked() const;
    ULONG GetCSRecursionCount();

    Microsoft::Console::VirtualTerminal::VtIo* GetVtIo();
    
private:
    CRITICAL_SECTION _csConsoleLock;   // serialize input and output using this
    
    Microsoft::Console::VirtualTerminal::VtIo _vtIo;
};

#define ConsoleLocked() (ServiceLocator::LocateGlobals()->getConsoleInformation()->ConsoleLock.OwningThread == NtCurrentTeb()->ClientId.UniqueThread)

#define CONSOLE_STATUS_WAIT 0xC0030001
#define CONSOLE_STATUS_READ_COMPLETE 0xC0030002
#define CONSOLE_STATUS_WAIT_NO_BLOCK 0xC0030003

#include "..\server\ObjectHandle.h"


NTSTATUS SetActiveScreenBuffer(_Inout_ PSCREEN_INFORMATION pScreenInfo);
