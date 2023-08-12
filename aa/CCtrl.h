#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <optional>

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

CObject::CObject(const std::string strName)
    : m_strName(strName) {}

std::string CObject::getName() const {
    return m_strName;
}

void CObject::setName(const std::string& strName) {
    m_strName = strName;
}

/// @brief 菜单类
class CMenu : public CObject {
    //ctor & dtor
public:
    CMenu() = default;
    CMenu(const std::string& strName);
    CMenu(const CMenu&) = delete;

    virtual ~CMenu();

public:
    bool appendCtrl(const std::string& strCtrlName, CObject* ctrl);

public:
    virtual bool onClick(std::vector<std::string> vecCmd) override;

    //props
private:
    std::vector<CObject*> m_vecSubCtrl;     //子控件容器
};

CMenu::CMenu(const std::string& strName)
    : CObject(strName) {}

CMenu::~CMenu() {
    for (auto& item : m_vecSubCtrl) {
        if (item != nullptr) {
            delete item;
        }
    }
    m_vecSubCtrl.clear();
}

bool CMenu::appendCtrl(const std::string& strCtrlName, CObject* ctrl) {
    for (auto& item : m_vecSubCtrl) {
        if (item->getName() == strCtrlName) {
            std::cout << "Append failed" << std::endl;
            return false;
        }
    }

    m_vecSubCtrl.push_back(ctrl);
    return true;
}

bool CMenu::onClick(std::vector<std::string> vecCmd) {
    if (vecCmd.size() == 1) {
        if (vecCmd.back() != m_strName) {
            return false;
        }

        for (auto& item : m_vecSubCtrl) {
            std::cout << item->getName() << " ";
        }
        std::cout << std::endl;
        return true;
    }

    vecCmd.pop_back();
    for (auto& item : m_vecSubCtrl) {
        if (vecCmd.back() == item->getName()) {
            return item->onClick(vecCmd);
        }
    }
    return false;
}

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

CLabel::CLabel(const std::string strName)
    : CObject(strName) {}

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

CButton::CButton(const std::string& strName)
    : CLabel(strName) {}

bool CButton::onClick(std::vector<std::string> vecCmd) {

    if (vecCmd.back() == m_strName) { //多余
        std::cout << "行为按钮" << std::endl;
        return true;
    }

    return false;
}

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

CSwitch::CSwitch()
    : m_bCurState(true) {}

CSwitch::CSwitch(const std::string& strName)
    : CLabel(strName) {}

bool CSwitch::onClick(std::vector<std::string> vecCmd) {
    if (vecCmd.back() == m_strName) { //多余
        std::cout << "开关按钮" << std::endl;
        return true;
    }

    return false;
}

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

CMutiChoice::CMutiChoice()
    : m_iCurSel(0) {}

CMutiChoice::CMutiChoice(const std::string& strName)
    : CLabel(strName), m_iCurSel(0) {}

bool CMutiChoice::onClick(std::vector<std::string> vecCmd) {
    if (vecCmd.back() == m_strName) { //多余
        std::cout << "二选一" << std::endl; //多选一
        return true;
    }

    return false;
}

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

CText::CText(const std::string& strText, bool bButton) {
    if (bButton)
        m_btnBehavior.emplace(strText);
    else
        m_strText.emplace(strText);
}

CText::CText(const std::string& strName, const std::string& strText, bool bButton)
    : CLabel(strName) {
    if (bButton)
        m_btnBehavior.emplace(strText);
    else
        m_strText.emplace(strText);
}

bool CText::onClick(std::vector<std::string> vecCmd) {
    if (vecCmd.back() == m_strName) {
        if (m_btnBehavior.has_value())
            std::cout << "显示标签+行为按钮" << std::endl;      //行为按钮
        else
            std::cout << "显示标签" << std::endl;              //显示标签
        return true;
    }
    return false;
}