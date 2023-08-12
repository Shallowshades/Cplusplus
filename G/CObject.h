#pragma once

#include <iostream>
#include <string>
#include <vector>

/// @brief 纯虚类 所有控件的基类
class CObject {
    //ctor & dtor
public:
    CObject() = default;
    CObject(const std::string strName);
    CObject(const CObject&) = delete;
    CObject& operator = (const CObject&) = delete;
    virtual ~CObject() = default;

    //get & set
public:
    std::string getName() const;
    void setName(const std::string& strName);

public:
    virtual bool onClick(std::vector<std::string> vecCmd) = 0; //change

    //props
protected:
    std::string m_strName;      //控件名称
};