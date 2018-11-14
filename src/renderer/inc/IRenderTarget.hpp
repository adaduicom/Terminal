/*++
Copyright (c) Microsoft Corporation

Module Name:
- IRenderTarget.hpp

Abstract:
- This serves as the entry point for console rendering activites.

Author(s):
- Michael Niksa (MiNiksa) 17-Nov-2015
--*/

#pragma once

#include "FontInfoDesired.hpp"
#include "IRenderEngine.hpp"
#include "../types/inc/viewport.hpp"

namespace Microsoft::Console::Render
{
    class IRenderTarget
    {
    public:
        virtual ~IRenderTarget() {};

        virtual void TriggerRedraw(const Microsoft::Console::Types::Viewport& region) = 0;
        virtual void TriggerRedraw(const COORD* const pcoord) = 0;
        virtual void TriggerRedrawCursor(const COORD* const pcoord) = 0;

        virtual void TriggerRedrawAll() = 0;
        virtual void TriggerTeardown() = 0;

        virtual void TriggerSelection() = 0;
        virtual void TriggerScroll() = 0;
        virtual void TriggerScroll(const COORD* const pcoordDelta) = 0;
        virtual void TriggerCircling() = 0;
        virtual void TriggerTitleChange() = 0;
    };
}
