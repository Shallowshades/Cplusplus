#pragma once

#include "CLabel.h"
#include "CButton.h"
#include <optional>

/// @brief 显示标签（+按钮标签）
class CText : public CLabel {

public:
    enum ETextAndButton {
        Text = 0,
        Button
    };

    //ctor & dtor
public:
    CText(const std::string& strText, bool bButton = false);
    CText(const std::string& strName, const std::string& strText, bool bButton = false);
    ~CText() = default;

public:
    virtual bool onClick(std::vector<std::string> vecCmd) override;

    //props
private:
    std::optional<std::string> m_strText;
    std::optional<CButton> m_btnBehavior;
};