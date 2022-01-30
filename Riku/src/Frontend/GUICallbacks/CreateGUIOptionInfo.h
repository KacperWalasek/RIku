#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"

namespace CEGUI::Functor {

    class CreateGUIOptionInfo : public Functor
    {
    private:
        CEGUI::ScrollablePane* list;
        std::vector<std::string> headers;
        std::vector<std::string> optionInfo;
    public:
        CreateGUIOptionInfo(CEGUI::ScrollablePane* list, std::vector<std::string> headers, std::vector<std::string> info)
            : Functor(), list(list), headers(headers), optionInfo(info) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            for (const auto& header : headers)
            {
                CEGUI::Window* item = static_cast<CEGUI::Window*>(list->getChildElementRecursive(header));
                if (item == nullptr) continue;
                list->removeChild(item);
                item->destroy();
                delete item;
                item = static_cast<CEGUI::Window*>(list->getChildElementRecursive(header + "/description"));
                list->removeChild(item);
                item->destroy();
                delete item;
            }
            float y = 0;
            for (int i = 1; i < headers.size(); i++)
            {
                auto header = headers[i];
                auto label = static_cast<CEGUI::Window*>(CEGUI::GUI::createWidgetStatic("WindowsLook/Label",
                    glm::vec4(0.0f, 0.0f, 0.2f, 0.0f), glm::vec4(20.0f, y, 0.0f, 32.0f), header));
                label->setText(front::Lang::getUtf(header));
                label->setProperty("HorzFormatting", "LeftAligned");
                list->addChild(label);
                label = static_cast<CEGUI::Window*>(CEGUI::GUI::createWidgetStatic("WindowsLook/Label",
                    glm::vec4(0.2f, 0.0f, 0.65f, 0.0f), glm::vec4(20.0f, y, 0.0f, 32.0f), header+"/description"));
                label->setText(front::Lang::getUtf(optionInfo[i]));
                label->setProperty("HorzFormatting", "LeftAligned");
                list->addChild(label);
                y += 32.0f;
            }
            return true;
        };
    };
}