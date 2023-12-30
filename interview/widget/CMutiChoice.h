#pragma once

#include "CLabel.h"

/// @brief 多选一类
class CMutiChoice : public CLabel {
    //ctor & dtor
public:
    CMutiChoice();
    CMutiChoice(const std::string& strName);
    ~CMutiChoice() = default;

public:
    virtual bool onClick(std::vector<std::string> vecCmd) override;

    //props
private:
    int m_iCurSel;                               //当前选择的下标
    std::vector<std::string> m_vecSelections;       //选择集
};