#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "Includes/Icon.h"
#include "Includes/include/Includes.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_android.h"
#include "Includes/import.h"
using namespace Tools;
#include "hooks.h"



ImVec4 AccentColor = ImVec4(1.00f, 0.16f, 0.42f, 1.0f); // Vibrant Pink

void SetupModernStyle()
{
    ImGuiStyle& s = ImGui::GetStyle();

    s.FrameRounding = 6.f;
    s.WindowRounding = 8.f;
    s.ChildRounding = 6.f;
    s.ScrollbarRounding = 6.f;
    s.GrabRounding = 6.f;
    s.TabRounding = 6.f;

    s.FramePadding = ImVec2(16, 12);
    s.ItemSpacing = ImVec2(14, 14);
    s.WindowPadding = ImVec2(18, 18);

    s.WindowBorderSize = 0.f;
    s.FrameBorderSize = 0.f;
    s.PopupBorderSize = 0.f;

    ImVec4 bg  = ImVec4(0.07f, 0.07f, 0.09f, 0.85f);
    ImVec4 bg2 = ImVec4(0.11f, 0.11f, 0.14f, 0.60f);
    ImVec4 hov = ImVec4(0.18f, 0.18f, 0.22f, 1.00f);
    ImVec4 act = ImVec4(0.24f, 0.24f, 0.30f, 1.00f);
    ImVec4 text = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);

    s.Colors[ImGuiCol_Text] = text;
    s.Colors[ImGuiCol_WindowBg] = bg;
    s.Colors[ImGuiCol_ChildBg] = bg2;
    s.Colors[ImGuiCol_PopupBg] = bg2;

    s.Colors[ImGuiCol_FrameBg] = bg2;
    s.Colors[ImGuiCol_FrameBgHovered] = hov;
    s.Colors[ImGuiCol_FrameBgActive] = act;

    s.Colors[ImGuiCol_Button] = bg2;
    s.Colors[ImGuiCol_ButtonHovered] = hov;
    s.Colors[ImGuiCol_ButtonActive] = act;

    s.Colors[ImGuiCol_Header] = bg2;
    s.Colors[ImGuiCol_HeaderHovered] = hov;
    s.Colors[ImGuiCol_HeaderActive] = act;

    s.Colors[ImGuiCol_Separator] = bg2;
    s.Colors[ImGuiCol_SeparatorHovered] = hov;
    s.Colors[ImGuiCol_SeparatorActive] = act;

    s.Colors[ImGuiCol_Tab] = bg2;
    s.Colors[ImGuiCol_TabHovered] = hov;
    s.Colors[ImGuiCol_TabActive] = act;
    s.Colors[ImGuiCol_TabUnfocused] = bg2;
    s.Colors[ImGuiCol_TabUnfocusedActive] = hov;

    ImGui::GetStyle().ScaleAllSizes(1.5f);
}

void ApplyAccentColor() {
    ImGuiStyle& style = ImGui::GetStyle();

    style.Colors[ImGuiCol_Button] = AccentColor;
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(AccentColor.x + 0.1f, AccentColor.y + 0.1f, AccentColor.z + 0.1f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(AccentColor.x - 0.1f, AccentColor.y - 0.1f, AccentColor.z - 0.1f, 1.0f);

    style.Colors[ImGuiCol_ResizeGrip] = AccentColor;
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(AccentColor.x + 0.1f, AccentColor.y + 0.1f, AccentColor.z + 0.1f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(AccentColor.x - 0.1f, AccentColor.y - 0.1f, AccentColor.z - 0.1f, 1.0f);

    style.Colors[ImGuiCol_SliderGrab] = AccentColor;
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(AccentColor.x - 0.1f, AccentColor.y - 0.1f, AccentColor.z - 0.1f, 1.0f);

    style.Colors[ImGuiCol_CheckMark] = AccentColor;
    style.Colors[ImGuiCol_Header] = AccentColor;
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(AccentColor.x + 0.1f, AccentColor.y + 0.1f, AccentColor.z + 0.1f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(AccentColor.x - 0.1f, AccentColor.y - 0.1f, AccentColor.z - 0.1f, 1.0f);

    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    
    style.Colors[ImGuiCol_TabActive] = AccentColor;
    style.Colors[ImGuiCol_TabHovered] = ImVec4(AccentColor.x + 0.1f, AccentColor.y + 0.1f, AccentColor.z + 0.1f, 1.0f);
}

void SetupFontAwesomeIcons() {
    if (icons_font) {
        return; 
    }

    ImGuiIO& io = ImGui::GetIO();

    float fontBaseSize = 1.0f; 
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    float iconFontSize = fontBaseSize * 8.0f / 7.0f;

    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = iconFontSize;
    icons_config.OversampleH = 2.5;
    icons_config.OversampleV = 2.5;

    icons_font = io.Fonts->AddFontFromMemoryCompressedTTF(
        font_awesome_data,
        font_awesome_size,
        iconFontSize,
        &icons_config,
        icons_ranges
    );

    if (!icons_font) {
        font_load_failed = true;
        return;
    }

    static const ImWchar custom_font_ranges[] = { 0x0400, 0x052F, 0 };
    ImFontConfig custom_font_config;
    custom_font_config.FontDataOwnedByAtlas = false;

    io.Fonts->AddFontFromMemoryCompressedTTF(
        font_awesome_data,
        font_awesome_size,
        iconFontSize,
        &icons_config,
        icons_ranges
    );
}




//int screenWidth = 0;
//int screenHeight = 0;
bool g_Initialized = false;
ImGuiWindow* g_window = NULL;


ImColor boxColor = ImColor(225, 0, 0, 255);
ImColor lineColor = ImColor(225, 0, 0, 255);
ImColor ggColor = ImColor(225, 0, 0, 255);                       

extern "C" {
    JNIEXPORT void JNICALL Java_com_Cat_mod_GLES3JNIView_init(JNIEnv* env, jclass cls);
    JNIEXPORT void JNICALL Java_com_Cat_mod_GLES3JNIView_resize(JNIEnv* env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_com_Cat_mod_GLES3JNIView_step(JNIEnv* env, jobject obj);
	JNIEXPORT void JNICALL Java_com_Cat_mod_GLES3JNIView_imgui_Shutdown(JNIEnv* env, jobject obj);
	JNIEXPORT void JNICALL Java_com_Cat_mod_GLES3JNIView_MotionEventClick(JNIEnv* env, jobject obj,jboolean down,jfloat PosX,jfloat PosY);
	JNIEXPORT jstring JNICALL Java_com_Cat_mod_GLES3JNIView_getWindowRect(JNIEnv *env, jobject thiz);
	JNIEXPORT void JNICALL Java_com_Cat_mod_GLES3JNIView_real(JNIEnv* env, jobject obj, jint width, jint height);
};

JNIEXPORT void JNICALL
Java_com_Cat_mod_GLES3JNIView_init(JNIEnv* env, jclass cls) {
    if (g_Initialized) return;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();
    SetupModernStyle();

    io.Fonts->AddFontDefault();
    io.FontGlobalScale = 2.0f;

    ImGui_ImplOpenGL3_Init("#version 300 es");

    g_Initialized = true;
}
JNIEXPORT void JNICALL
Java_com_Cat_mod_GLES3JNIView_resize(JNIEnv* env, jobject obj, jint width, jint height) {
	screenWidth = (int) width;
    screenHeight = (int) height;
	glViewport(0, 0, width, height);
	ImGuiIO &io = ImGui::GetIO();
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.IniFilename = NULL;
	ImGui::GetIO().DisplaySize = ImVec2((float)width, (float)height);
}



void ImGuiShowDemo(bool* p_open) {
    ImGui::ShowDemoWindow(p_open);
}





int selectedTab = 0;

// Variables for Tab Animations
float tabAlpha = 1.0f;
float tabSlideY = 0.0f;

// Variables for Menu Open/Close Animation
bool isMenuOpen = true;
float menuAlpha = 1.0f;

struct Particle {
    ImVec2 pos;
    ImVec2 vel;
    float radius;
    ImVec4 color;
};

std::vector<Particle> particles;
bool particlesInit = false;

void DrawParticles(float alphaMultiplier) {
    if (alphaMultiplier <= 0.0f) return;
    
    ImVec2 winPos = ImGui::GetWindowPos();
    ImVec2 winSize = ImGui::GetWindowSize();

    if (!particlesInit && winSize.x > 0 && winSize.y > 0) {
        for (int i = 0; i < 60; ++i) {
            Particle p;
            p.pos.x = (float)(rand() % (int)winSize.x);
            p.pos.y = (float)(rand() % (int)winSize.y);
            p.vel.x = ((float)(rand() % 100) / 100.0f - 0.5f) * 2.0f; 
            p.vel.y = ((float)(rand() % 100) / 100.0f - 0.5f) * 2.0f; 
            p.radius = 2.0f + (float)(rand() % 10) / 10.0f;
            
            int colorType = rand() % 3;
            if (colorType == 0) p.color = ImVec4(1.0f, 0.2f, 0.3f, 0.8f); // Red
            else if (colorType == 1) p.color = ImVec4(0.2f, 1.0f, 0.4f, 0.8f); // Green
            else p.color = ImVec4(0.2f, 0.5f, 1.0f, 0.8f); // Blue
            
            particles.push_back(p);
        }
        particlesInit = true;
    }
    
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    
    ImVec2 mousePos = ImVec2(io.MousePos.x - winPos.x, io.MousePos.y - winPos.y);
    bool isMouseDown = io.MouseDown[0];

    for (size_t i = 0; i < particles.size(); ++i) {
        Particle& p = particles[i];
        
        p.pos.x += p.vel.x * io.DeltaTime * 60.0f;
        p.pos.y += p.vel.y * io.DeltaTime * 60.0f;
        
        if (p.pos.x < 0) { p.pos.x = 0; p.vel.x *= -1.0f; }
        if (p.pos.x > winSize.x) { p.pos.x = winSize.x; p.vel.x *= -1.0f; }
        if (p.pos.y < 0) { p.pos.y = 0; p.vel.y *= -1.0f; }
        if (p.pos.y > winSize.y) { p.pos.y = winSize.y; p.vel.y *= -1.0f; }
        
        float dx = mousePos.x - p.pos.x;
        float dy = mousePos.y - p.pos.y;
        float dist = sqrt(dx*dx + dy*dy);
        
        if (dist < 200.0f) {
            float interactionAlpha = (1.0f - dist/200.0f) * alphaMultiplier;
            draw_list->AddLine(
                ImVec2(winPos.x + p.pos.x, winPos.y + p.pos.y), 
                ImVec2(winPos.x + mousePos.x, winPos.y + mousePos.y), 
                ImColor(p.color.x, p.color.y, p.color.z, 0.5f * interactionAlpha), 1.5f);
            
            if (isMouseDown) {
                p.vel.x += (dx / dist) * 0.15f;
                p.vel.y += (dy / dist) * 0.15f;
            } else {
                p.vel.x -= (dx / dist) * 0.05f;
                p.vel.y -= (dy / dist) * 0.05f;
            }
        }
        
        float speed = sqrt(p.vel.x*p.vel.x + p.vel.y*p.vel.y);
        if (speed > 4.0f) {
            p.vel.x = (p.vel.x / speed) * 4.0f;
            p.vel.y = (p.vel.y / speed) * 4.0f;
        } else if (speed < 0.5f && !isMouseDown) {
            p.vel.x *= 1.01f;
            p.vel.y *= 1.01f;
        }

        for (size_t j = i + 1; j < particles.size(); ++j) {
            Particle& p2 = particles[j];
            float dx2 = p.pos.x - p2.pos.x;
            float dy2 = p.pos.y - p2.pos.y;
            float dist2 = sqrt(dx2*dx2 + dy2*dy2);
            if (dist2 < 120.0f) {
                float lineAlpha = 0.6f * (1.0f - dist2 / 120.0f) * alphaMultiplier;
                draw_list->AddLine(
                    ImVec2(winPos.x + p.pos.x, winPos.y + p.pos.y), 
                    ImVec2(winPos.x + p2.pos.x, winPos.y + p2.pos.y), 
                    ImColor((p.color.x + p2.color.x)/2.0f, (p.color.y + p2.color.y)/2.0f, (p.color.z + p2.color.z)/2.0f, lineAlpha), 1.0f);
            }
        }
        
        draw_list->AddCircleFilled(
            ImVec2(winPos.x + p.pos.x, winPos.y + p.pos.y), 
            p.radius, 
            ImColor(p.color.x, p.color.y, p.color.z, p.color.w * alphaMultiplier));
    }
}

void BeginDraw() {
    
    ApplyAccentColor();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::SetNextWindowSize(ImVec2(1000, 640), ImGuiCond_FirstUseEver);
    
    // Apply Menu Fade Alpha
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, menuAlpha);
    
    if (ImGui::Begin("Java Based - ImGui 32 x 64", nullptr, ImGuiWindowFlags_NoSavedSettings)) {
        g_window = ImGui::GetCurrentWindow();

        // Draw particles completely inside the UI
        DrawParticles(menuAlpha);

        ImGui::BeginChild("Sidebar", ImVec2(200, 0), true);

        const char* tabs[] = {
            "Dashboard",
            "Player",
            "Visuals",
            "Settings",
            "About"
        };

        for (int i = 0; i < IM_ARRAYSIZE(tabs); i++) {
            if (ImGui::Selectable(tabs[i], selectedTab == i, 0, ImVec2(180, 40))) {
                if (selectedTab != i) {
                    selectedTab = i;
                    tabAlpha = 0.0f;
                    tabSlideY = 30.0f; // Slide distance
                }
            }
        }

        ImGui::EndChild();
        ImGui::SameLine();

        // Animate Tabs (No lambdas)
        if (tabAlpha < 1.0f) {
            tabAlpha += io.DeltaTime * 6.0f; // Fade speed
            if (tabAlpha > 1.0f) tabAlpha = 1.0f;
        }
        if (tabSlideY > 0.0f) {
            tabSlideY -= io.DeltaTime * 150.0f; // Slide speed
            if (tabSlideY < 0.0f) tabSlideY = 0.0f;
        }

        ImGui::BeginChild("MainContent", ImVec2(0, 0), true);
        
        // Apply Tab Animation
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tabAlpha);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + tabSlideY);

        switch (selectedTab) {
        case 0:
            ImGui::Text("Dashboard");
            ImGui::Separator();
            ImGui::Text("Screen: %dx%d", screenWidth, screenHeight);
            ImGui::Text("FPS: %.1f", io.Framerate);
            ImGui::Text("Time per frame: %.3f ms", 1000.0f / io.Framerate);
            break;

        case 1:
            ImGui::Text("Player Controls");
            ImGui::Separator();
            ImGui::SliderFloat("Speed", &speed, 0.1f, 10.0f);
            ImGui::Checkbox("God Mode", &godmode);
            break;

        case 2:
            ImGui::Text("Visual Settings");
            ImGui::Separator();
            ImGui::Checkbox("Enable Example", &Health);
            break;

        case 3:
            ImGui::Text("Settings");
            ImGui::Separator();
            ImGui::ColorEdit3("Accent", (float*)&AccentColor);
            break;

        case 4:
            ImGui::Text("About & Credits");
            ImGui::Separator();
            ImGui::Text("Developed by CatmodRX");
            ImGui::Text("Telegram : @CatmodRX_op_mods");
            ImGui::Separator();
            ImGui::Text("DeathZoneMod");
            ImGui::Text("Telegram : @DeathZoneMod");
            break;
        }
        
        ImGui::PopStyleVar(); // Pop Tab Alpha
        ImGui::EndChild();
    }
    ImGui::End();
    
    ImGui::PopStyleVar(); // Pop Menu Alpha
}





bool isAuthenticated = false;
char loginKeyBuf[64] = "";
char loginMessage[128] = "";
bool showKeyboard = false;
bool capsLock = false;

// Custom ImGui On-Screen Keyboard for login key entry
void DrawImGuiKeyboard(char* buf, int bufSize) {
    ImGui::SetNextWindowSize(ImVec2(screenWidth * 0.95f, 340), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(screenWidth * 0.025f, screenHeight - 360), ImGuiCond_FirstUseEver);
    
    ImGui::Begin("Modcat Keyboard", NULL, 
        ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoScrollbar | 
        ImGuiWindowFlags_NoSavedSettings);

    int len = (int)strlen(buf);
    float btnW = (ImGui::GetContentRegionAvail().x - 9 * ImGui::GetStyle().ItemSpacing.x) / 10.0f;
    float btnH = 45.0f;

    // Row 1: Numbers 1-0
    const char* numRow[] = {"1","2","3","4","5","6","7","8","9","0"};
    for (int i = 0; i < 10; i++) {
        if (i > 0) ImGui::SameLine();
        if (ImGui::Button(numRow[i], ImVec2(btnW, btnH))) {
            if (len < bufSize - 1) {
                buf[len] = numRow[i][0];
                buf[len + 1] = '\0';
            }
        }
    }

    // Row 2: Q-P
    const char* row2[] = {"Q","W","E","R","T","Y","U","I","O","P"};
    for (int i = 0; i < 10; i++) {
        if (i > 0) ImGui::SameLine();
        const char* label = row2[i];
        if (ImGui::Button(label, ImVec2(btnW, btnH))) {
            if (len < bufSize - 1) {
                char c = label[0];
                if (!capsLock) c = c + 32; // lowercase
                buf[len] = c;
                buf[len + 1] = '\0';
            }
        }
    }

    // Row 3: A-L
    const char* row3[] = {"A","S","D","F","G","H","J","K","L"};
    float row3Offset = (ImGui::GetContentRegionAvail().x - 9 * btnW - 8 * ImGui::GetStyle().ItemSpacing.x) * 0.5f;
    if (row3Offset > 0) ImGui::SetCursorPosX(ImGui::GetCursorPosX() + row3Offset);
    for (int i = 0; i < 9; i++) {
        if (i > 0) ImGui::SameLine();
        const char* label = row3[i];
        if (ImGui::Button(label, ImVec2(btnW, btnH))) {
            if (len < bufSize - 1) {
                char c = label[0];
                if (!capsLock) c = c + 32;
                buf[len] = c;
                buf[len + 1] = '\0';
            }
        }
    }

    // Row 4: CAPS Z-M BACK
    const char* row4[] = {"Z","X","C","V","B","N","M"};
    
    // Caps button
    ImVec4 capsColor = capsLock ? AccentColor : ImGui::GetStyle().Colors[ImGuiCol_Button];
    ImGui::PushStyleColor(ImGuiCol_Button, capsColor);
    if (ImGui::Button("CAP", ImVec2(btnW, btnH))) {
        capsLock = !capsLock;
    }
    ImGui::PopStyleColor();
    ImGui::SameLine();

    for (int i = 0; i < 7; i++) {
        const char* label = row4[i];
        if (ImGui::Button(label, ImVec2(btnW, btnH))) {
            if (len < bufSize - 1) {
                char c = label[0];
                if (!capsLock) c = c + 32;
                buf[len] = c;
                buf[len + 1] = '\0';
            }
        }
        ImGui::SameLine();
    }

    // Backspace
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
    if (ImGui::Button("<--", ImVec2(btnW, btnH))) {
        if (len > 0) {
            buf[len - 1] = '\0';
        }
    }
    ImGui::PopStyleColor();

    // Row 5: Special keys
    if (ImGui::Button("-", ImVec2(btnW, btnH))) {
        if (len < bufSize - 1) { buf[len] = '-'; buf[len+1] = '\0'; }
    }
    ImGui::SameLine();
    if (ImGui::Button("_", ImVec2(btnW, btnH))) {
        if (len < bufSize - 1) { buf[len] = '_'; buf[len+1] = '\0'; }
    }
    ImGui::SameLine();
    if (ImGui::Button("SPACE", ImVec2(btnW * 4 + ImGui::GetStyle().ItemSpacing.x * 3, btnH))) {
        if (len < bufSize - 1) { buf[len] = ' '; buf[len+1] = '\0'; }
    }
    ImGui::SameLine();
    if (ImGui::Button(".", ImVec2(btnW, btnH))) {
        if (len < bufSize - 1) { buf[len] = '.'; buf[len+1] = '\0'; }
    }
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.7f, 0.3f, 1.0f));
    if (ImGui::Button("DONE", ImVec2(btnW * 2 + ImGui::GetStyle().ItemSpacing.x, btnH))) {
        showKeyboard = false;
    }
    ImGui::PopStyleColor();

    ImGui::End();
}

extern "C" JNIEXPORT void JNICALL Java_com_Cat_mod_GLES3JNIView_setLoginKey(JNIEnv* env, jclass cls, jstring key) {
    const char* c_key = env->GetStringUTFChars(key, NULL);
    if (c_key != NULL) {
        strncpy(loginKeyBuf, c_key, sizeof(loginKeyBuf) - 1);
        loginKeyBuf[sizeof(loginKeyBuf) - 1] = '\0';
        env->ReleaseStringUTFChars(key, c_key);
    }
}

bool VerifyKeyWithServer(JNIEnv* env, const char* key) {
    jclass cls = env->FindClass("com/Cat/mod/GLES3JNIView");
    if (!cls) return false;
    
    jmethodID methodId = env->GetStaticMethodID(cls, "verifyKey", "(Ljava/lang/String;)Ljava/lang/String;");
    if (!methodId) return false;
    
    jstring jKey = env->NewStringUTF(key);
    jstring resultStr = (jstring)env->CallStaticObjectMethod(cls, methodId, jKey);
    env->DeleteLocalRef(jKey);
    
    if (!resultStr) return false;
    
    const char* cResult = env->GetStringUTFChars(resultStr, NULL);
    bool isValid = (strstr(cResult, "\"valid\":true") != NULL);
    env->ReleaseStringUTFChars(resultStr, cResult);
    
    return isValid;
}

JNIEXPORT void JNICALL
Java_com_Cat_mod_GLES3JNIView_step(JNIEnv* env, jobject obj) {
    
	ImGuiIO& io = ImGui::GetIO();
	bool show_demo_window = true;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(screenWidth,  screenHeight);
    ImGui::NewFrame();       
ImGuiStyle& style = ImGui::GetStyle();
ImVec4* colors = style.Colors;

colors[ImGuiCol_SliderGrab]       = ImVec4(0.30f, 0.60f, 1.00f, 1.00f); 
colors[ImGuiCol_SliderGrabActive] = ImVec4(0.45f, 0.75f, 1.00f, 1.00f); 
style.GrabMinSize = 10.0f;   
style.GrabRounding = 5.0f;  
	
    if (!isAuthenticated) {
        ImGui::SetNextWindowSize(ImVec2(screenWidth * 0.8f, showKeyboard ? 220 : 300), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(screenWidth * 0.1f, 40), ImGuiCond_FirstUseEver);
        ImGui::Begin("Modcat Login", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
        g_window = ImGui::GetCurrentWindow(); // Set for Java side vTouch mapping
        
        // Draw particles inside the login panel too
        DrawParticles(1.0f);

        ImGui::Text("Please enter your Access Key:");
        ImGui::Spacing();
        
        // Show the key buffer as read-only text display
        ImGui::InputText("##Key", loginKeyBuf, IM_ARRAYSIZE(loginKeyBuf), ImGuiInputTextFlags_ReadOnly);
        
        // Tap to toggle keyboard
        if (ImGui::IsItemClicked()) {
            showKeyboard = !showKeyboard;
        }
        ImGui::Spacing();
        
        if (ImGui::Button("Login", ImVec2(120, 40))) {
            if (strlen(loginKeyBuf) > 0) {
                if (VerifyKeyWithServer(env, loginKeyBuf)) {
                    isAuthenticated = true;
                    isMenuOpen = true; 
                } else {
                    strcpy(loginMessage, "Invalid Key or Expired!");
                }
            } else {
                strcpy(loginMessage, "Please enter a key.");
            }
        }
        
        if (strlen(loginMessage) > 0) {
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "%s", loginMessage);
        }
        
        if (showKeyboard) {
            DrawImGuiKeyboard(loginKeyBuf, IM_ARRAYSIZE(loginKeyBuf));
        }

        ImGui::End();
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return; // Skip rendering the rest until authenticated
    }
    // Menu Open/Close Animation Logic
    if (isMenuOpen) {
        if (menuAlpha < 1.0f) {
            menuAlpha += io.DeltaTime * 6.0f;
            if (menuAlpha > 1.0f) menuAlpha = 1.0f;
        }
    } else {
        if (menuAlpha > 0.0f) {
            menuAlpha -= io.DeltaTime * 6.0f;
            if (menuAlpha < 0.0f) menuAlpha = 0.0f;
        }
    }

    if (menuAlpha > 0.0f) {
        BeginDraw();
    }

    // Floating Button to toggle Menu
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0)); // Transparent bg for button window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    if (ImGui::Begin("FloatingIcon", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) {
        if (ImGui::Button(isMenuOpen ? "Hide" : "Modcat", ImVec2(80, 80))) {
            isMenuOpen = !isMenuOpen;
        }
    }
    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    ImGui::Render();
	glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}



void StartBackend(JNIEnv* env){
    //Input
	
	#if defined(__aarch64__)
        A64HookFunction((void*)env->functions->RegisterNatives, (void*)hook_RegisterNatives, (void **)&old_RegisterNatives);
#else
        MSHookFunction((void*)env->functions->RegisterNatives, (void*)hook_RegisterNatives, (void **)&old_RegisterNatives);
#endif

}
JNIEXPORT void JNICALL Java_com_Cat_mod_GLES3JNIView_imgui_Shutdown(JNIEnv* env, jobject obj){
    if (!g_Initialized)
        return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    g_Initialized=false;
}

JNIEXPORT void JNICALL Java_com_Cat_mod_GLES3JNIView_MotionEventClick(JNIEnv* env, jobject obj,jboolean down,jfloat PosX,jfloat PosY){
	ImGuiIO & io = ImGui::GetIO();
	io.MouseDown[0] = down;
	io.MousePos = ImVec2(PosX,PosY);
}

JNIEXPORT jstring JNICALL Java_com_Cat_mod_GLES3JNIView_getWindowRect(JNIEnv *env, jobject thiz) {
    char result[256]="0|0|0|0";
    if (!isAuthenticated) {
        // During login, we want the whole screen to be interactive for the custom keyboard
        sprintf(result, "0|0|%d|%d", screenWidth, screenHeight);
    } else if (g_window) {
        sprintf(result, "%d|%d|%d|%d", (int)g_window->Pos.x, (int)g_window->Pos.y, (int)g_window->Size.x, (int)g_window->Size.y);
    }
    return env->NewStringUTF(result);
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *globalEnv;
    vm->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);
    publicVM = vm;
    publicEnv = globalEnv;
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
    return JNI_VERSION_1_6;
	StartBackend(globalEnv);
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *vm, void *reserved) {}

