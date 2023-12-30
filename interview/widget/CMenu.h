#pragma once 

#include <string>
#include <unordered_map>
#include "CObject.h"

/// @brief 菜单类
class CMenu : public CObject {
    //ctor & dtor
public:
    CMenu() = default;
    CMenu(const std::string& strName);
    CMenu(const CMenu&) = delete;

    virtual ~CMenu();

    //get & set
public:
    const std::unordered_map<std::string, CObject*> getSubCtrl() const;
    void setSubCtrl(const std::unordered_map<std::string, CObject*>& mapSubCtrl);

public:
    bool appendCtrl(const std::string& strCtrlName, CObject* ctrl);

public:
    virtual bool onClick(std::vector<std::string> vecCmd) override;

    //props
private:
    std::unordered_map<std::string, CObject*> m_mapSubCtrl;     //子控件容器
};