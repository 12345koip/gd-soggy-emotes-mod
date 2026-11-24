#include <kx_.custom-emotes-api/CustomEmotes.hpp>
#include <Geode/Geode.hpp>

using namespace geode::prelude;

constexpr std::array<std::pair<const char*, const char*>, 6> kSoggyEmoteInfo {
    std::make_pair<const char*, const char*>("soggy_original.png"_spr, "soggy"),
    {"soggy_cup.png"_spr, "soggy_cup"},
    {"soggy_dry.png"_spr, "soggy_dry"},
    {"soggy_fear.png"_spr, "soggy_fear"},
    {"soggy_sniff.png"_spr, "soggy_sniff"},
    {"soggy_what.png"_spr, "soggy_what"}
};

$on_game(Loaded) {
    auto result = CustomEmotes::CustomEmotesContainer::create("Soggy");
    if (!result.ok()) {
        log::warn("Could not create container. Soggy emotes will not function.");
        return;
    }

    CustomEmotes::CustomEmoteOptions options {};
    options.scale = 1.0f;

    auto* container = result.unwrap();
    for (const auto& [filename, emoteName]: kSoggyEmoteInfo) {
        const auto res = container->NewEmoteFromImage(filename, emoteName, options);
        if (!res.ok())
            log::warn("soggy emote {} could not be created - {}", emoteName, res.unwrapErr());
        else
            log::info("created soggy emote {}", emoteName);
    }
}