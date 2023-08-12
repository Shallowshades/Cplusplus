#include "CCtrl.h"
#include <iostream>
#include <optional>
#include <memory>
#include <vector>
#include <algorithm>

int main() {

    //first menu 1
    std::shared_ptr<CMenu> myMenu = std::make_shared<CMenu>("�ҵ�");

    //second menu 1.1
    CMenu* commonMenu = new CMenu("����");
    CLabel* softVersion = new CText("����汾��", "�������", CText::ETextAndButton::Button);
    CLabel* databaseVersion = new CText("���ݿ�汾��", "��������", CText::ETextAndButton::Button);
    commonMenu->appendCtrl(softVersion->getName(), softVersion);
    commonMenu->appendCtrl(databaseVersion->getName(), databaseVersion);

    //second menu 1.2
    CMenu* userInfoMenu = new CMenu("�û���Ϣ");
    CLabel* userName = new CText("�û���", "XXXX", CText::ETextAndButton::Text);
    CLabel* logoutButton = new CButton("�˳���¼");
    userInfoMenu->appendCtrl(userName->getName(), userName);
    userInfoMenu->appendCtrl(logoutButton->getName(), logoutButton);

    //second menu 1.3
    CMenu* settingMenu = new CMenu("����");
    CLabel* setUnit = new CMutiChoice("���õ�λ");
    CLabel* openCamera = new CSwitch("�Ƿ�����");
    settingMenu->appendCtrl(setUnit->getName(), setUnit);
    settingMenu->appendCtrl(openCamera->getName(), openCamera);

    //append 
    myMenu->appendCtrl(commonMenu->getName(), commonMenu);
    myMenu->appendCtrl(userInfoMenu->getName(), userInfoMenu);
    myMenu->appendCtrl(settingMenu->getName(), settingMenu);

    while (true) {
        std::string strInput;
        getline(std::cin, strInput);

        //split
        std::vector<std::string> vecCmd;
        while (true) {

            int iPos = strInput.find_first_of('-');
            vecCmd.emplace_back(strInput.substr(0, iPos));
            if (iPos != std::string::npos)
                strInput = strInput.substr(iPos + 1, std::string::npos);
            else
                break;
        }
        
        for (auto item : vecCmd)
            std::cout << item << std::endl;
        std::reverse(vecCmd.begin(), vecCmd.end());

        std::cout << "---" << std::endl;
        if (!myMenu->onClick(vecCmd))
            std::cout << "��������" << std::endl;
        std::cout << "---" << std::endl;
    }

    return 0;
}