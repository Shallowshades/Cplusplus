#pragma once 

#include "CObject.h"

/// @brief 纯虚类 标签
class CLabel : public CObject {
    //ctor & dtor
public:
    CLabel() = default;
    CLabel(const std::string strName);
    virtual ~CLabel() = default;

public:
    virtual bool onClick(std::vector<std::string> vecCmd) = 0;
};