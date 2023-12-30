#pragma once

#include "CLabel.h"
#include <string>

/// @brief 按钮类
class CButton : public CLabel {
    //ctor & dtor
public:
    CButton() = default;
    CButton(const std::string& strName);
    virtual ~CButton() = default;

public:
    virtual bool onClick(std::vector<std::string> vecCmd) override;

};