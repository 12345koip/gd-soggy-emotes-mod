#include <ranges>
#include <Geode/Geode.hpp>
#include <Geode/modify/EmotePickerPopup.hpp>
#include "../Emotes/Metadata.hpp"

using namespace geode::prelude;
using namespace SoggyEmotes::Metadata;

class $modify(EmotePickerPopup) {
    struct Fields {
        std::vector<CCMenuItemSpriteExtra*> soggyEmotes {};
    };

    static void onModify(auto& self) {
        if (!self.setHookPriorityAfterPost("EmotePickerPopup::layoutEmoteGrid", "kx_.better-emote-picker"))
            log::warn("could not set EmotePickerPopup::layoutEmoteGrid hook prio");
    }

    void onBuildWindowContent() {
        EmotePickerPopup::onBuildWindowContent();

        //get rid of current.
        for (auto* cell: this->m_fields->soggyEmotes)
            cell->removeFromParent();
        this->m_fields->soggyEmotes.clear();

        //got to re-tag the recents so onPickEmote recognises them.
        for (auto* recent: this->m_recentEmoteButtons) {
            auto* sprite = static_cast<EmoteSprite*>(recent->getNormalImage());
            if (sprite->m_emoteDef->m_particleIndex >= kSoggyEmotesBase && sprite->m_emoteDef->m_particleIndex < kRecentEmotesBase)
                recent->setTag(sprite->m_emoteDef->m_particleIndex);
        }

        //and now add the soggy ones
        for (auto& def: g_soggyEmotesMap | std::views::values) {
            auto cell = this->addCell(&def, def.m_particleIndex);
            if (!cell) continue;

            cell->setID("soggy_emote"_spr);
            cell->setEnabled(this->m_canAdd);
            cell->setOpacity(this->m_canAdd? 255: 90);
            this->m_fields->soggyEmotes.push_back(cell);
        }

        this->layoutEmoteGrid();
    }

    void layoutEmoteGrid() {
        EmotePickerPopup::layoutEmoteGrid();

        //last non-alias def is at index 195 so its placed last and hence lowest
        const auto lastCell = this->m_scrollContentMenu->getChildByTag(195);
        if (!lastCell) return;
        const float lowestY = lastCell->getPositionY();

        const int maxCols = (this->m_windowWidth - 8.0f) / 26.0f;
        const float pad_x = (this->m_windowWidth - (maxCols * 26.0f)) * 0.5f;
        float currentY = lowestY - 38.0f;
        int currentCol = 0;

        for (auto* cell: this->m_fields->soggyEmotes) {
            cell->setPosition({pad_x + (currentCol + 0.5f) * 26.0f, currentY});
            ++currentCol;

            if (currentCol == maxCols) { //newline.
                currentCol = 0;
                currentY -= 26.0f;
            }
        }

        this->m_scrollContentLayer->setContentHeight(18.0f - currentY);
    }

    void onPickEmote(CCObject* sender) {
        if (!this->canAddEmote()) return;

        auto* sprite = static_cast<CCMenuItemSpriteExtra*>(sender);
        const auto tag = sprite->getTag();

        if (tag <= kSoggyEmotesBase || tag > kRecentEmotesBase)
            return EmotePickerPopup::onPickEmote(sender);

        auto* def = GetSoggyEmoteDefByIndex(tag);
        GameManager::sharedState()->addRecentEmote(def->m_name);
        this->m_input->insertAtCursor(fmt::format(":{}:", def->m_name));
    }
};