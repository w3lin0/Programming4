#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "imgui.h"

// System includes
#include <ctype.h>          // toupper
#include <limits.h>         // INT_MIN, INT_MAX
#include <math.h>           // sqrtf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>          // vsnprintf, sscanf, printf
#include <stdlib.h>         // NULL, malloc, free, atoi
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>         // intptr_t
#else
#include <stdint.h>         // intptr_t
#endif
#include "imgui_plot.h"
#include <chrono>

// Visual Studio warnings
#ifdef _MSC_VER
#pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#endif
#include <vector>
#include "GameObject3D.h"
#include "GameObject3DAlt.h"

// Clang/GCC warnings with -Weverything
#if defined(__clang__)
#if __has_warning("-Wunknown-warning-option")
#pragma clang diagnostic ignored "-Wunknown-warning-option"         // warning: unknown warning group 'xxx'                     // not all warnings are known by all Clang versions and they tend to be rename-happy.. so ignoring warnings triggers new warnings on some configuration. Great!
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"                // warning: unknown warning group 'xxx'
#pragma clang diagnostic ignored "-Wold-style-cast"                 // warning: use of old-style cast                           // yes, they are more terse.
#pragma clang diagnostic ignored "-Wdeprecated-declarations"        // warning: 'xx' is deprecated: The POSIX name for this..   // for strdup used in demo code (so user can copy & paste the code)
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"       // warning: cast to 'void *' from smaller integer type
#pragma clang diagnostic ignored "-Wformat-security"                // warning: format string is not a string literal
#pragma clang diagnostic ignored "-Wexit-time-destructors"          // warning: declaration requires an exit-time destructor    // exit-time destruction order is undefined. if MemFree() leads to users code that has been disabled before exit it might cause problems. ImGui coding style welcomes static/globals.
#pragma clang diagnostic ignored "-Wunused-macros"                  // warning: macro is not used                               // we define snprintf/vsnprintf on Windows so they are available, but not always used.
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"  // warning: zero as null pointer constant                   // some standard header variations use #define NULL 0
#pragma clang diagnostic ignored "-Wdouble-promotion"               // warning: implicit conversion from 'float' to 'double' when passing argument to function  // using printf() is a misery with this as C++ va_arg ellipsis changes float to double.
#pragma clang diagnostic ignored "-Wreserved-id-macro"              // warning: macro name is a reserved identifier
#pragma clang diagnostic ignored "-Wimplicit-int-float-conversion"  // warning: implicit conversion from 'xxx' to 'float' may lose precision
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wpragmas"                  // warning: unknown option after '#pragma GCC diagnostic' kind
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"      // warning: cast to pointer from integer of different size
#pragma GCC diagnostic ignored "-Wformat-security"          // warning: format string is not a string literal (potentially insecure)
#pragma GCC diagnostic ignored "-Wdouble-promotion"         // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma GCC diagnostic ignored "-Wconversion"               // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#pragma GCC diagnostic ignored "-Wmisleading-indentation"   // [__GNUC__ >= 6] warning: this 'if' clause does not guard this statement      // GCC 6.0+ only. See #883 on GitHub.
#endif

// Play it nice with Windows users (Update: May 2018, Notepad now supports Unix-style carriage returns!)
#ifdef _WIN32
#define IM_NEWLINE  "\r\n"
#else
#define IM_NEWLINE  "\n"
#endif

// Helpers
#if defined(_MSC_VER) && !defined(snprintf)
#define snprintf    _snprintf
#endif
#if defined(_MSC_VER) && !defined(vsnprintf)
#define vsnprintf   _vsnprintf
#endif

// Helpers macros
// We normally try to not use many helpers in imgui_demo.cpp in order to make code easier to copy and paste,
// but making an exception here as those are largely simplifying code...
// In other imgui sources we can use nicer internal functions from imgui_internal.h (ImMin/ImMax) but not in the demo.
#define IM_MIN(A, B)            (((A) < (B)) ? (A) : (B))
#define IM_MAX(A, B)            (((A) >= (B)) ? (A) : (B))
#define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))

// Enforce cdecl calling convention for functions called by the standard library, in case compilation settings changed the default to e.g. __vectorcall
#ifndef IMGUI_CDECL
#ifdef _MSC_VER
#define IMGUI_CDECL __cdecl
#else
#define IMGUI_CDECL
#endif
#endif

//-----------------------------------------------------------------------------
// [SECTION] Forward Declarations, Helpers
//-----------------------------------------------------------------------------


// Forward Declarations
static void ShowExampleAppSimpleOverlay(bool* p_open);


// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
//static void HelpMarker(const char* desc)
//{
//    ImGui::TextDisabled("(?)");
//    if (ImGui::IsItemHovered())
//    {
//        ImGui::BeginTooltip();
//        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
//        ImGui::TextUnformatted(desc);
//        ImGui::PopTextWrapPos();
//        ImGui::EndTooltip();
//    }
//}

// Helper to display basic user controls.
//void ImGui::ShowUserGuide()
//{
//    ImGuiIO& io = ImGui::GetIO();
//    ImGui::BulletText("Double-click on title bar to collapse window.");
//    ImGui::BulletText(
//        "Click and drag on lower corner to resize window\n"
//        "(double-click to auto fit window to its contents).");
//    ImGui::BulletText("CTRL+Click on a slider or drag box to input value as text.");
//    ImGui::BulletText("TAB/SHIFT+TAB to cycle through keyboard editable fields.");
//    if (io.FontAllowUserScaling)
//        ImGui::BulletText("CTRL+Mouse Wheel to zoom window contents.");
//    ImGui::BulletText("While inputing text:\n");
//    ImGui::Indent();
//    ImGui::BulletText("CTRL+Left/Right to word jump.");
//    ImGui::BulletText("CTRL+A or double-click to select all.");
//    ImGui::BulletText("CTRL+X/C/V to use clipboard cut/copy/paste.");
//    ImGui::BulletText("CTRL+Z,CTRL+Y to undo/redo.");
//    ImGui::BulletText("ESCAPE to revert.");
//    ImGui::BulletText("You can apply arithmetic operators +,*,/ on numerical values.\nUse +- to subtract.");
//    ImGui::Unindent();
//    ImGui::BulletText("With keyboard navigation enabled:");
//    ImGui::Indent();
//    ImGui::BulletText("Arrow keys to navigate.");
//    ImGui::BulletText("Space to activate a widget.");
//    ImGui::BulletText("Return to input text into a widget.");
//    ImGui::BulletText("Escape to deactivate a widget, close popup, exit child window.");
//    ImGui::BulletText("Alt to jump to the menu layer of a window.");
//    ImGui::BulletText("CTRL+Tab to select a window.");
//    ImGui::Unindent();
//}
constexpr size_t buf_size = 11;
static float x_data[buf_size]{ 1,2,4,8,16,32,64,128,256,512,1024 };
static float y_int[buf_size]{};
static float y_gameObject3d[buf_size];
static float y_gameObject3dAlt[buf_size];
bool intDataGenerated{ false };
bool gameObject3dDataGenerated{ false };
bool gameObject3dAltDataGenerated{ false };

void GenerateIntData() {
    std::vector<int> arrInt{};
    for (int i{ 0 }; i < 1000000; i++) {
        arrInt.push_back(1);
    }
    int stepSize{ 1 };
    for (int i{ 0 }; i < buf_size; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t e{ 0 }; e < arrInt.size(); e += stepSize) {
            arrInt.at(e) *= 2;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        y_int[i] = (float)duration;
        stepSize *= 2;
    }
}
void GenerateGameObject3dData() {
    std::vector<GameObject3D> arrGameObject3d{};
    for (int i{ 0 }; i < 1000000; i++) {
        arrGameObject3d.push_back(GameObject3D());
    }
    int stepSize{ 1 };
    for (int i{ 0 }; i < buf_size; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t e{ 0 }; e < arrGameObject3d.size(); e += stepSize) {
            arrGameObject3d.at(e).ID *= 2;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        y_gameObject3d[i] = (float)duration;
        stepSize *= 2;
    }
}
void GenerateGameObject3dAltData() {
    std::vector<GameObject3DAlt> arrGameObject3dAlt{};
    for (int i{ 0 }; i < 1000000; i++) {
        arrGameObject3dAlt.push_back(GameObject3DAlt());
    }
    int stepSize{ 1 };
    for (int i{ 0 }; i < buf_size; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t e{ 0 }; e < arrGameObject3dAlt.size(); e += stepSize) {
            arrGameObject3dAlt.at(e).ID *= 2;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        y_gameObject3dAlt[i] = (float)duration;
        stepSize *= 2;
    }
}

void ImGui::ShowGraphs(bool*) {
    static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
    static uint32_t selection_start = 0, selection_length = 0;
    ImGui::PlotConfig conf;

    ImGui::Begin("Exercise 1: int", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::Button("Generate data for int's")) {
        GenerateIntData();
        intDataGenerated = true;
    }
    if (intDataGenerated) {
        conf.values.xs = x_data;
        conf.values.ys = y_int;
        conf.values.count = buf_size;
        conf.values.color = ImColor(0, 255, 0);
        conf.scale.min = 0;
        conf.scale.max = y_int[0];
        conf.tooltip.show = true;
        conf.grid_x.show = true;
        conf.grid_x.size = 250;
        conf.grid_x.subticks = 2;
        conf.grid_y.show = true;
        conf.grid_y.size = 10000;
        conf.grid_y.subticks = 2;
        conf.selection.show = true;
        conf.selection.start = &selection_start;
        conf.selection.length = &selection_length;
        conf.frame_size = ImVec2(300, 200);

        ImGui::Plot("intData", conf);
    }
    ImGui::End();

    ImGui::Begin("Exercise 2: GameObject3D", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::Button("Generate data for GameObject3D")) {
        GenerateGameObject3dData();
        gameObject3dDataGenerated = true;
    }
    if (gameObject3dDataGenerated) {
        conf.values.ys = y_gameObject3d;
        conf.scale.max = y_gameObject3d[0];

        ImGui::Plot("GameObject3dData", conf);
    }
    if (ImGui::Button("Generate data for GameObject3dAlt")) {
        GenerateGameObject3dAltData();
        gameObject3dAltDataGenerated = true;
    }
    if (gameObject3dAltDataGenerated) {
        conf.values.ys = y_gameObject3dAlt;
        conf.scale.max = y_gameObject3dAlt[0];

        ImGui::Plot("GameObject3dAltData", conf);
    }
    ImGui::End();
}

//static void ShowExampleAppSimpleOverlay(bool* p_open)
//{
//    ImGui::SetNextWindowSize(ImVec2(300, 240), ImGuiCond_FirstUseEver);
//    if (ImGui::Begin("Exercise 1", p_open, ImGuiWindowFlags_None))
//    {
//       
//    }
//    ImGui::End();
//}