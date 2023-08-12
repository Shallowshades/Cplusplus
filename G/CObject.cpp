#include "CObject.h"

CObject::CObject(const std::string strName)
    : m_strName(strName) {}

std::string CObject::getName() const {
    return m_strName;
}

void CObject::setName(const std::string& strName) {
    m_strName = strName;
}
