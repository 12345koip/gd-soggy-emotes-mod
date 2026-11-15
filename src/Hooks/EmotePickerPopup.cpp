#include <Geode/Geode.hpp>
#include <Geode/modify/EmotePickerPopup.hpp>
#include "../Emotes/Metadata.hpp"

using namespace geode::prelude;

class $modify(EmotePickerPopup) {
    struct Fields {
        std::vector<CCMenuItemSpriteExtra*> soggyEmotes {};
    };

    void onBuildWindowContent() {
        EmotePickerPopup::onBuildWindowContent();
        this->m_fields->soggyEmotes.clear();

        for (auto& [_, def]: SoggyEmotes::Metadata::g_soggyEmotesMap) {
            auto cell = this->addCell(&def, def.m_particleIndex);
            cell->setID("soggy_emote"_spr);
            this->m_fields->soggyEmotes.push_back(cell);
        }
    }

    void layoutEmoteGrid() {
        EmotePickerPopup::layoutEmoteGrid();


    }
};