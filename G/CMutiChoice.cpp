#include "CMutiChoice.h"

CMutiChoice::CMutiChoice()
    : m_iCurSel(0) {}

CMutiChoice::CMutiChoice(const std::string& strName)
    : CLabel(strName), m_iCurSel(0) {}

bool CMutiChoice::onClick(std::vector<std::string> vecCmd) {
    if (vecCmd.back() == m_strName) { //����
        std::cout << "��ѡһ" << std::endl; //��ѡһ
        return true;
    }

    return false;
}