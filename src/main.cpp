#include <Geode/Geode.hpp>
#include "Emotes/Metadata.hpp"

using namespace geode::prelude;

$on_game(Loaded) {
    //this way i dont have to mess with the emote sprite class bc this works
    //with createWithName, etc. yay :D
    for (auto& [path, def]: SoggyEmotes::Metadata::g_soggyEmotesMap) {
        auto texture = CCTextureCache::get()->addImage(path, false);

        if (!texture) {
            log::warn("soggy emote {} could not be placed in the texture cache", path);
            continue;
        }

        const auto size = texture->getContentSize();
        const auto frame = CCSpriteFrame::createWithTexture(texture, {0, 0, size.width, size.height});
        const auto name = fmt::format("particle_{}_001.png", def.m_particleIndex);
        CCSpriteFrameCache::get()->addSpriteFrame(frame, name.c_str());

        log::info("soggy emote {} successfully registered in sprite frame cache as {}", path, name);
    }
}