#ifndef ImGuiAndroid_ESP
#define ImGuiAndroid_ESP

#include "imgui_internal.h"

namespace ESP {
    void DrawLine(ImVec2 start, ImVec2 end, ImVec4 color) {
        auto background = ImGui::GetBackgroundDrawList();
        if(background) {
            background->AddLine(start, end, ImColor(color.x,color.y,color.z,color.w));
        }
    }
    void DrawBox(ImVec4 rect, ImVec4 color) {
        ImVec2 v1(rect.x, rect.y);
        ImVec2 v2(rect.x + rect.z, rect.y);
        ImVec2 v3(rect.x + rect.z, rect.y + rect.w);
        ImVec2 v4(rect.x, rect.y + rect.w);

        DrawLine(v1, v2, color);
        DrawLine(v2, v3, color);
        DrawLine(v3, v4, color);
        DrawLine(v4, v1, color);
    }
    void DrawCircle(float X, float Y, float radius, bool filled, ImVec4 color) {
        auto background = ImGui::GetBackgroundDrawList();
        if(background) {
            if(filled) {
                background->AddCircleFilled(ImVec2(X, Y), radius, ImColor(color.x,color.y,color.z,color.w));
            } else {
                background->AddCircle(ImVec2(X, Y), radius, ImColor(color.x,color.y,color.z,color.w));
            }
        }
    }
    void DrawText(ImVec2 position, ImVec4 color, const char *text) {
        auto background = ImGui::GetBackgroundDrawList();
        if(background) {
            background->AddText(NULL, 22.0f, position, ImColor(color.x,color.y,color.z,color.w), text);
        }
    }
    
    void DrawBox(ImVec2 p, ImVec2 size, float fontsize, ImVec4 color, const char *text)
    { 
        auto background = ImGui::GetBackgroundDrawList();
        ImVec2 textPos(p.x - (size.x/2) + (size.x - ImGui::CalcTextSize(text).x)/2, p.y + (size.y - ImGui::CalcTextSize(text).y)/2);
        background->AddRectFilled(ImVec2(p.x - (size.x/2), p.y) , ImVec2(p.x + (size.x/2), p.y + size.y), ImColor(color));
        background->AddText(NULL, fontsize, textPos, ImColor(1.0f, 1.0f, 1.0f, 1.0f), text);
    }
}

#endif ImGuiAndroid_ESP