void window::setcolorinactive(const std::string text0content, const std::string text0background,
                              const std::string text1content, const std::string text1background,
                              const std::string paddingContent, const std::string paddingBackground,
                              const std::string errorContent, const std::string errorBackground) {
    const int i = 0;
    color[i].text[0].content = text0content;
    color[i].text[0].background = text0background;
    color[i].text[1].content = text1content;
    color[i].text[1].background = text1background;
    color[i].padding.content = paddingContent;
    color[i].padding.background = paddingBackground;
    color[i].error.content = errorContent;
    color[i].error.background = errorBackground;
}

void window::setcoloractive(const std::string text0content, const std::string text0background,
                              const std::string text1content, const std::string text1background,
                              const std::string paddingContent, const std::string paddingBackground,
                              const std::string errorContent, const std::string errorBackground) {
    const int i = 1;
    color[i].text[0].content = text0content;
    color[i].text[0].background = text0background;
    color[i].text[1].content = text1content;
    color[i].text[1].background = text1background;
    color[i].padding.content = paddingContent;
    color[i].padding.background = paddingBackground;
    color[i].error.content = errorContent;
    color[i].error.background = errorBackground;
}
