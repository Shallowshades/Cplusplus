#include "CSwitch.h"

CSwitch::CSwitch()
    : m_bCurState(true) {}

CSwitch::CSwitch(const std::string& strName)
    : CLabel(strName) {}

bool CSwitch::onClick(std::vector<std::string> vecCmd) {
    if (vecCmd.back() == m_strName) { //����
        std::cout << "���ذ�ť" << std::endl;
        return true;
    }

    return false;
}
