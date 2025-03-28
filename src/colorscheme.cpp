/*
 *  This file is part of Poedit (https://poedit.net)
 *
 *  Copyright (C) 2016-2025 Vaclav Slavik
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 */

#include "colorscheme.h"

#include <wx/artprov.h>
#include <wx/settings.h>

#ifdef __WXGTK__
    #include <pango/pango.h>
    #if PANGO_VERSION_CHECK(1,38,0)
        #define SUPPORTS_BGALPHA
    #endif
#else
    #define SUPPORTS_BGALPHA
#endif


namespace
{

#ifdef __WXOSX__

inline wxColour sRGB(int r, int g, int b, double a = 1.0)
{
    return wxColour([NSColor colorWithSRGBRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:a]);
}

inline bool IsDarkAppearance(NSAppearance *appearance)
{
    NSAppearanceName appearanceName = [appearance bestMatchFromAppearancesWithNames:@[NSAppearanceNameAqua, NSAppearanceNameDarkAqua]];
    return [appearanceName isEqualToString:NSAppearanceNameDarkAqua];
}

#else

inline wxColour sRGB(int r, int g, int b, double a = 1.0)
{
    return wxColour(r, g, b, int(a * wxALPHA_OPAQUE));
}

#endif

} // anonymous namespace

std::unique_ptr<ColorScheme::Data> ColorScheme::s_data;
bool ColorScheme::s_appModeDetermined = false;
ColorScheme::Mode ColorScheme::s_appMode = ColorScheme::Mode::Light;


wxColour ColorScheme::DoGet(Color color, Mode mode)
{
    switch (color)
    {
        // Labels:

        case Color::Label:
            #ifdef __WXOSX__
            return wxColour([NSColor labelColor]);
            #else
            return wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
            #endif

        case Color::SecondaryLabel:
            #ifdef __WXOSX__
            return wxColour([NSColor secondaryLabelColor]);
            #elif defined(__WXGTK__)
            return wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
            #else
            return wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT);
            #endif

        case Color::ListControlBg:
            #ifdef __WXOSX__
            if (mode == Dark)
            {
                // FIXME: In dark mode, listbox color is special and requires NSBox to be rendered correctly;
                //        this is just passable approximation
                return wxColour([NSColor underPageBackgroundColor]);
            }
            else
            #endif
            return wxSystemSettings::GetColour(wxSYS_COLOUR_LISTBOX);

        // List items:

        case Color::ItemID:
            #ifdef __WXOSX__
            return wxColour([NSColor tertiaryLabelColor]);
            #else
            return mode == Light ? "#a1a1a1" : wxSystemSettings::GetColour(wxSYS_COLOUR_LISTBOXTEXT).ChangeLightness(50);
            #endif
        case Color::ItemFuzzy:
            return mode == Dark ? sRGB(253, 178, 72) : sRGB(230, 134, 0);
        case Color::ItemError:
            return sRGB(225, 77, 49);
        case Color::ErrorText:
            return *wxRED;
        case Color::ItemContextFg:
            return mode == Dark ? sRGB(180, 222, 254) : sRGB(70, 109, 137);
        case Color::ItemContextBg:
            if (mode == Dark)
                return sRGB(67, 94, 147, 0.6);
            else
                return sRGB(217, 232, 242);
        case Color::ItemContextBgHighlighted:
            #if defined(__WXMSW__)
            return sRGB(255, 255, 255, 0.50);
            #elif defined(SUPPORTS_BGALPHA)
            return sRGB(255, 255, 255, 0.35);
            #else
            return DoGet(Color::ItemContextBg, mode);
            #endif

        // Tags:

        case Color::TagContextFg:
            return DoGet(Color::ItemContextFg, mode);
        case Color::TagContextBg:
            return DoGet(Color::ItemContextBg, mode);
        case Color::TagSecondaryBg:
            return mode == Dark ? sRGB(255, 255, 255, 0.5) : sRGB(0, 0, 0, 0.10);
        case Color::TagErrorLineBg:
            return sRGB(241, 134, 135);
        case Color::TagWarningLineBg:
            return mode == Dark ? sRGB(198, 171, 113) : sRGB(253, 235, 176);
        case Color::TagErrorLineFg:
            return sRGB(0, 0, 0, 0.8);
        case Color::TagSecondaryFg:
        case Color::TagWarningLineFg:
            return sRGB(0, 0, 0, 0.9);


        // Separators:

        case Color::ToolbarSeparator:
            return mode == Dark ? "#505050" : "#cdcdcd";
        case Color::SidebarSeparator:
            return mode == Dark ? *wxBLACK : "#cbcbcb";
        case Color::EditingSeparator:
            return mode == Dark ? sRGB(80, 80, 80) : sRGB(204, 204, 204);
        case Color::SidebarBlockSeparator:
            return mode == Dark ? sRGB(80, 80, 80, 0.8) : sRGB(204, 204, 204, 0.8);
        case Color::EditingThickSeparator:
            return mode == Dark ? sRGB(46, 47, 50) : sRGB(240, 240, 240);

        // Backgrounds:

        case Color::SidebarBackground:
            #ifdef __WXOSX__
            if (@available(macOS 11.0, *))
                return mode == Dark ? sRGB(46, 47, 50) : sRGB(240, 240, 240); // same as EditingThickSeparator
            #endif
            return mode == Dark ? sRGB(45, 42, 41) : "#edf0f4";

        case Color::EditingBackground:
            #ifdef __WXOSX__
            return wxColour([NSColor textBackgroundColor]);
            #else
            return wxSystemSettings::GetColour(wxSYS_COLOUR_LISTBOX);
            #endif

        // Fuzzy toggle:
        case Color::FuzzySwitch:
            return mode == Dark ? sRGB(253, 178, 72) : sRGB(244, 143, 0);
        case Color::FuzzySwitchInactive:
            #ifdef __WXGTK__
            return mode == Dark ? sRGB(163, 163, 163) : sRGB(87, 87, 87);
            #else
            return DoGet(Color::SecondaryLabel, mode);
            #endif

        // Syntax highlighting:

        case Color::SyntaxLeadingWhitespaceBg:
            return mode == Dark ? sRGB(75, 49, 111) : sRGB(234, 223, 247);
        case Color::SyntaxEscapeFg:
            return mode == Dark ? sRGB(234, 188, 244) : sRGB(162, 0, 20);
        case Color::SyntaxEscapeBg:
            return mode == Dark ? sRGB(90, 15, 167, 0.5) : sRGB(254, 234, 236);
        case Color::SyntaxMarkup:
            return mode == Dark ? sRGB(76, 156, 230) : sRGB(0, 121, 215);
        case Color::SyntaxFormat:
            return mode == Dark ? sRGB(250, 165, 251) : sRGB(178, 52, 197);

        // Attention bar:

#ifdef __WXGTK__
        // FIXME: use system colors
        case Color::AttentionWarningBackground:
            return sRGB(250, 173, 61);
        case Color::AttentionQuestionBackground:
            return sRGB(138, 173, 212);
        case Color::AttentionErrorBackground:
            return sRGB(237, 54, 54);
#else
        case Color::AttentionWarningBackground:
            return mode == Dark ? sRGB(254, 224, 132) : sRGB(254, 228, 149);
        case Color::AttentionQuestionBackground:
            return sRGB(199, 244, 156);
        case Color::AttentionErrorBackground:
            return sRGB(241, 103, 104);
#endif

        // Buttons:

        case Color::TranslucentButton:
            return sRGB(255, 255, 255, 0.5);

        case Color::Max:
            return wxColour();
    }

    return wxColour(); // Visual C++ being silly
}


void ColorScheme::InvalidateCachesIfNeeded()
{
    if (!s_appModeDetermined)
        return; // nothing to do yet

    // invalidate the mode and force re-checking:
    auto prevMode = s_appMode;
    s_appModeDetermined = false;
    if (prevMode == GetAppMode())
        return;  // mode didn't really check, nothing to invalidate

#ifndef __WXOSX__
    // Colors are cached for both variants, so don't need to be invalidated.
    // s_appMode was refreshed above in any case.
    // That leaves cached template icons in wxArtProvider on non-Mac platforms,
    // which we can purge by adding a dummy provider:
    auto dummy = new wxArtProvider();
    wxArtProvider::Push(dummy);
    wxArtProvider::Delete(dummy);
#endif
}


ColorScheme::Mode ColorScheme::GetAppMode()
{
    if (!s_appModeDetermined)
    {
#ifdef __WXOSX__
        s_appMode = IsDarkAppearance(NSApp.effectiveAppearance) ? Dark : Light;
#else
        auto colBg = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
        auto colFg = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
        s_appMode = (colFg.GetLuminance() - colBg.GetLuminance() > 0.2) ? Dark : Light;
#endif
        s_appModeDetermined = true;
    }

    return s_appMode;
}


ColorScheme::Mode ColorScheme::GetWindowMode(wxWindow *win)
{
    // TODO: Migrate to using wxSystemAppearance. That is only app-wide, not per-window,
    //       but I don't think Poedit actually requires per-window handling.
#ifdef __WXOSX__
    NSView *view = win->GetHandle();
    return IsDarkAppearance(view.effectiveAppearance) ? Dark : Light;
#else
    // Use dark scheme for very dark backgrounds:
    auto colBg = win->GetDefaultAttributes().colBg;
    auto colFg = win->GetDefaultAttributes().colFg;
    return (colFg.GetLuminance() - colBg.GetLuminance() > 0.2) ? Dark : Light;
#endif
}


wxColour ColorScheme::GetBlendedOn(Color color, wxWindow *win, Color bgColor)
{
    auto bg = (bgColor != Color::Max) ? Get(bgColor, win) : win->GetBackgroundColour();
    auto fg = Get(color, win);
#ifndef __WXOSX__
    if (fg.Alpha() != wxALPHA_OPAQUE)
    {
        double alpha = fg.Alpha() / 255.0;
        return wxColour(wxColour::AlphaBlend(fg.Red(), bg.Red(), alpha),
                        wxColour::AlphaBlend(fg.Green(), bg.Green(), alpha),
                        wxColour::AlphaBlend(fg.Blue(), bg.Blue(), alpha));
    }
#endif
    return fg;
}

void ColorScheme::CleanUp()
{
    s_data.reset();
}
