#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>

#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "Includes/Vector2.hpp"
#include "Includes/Vector3.hpp"
#include "Includes/Quaternion.hpp"
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Includes.h"
#include "Includes/Tools.h"
#include "Includes/fake_dlfcn.h"
#include "Includes/Il2Cpp.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h> 

#include <SOCKET/server.h>

#include "Includes/Macros.h"
#include "ImGui/imgui.h"
#include "ImGui/ESP.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_android.h"
#include "MonoString.h"
#include "Data/Fonts/Roboto-Regular.h"
//Target lib here
#define targetLibName OBFUSCATE("libFileA.so")

//read write data
void write_file (std::string path,std::string str) 
{
  std::ofstream myfile;
  myfile.open (path);
  myfile << str;
  myfile.close();
}
std::string float_to_string (float value) 
{
    std::string str; 
    str = std::to_string(value);
    return str;
}
char string_to_char(std::string str) 
{
    std::string convert = str;
    int get_len = convert.length();
    char char_array[get_len + 1];
    strcpy(char_array, convert.c_str());
    for (int i = 0; i < get_len; i++)
    return char_array[i];
}
std::string int_to_string(int num)
{
     std::string str = to_string(num);
     return str;
}
float string_to_float (std::string str) 
{
    float value; 
    value = std::stoi(str); 
    return value;
}
string readFile(string file_path)
{
  string line;
  string output = "";
  ifstream myfile2 (file_path);
  if (myfile2.is_open())
  {
    while ( getline (myfile2,line) )
    {
      output = line;
      return output;
    }
    myfile2.close();
    return "";
  }
  else cout << "Unable to open file";
  return "";
}
