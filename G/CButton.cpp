#include "CButton.h"

CButton::CButton(const std::string& strName)
    : CLabel(strName) {}

bool CButton::onClick(std::vector<std::string> vecCmd) {

    if (vecCmd.back() == m_strName) { //����
        std::cout << "��Ϊ��ť" << std::endl;
        return true;
    }

    return false;
}

