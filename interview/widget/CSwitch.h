#pragma once

#include "CLabel.h"

/// @brief 开关类
class CSwitch : public CLabel {
    //ctor & dtor
public:
    CSwitch();
    CSwitch(const std::string& strName);
    ~CSwitch() = default;

public:
    virtual bool onClick(std::vector<std::string> vecCmd) override;

    //props
private:
    bool m_bCurState;   //当前开关状态
};