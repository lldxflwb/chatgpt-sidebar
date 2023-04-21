//
// Created by 48449 on 2023/4/21.
//

#include "GetTextInterface.h"


GetTextInterface::GetTextInterface() :GetTextInterface(UseMode::DefaultMode,""){
    if (UseMode::DefaultMode == mode){
        installMouseHook();
    }
}

GetTextInterface::GetTextInterface(GetTextInterface::UseMode mode, const QString &text) : mode(mode), text(text) {

}

GetTextInterface::~GetTextInterface() {
    if (UseMode::DefaultMode == mode ){
        uninstallMouseHook();
    }
}

void GetTextInterface::ChangeMode(GetTextInterface::UseMode mode_) {
    if (UseMode::DefaultMode == mode ){
        uninstallMouseHook();
    }
    if (UseMode::DefaultMode == mode_){
        installMouseHook();
    }
}
