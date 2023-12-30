#include "CMenu.h"

CMenu::CMenu(const std::string& strName)
    : CObject(strName) {}

CMenu::~CMenu() {
    for (auto& item : m_mapSubCtrl) {
        if (item.second != nullptr) {
            delete item.second;
        }
    }
    m_mapSubCtrl.clear();
}

const std::unordered_map<std::string, CObject*> CMenu::getSubCtrl() const {
    return m_mapSubCtrl;
}

void CMenu::setSubCtrl(const std::unordered_map<std::string, CObject*>& mapSubCtrl) {
    m_mapSubCtrl = mapSubCtrl;
}

bool CMenu::appendCtrl(const std::string& strCtrlName, CObject* ctrl) {
    if (m_mapSubCtrl.find(strCtrlName) != m_mapSubCtrl.end()) {
        std::cout << "Append failed" << std::endl;
        return false;
    }

    m_mapSubCtrl[strCtrlName] = ctrl;
    return true;
}

bool CMenu::onClick(std::vector<std::string> vecCmd) {
    if (vecCmd.size() == 1) {
        if (vecCmd.back() != m_strName) {
            return false;
        }

        for (auto item : m_mapSubCtrl) {
            std::cout << item.first << " ";
        }
        std::cout << std::endl;
        return true;
    }

    vecCmd.pop_back();
    for (auto item : m_mapSubCtrl) {
        if (vecCmd.back() == item.first) {
            return item.second->onClick(vecCmd);
        }
    }
    return false;
}
