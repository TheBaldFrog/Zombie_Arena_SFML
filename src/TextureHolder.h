#pragma once

#include <SFML/Graphics.hpp>
#include <map>

using namespace std;
using namespace sf;

class TextureHolder
{
private:
    map<string, Texture> m_Texture;
    static TextureHolder *m_s_Instance;

public:
    TextureHolder();
    static Texture &GetTexture(string const &filename);
};