#pragma once
#include <Geode/Geode.hpp>

namespace SoggyEmotes::Metadata {
    //just to be added to the particle index so we don't collide.
    constexpr auto g_soggyEmotesBase = 1000;

    static std::map<const char*, EmoteDef> g_soggyEmotesMap {
        {"soggy_original.png"_spr, {
            .m_name = "soggy",
            .m_particleIndex = g_soggyEmotesBase + 1,
            .m_scale = 1.0f,
            .m_x = 0.0f, .m_y = 0.0f,
            .m_color = cocos2d::ccColor3B(230, 230, 230),
            .m_isAlias = false
        }},

        {"soggy_cup.png"_spr, {
            .m_name = "soggy_cup",
            .m_particleIndex = g_soggyEmotesBase + 2,
            .m_scale = 1.0f,
            .m_x = 0.0f, .m_y = 0.0f,
            .m_color = cocos2d::ccColor3B(230, 230, 230),
            .m_isAlias = false
        }},

        {"soggy_dry.png"_spr, {
            .m_name = "soggy_dry",
            .m_particleIndex = g_soggyEmotesBase + 3,
            .m_scale = 1.0f,
            .m_x = 0.0f, .m_y = 0.0f,
            .m_color = cocos2d::ccColor3B(230, 230, 230),
            .m_isAlias = false
        }},

        {"soggy_fear.png"_spr, {
            .m_name = "soggy_fear",
            .m_particleIndex = g_soggyEmotesBase + 4,
            .m_scale = 1.0f,
            .m_x = 0.0f, .m_y = 0.0f,
            .m_color = cocos2d::ccColor3B(230, 230, 230),
            .m_isAlias = false
        }},

        {"soggy_sniff.png"_spr, {
            .m_name = "soggy_hey",
            .m_particleIndex = g_soggyEmotesBase + 5,
            .m_scale = 1.0f,
            .m_x = 0.0f, .m_y = 0.0f,
            .m_color = cocos2d::ccColor3B(230, 230, 230),
            .m_isAlias = false
        }},

        {"soggy_what.png"_spr, {
            .m_name = "soggy_what",
            .m_particleIndex = g_soggyEmotesBase + 6,
            .m_scale = 1.0f,
            .m_x = 0.0f, .m_y = 0.0f,
            .m_color = cocos2d::ccColor3B(230, 230, 230),
            .m_isAlias = false
        }}
    };

    inline EmoteDef* GetSoggyEmoteDefByIndex(const int tag) {
        for (auto& [_, def]: g_soggyEmotesMap) {
            if (def.m_particleIndex == tag)
                return &def;
        }

        return nullptr;
    }
}