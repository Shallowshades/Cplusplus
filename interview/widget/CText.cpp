#include "CText.h"

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
