#include <ranges>
#include <Geode/Geode.hpp>
#include <Geode/modify/EmoteSprite.hpp>
#include "../Emotes/Metadata.hpp"

using namespace geode::prelude;

class $modify(EmoteSprite) {
    static EmoteDef* defForName(const std::string& name) {
        for (auto& def: SoggyEmotes::Metadata::g_soggyEmotesMap | std::views::values)
            if (name == def.m_name)
                return &def;

        return EmoteSprite::defForName(name);
    }
};