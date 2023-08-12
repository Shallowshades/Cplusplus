#include "CCtrl.h"
#include <iostream>
#include <optional>
#include <memory>
#include <vector>
#include <algorithm>

int main() {

    //first menu 1
    std::shared_ptr<CMenu> myMenu = std::make_shared<CMenu>("我的");

    //second menu 1.1
    CMenu* commonMenu = new CMenu("常用");
    CLabel* softVersion = new CText("软件版本号", "更新软件", CText::ETextAndButton::Button);
    CLabel* databaseVersion = new CText("数据库版本号", "更新数据", CText::ETextAndButton::Button);
    commonMenu->appendCtrl(softVersion->getName(), softVersion);
    commonMenu->appendCtrl(databaseVersion->getName(), databaseVersion);

    //second menu 1.2
    CMenu* userInfoMenu = new CMenu("用户信息");
    CLabel* userName = new CText("用户名", "XXXX", CText::ETextAndButton::Text);
    CLabel* logoutButton = new CButton("退出登录");
    userInfoMenu->appendCtrl(userName->getName(), userName);
    userInfoMenu->appendCtrl(logoutButton->getName(), logoutButton);

    //second menu 1.3
    CMenu* settingMenu = new CMenu("设置");
    CLabel* setUnit = new CMutiChoice("设置单位");
    CLabel* openCamera = new CSwitch("是否打开相机");
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
            std::cout << "输入有误" << std::endl;
        std::cout << "---" << std::endl;
    }

    return 0;
}