#include "CButton.h"

CButton::CButton(const std::string& strName)
    : CLabel(strName) {}

bool CButton::onClick(std::vector<std::string> vecCmd) {

    if (vecCmd.back() == m_strName) { //多余
        std::cout << "行为按钮" << std::endl;
        return true;
    }

    return false;
}

